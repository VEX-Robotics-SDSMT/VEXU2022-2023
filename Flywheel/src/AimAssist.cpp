#include "../include/AimAssist.h"
using namespace Mines;

AimAssist::AimAssist(pros::Vision pVision, uint8_t targetSigID) : frameQueue()
{
    vision = &pVision;
    targetSig = targetSigID;
}

Target AimAssist::GetTarget()
{
    Target retVal;
    retVal.certainty = meanCertainty;
    retVal.degrees = degreeMean;
    retVal.degVar = degreeVariance;
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

void AimAssist::update()
{
    SubTarget newFrame = checkTargeting();

    //add the new data to the queue and if it has any certainty, update the running totals
    frameQueue.push(newFrame);
    int size = frameQueue.size();
    meanCertainty += newFrame.certainty / size;
    if (newFrame.certainty > 0.01)
    {
        distMean += newFrame.distance / size;
        distVariance += pow(newFrame.distance - distMean, 2) / size;
        degreeMean += newFrame.degrees / size;
        degreeVariance += pow(newFrame.degrees - degreeMean, 2) / size;
    }

    //remove oldest data if the max count is reached
    if (frameQueue.size() >= TARGET_COUNT)
    {
        SubTarget oldFrame = frameQueue.front();
        frameQueue.pop();

        size = frameQueue.size();
        meanCertainty -= oldFrame.certainty / size;
        if (oldFrame.certainty > 0.01)
        {
            distMean -= oldFrame.distance / size;
            distVariance -= pow(oldFrame.distance - distMean, 2) / size;
            degreeMean -= oldFrame.degrees / size;
            degreeVariance -= pow(oldFrame.degrees - degreeMean, 2) / size;
        }
    }
}

SubTarget AimAssist::checkTargeting()
{
    
}


bool sortHelper(pros::vision_object_s_t i1, pros::vision_object_s_t i2)
{
    return (i1.x_middle_coord < i2.x_middle_coord);
}

std::vector<pros::vision_object_s_t> AimAssist::getObjectsBySig()
{
    std::vector<pros::vision_object_s_t> retOb;
    for (int i = 0; i < 8; i++)
    {
        retOb.push_back(vision->get_by_sig(i, targetSig));
    }

    std::sort(retOb.begin(), retOb.end());
    return retOb;
}
