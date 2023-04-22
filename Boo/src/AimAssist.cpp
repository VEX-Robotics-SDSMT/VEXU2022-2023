#include "../include/AimAssist.h"
using namespace Mines;

AimAssist::AimAssist(pros::Vision pVision, uint8_t targetSigID, DiffDrive *diffDrive, void (*fireFunc)()) : frameQueue(), 
logger(LoggerSettings::none), vision(pVision)
{
    targetSig = targetSigID;
    deltaTime = DELTA_TIME;
    fire = fireFunc; //setting a function pointer
    drive = diffDrive;
}

Target AimAssist::GetTarget()
{
    Target retVal;
    retVal.certainty = meanCertainty;
    retVal.rotation = degreeMean;
    retVal.rotVar = degreeVariance;
    retVal.distance = distMean;
    retVal.distVar = distVariance;
    
    return retVal;
}

void AimAssist::Clear()
{
    while (frameQueue.size() > 0)
    {
        frameQueue.pop();
    }
    meanCertainty = 0;
}

void AimAssist::update(double deltaT)
{
    //add the new data to the queue and if it has any certainty, update the running totals
    SubTarget newFrame = checkTargeting();
    frameQueue.push(newFrame);
    meanCertainty += newFrame.certainty / TARGET_COUNT;
    distMean += newFrame.distance / TARGET_COUNT;
    distVariance += pow(newFrame.distance - distMean, 2) / TARGET_COUNT;
    degreeMean += newFrame.rotation / TARGET_COUNT;
    degreeVariance += pow(newFrame.rotation - degreeMean, 2) / TARGET_COUNT;

    //std::cout << "inVal: " << newFrame.rotation / TARGET_COUNT << std::endl;

    //remove oldest data if the max count is reached
    if (frameQueue.size() > TARGET_COUNT)
    {
        SubTarget oldFrame = frameQueue.front();
        frameQueue.pop();

        meanCertainty -= oldFrame.certainty / TARGET_COUNT;
        distMean -= oldFrame.distance / TARGET_COUNT;
        distVariance -= pow(oldFrame.distance - distMean, 2) / TARGET_COUNT;
        degreeMean -= oldFrame.rotation / TARGET_COUNT;
        degreeVariance -= pow(oldFrame.rotation - degreeMean, 2) / TARGET_COUNT;

        //std::cout << "outVal: " << oldFrame.rotation / TARGET_COUNT << std::endl;
    }

    //std::cout << degreeMean << std::endl;
}

double getRatioAccuracy(double target, double other)
{
    double currentScaled = other / target;
    //std::cout << "scaled: " << currentScaled << " " << target << " " << other << std::endl;
    return std::min(currentScaled, 1 / currentScaled);
}

double AimAssist::getOffsetAccuracy(double distance)
{
    return std::max((-std::fabs(distance) / MAX_DIST) + 1.0, 0.0);
}

double AimAssist::getPairAccuracy(pros::vision_object_s_t top, pros::vision_object_s_t bottom)
{
    double topAccuracy = getRatioAccuracy(TOP_RATIO, top.height/(double)top.width);
    logger.Log("top acc: " + std::to_string(topAccuracy), 3, LoggerSettings::verbose);
    double bottomAccuracy = getRatioAccuracy(BOTTOM_RATIO, bottom.height/(double)bottom.width);
    logger.Log("bot acc: " + std::to_string(bottomAccuracy), 4, LoggerSettings::verbose);
    double distanceAccuracy = getOffsetAccuracy(top.x_middle_coord - bottom.x_middle_coord);
    logger.Log("dist acc: " + std::to_string(distanceAccuracy), 5, LoggerSettings::verbose);
    //std::cout << "top:" << topAccuracy << " bot:" << bottomAccuracy << " dist:" << distanceAccuracy << std::endl;
    return (topAccuracy + bottomAccuracy + distanceAccuracy) / 3;
}

SubTarget AimAssist::checkTargeting()
{
    std::vector<pros::vision_object_s_t> objectList =  getObjectsBySig();
    int listSize = objectList.size();
    double bestAccuracy = 0;
    int bestTop = -1;
    int bestBottom = -1;

    getPairAccuracy(objectList[0], objectList[1]);
    for(int i = 0; i < listSize; i++)
    {
        for (int j = 0; j < listSize; j++)
        {
            if (i != j)
            {
                double currentError = getPairAccuracy(objectList[i], objectList[j]);
                if(currentError > bestAccuracy)
                {
                    bestAccuracy = currentError;
                    bestTop = i;
                    bestBottom = j;
                }
            }
        }
    }

    SubTarget target = SubTarget();
    target.rotation = objectList[bestBottom].x_middle_coord; // might need to be rotated to center
    target.distance = objectList[bestBottom].y_middle_coord - objectList[bestTop].y_middle_coord; //TODO: some fancy trig here
    target.certainty = bestAccuracy;
    //std::cout << "target: " << target.degrees << " " << target.distance << " " << target.certainty << std::endl;
    return target;
}


bool sortHelper(pros::vision_object_s_t i1, pros::vision_object_s_t i2)
{
    return (i1.x_middle_coord < i2.x_middle_coord);
}

std::vector<pros::vision_object_s_t> AimAssist::getObjectsBySig()
{
    std::vector<pros::vision_object_s_t> retOb;
    for (int i = 0; i < OBS_TO_GET; i++)
    {
        pros::vision_object_s_t box = vision.get_by_sig(i, targetSig);
        logger.Log("box hw: " + std::to_string(box.height) + ", " + std::to_string(box.width), i, LoggerSettings::verbose);
        //std::cout << "box: " << box.width << " " << box.height << " " << box.x_middle_coord << std::endl;
        retOb.push_back(box);
    }

    std::sort(retOb.begin(), retOb.end(), sortHelper);
    return retOb;
}





void AimAssist::AimFire(int disksToFire)
{
    int FiredDisks = 0;
    drive->SetPausedPID(true);

    while (FiredDisks < disksToFire)
    {
        Target target = GetTarget();
        //std::cout << "Rot: " << target.rotation << " rotVar: " << target.rotVar << " certainty: " << target.certainty << std::endl;
        double targetSpeed = fabs(target.rotation - leftOffset) * turnSpeed;

        if (target.certainty > 0.6)
        {

            if (target.rotation > (leftOffset + turnTol))
            {
                drive->setTurnVelocity(targetSpeed);
                std::cout << "Too much: " << targetSpeed << std::endl;
            }
            else if (target.rotation < (leftOffset - turnTol))
            {
                drive->setTurnVelocity(-targetSpeed);
                std::cout << "Not Enough: " << targetSpeed << std::endl;
            }
            else
            {
                std::cout << "Just right\n";
                drive->setTurnVelocity(0);
                //fire();
                //pros::delay(250);
            }
        }
        else
        {
            std::cout << "Uncertain: " << target.certainty << std::endl;
            drive->setTurnVelocity(0);
        }

        pros::delay(20);
    }

    drive->SetPausedPID(false);
}

//d = (h / tan(theta)) - (h1*h2)
double doDistCalc(double hHigh, double hLow, double theta)
{
    double hMid = hHigh - hLow;
    return (hMid / tan(theta)) - (hHigh - hLow);
}

double AimAssist::getDistanceFromGoal()
{
    
    



    
}
