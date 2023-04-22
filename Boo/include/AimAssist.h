#ifndef AIM_ASSIST_H
#define AIM_ASSIST_H

#include "pros/vision.hpp"
#include "TaskBase.h"
#include <queue>
#include <vector>
#include "math.h"
#include "Logger.h"
#include "DiffDrive.h"

namespace Mines{

struct SubTarget
{
    double rotation;
    double distance;
    double certainty; //between 0 and 1
};

struct Target
{
    double rotation;
    double distance;
    double certainty; //between 0 and 1
    double rotVar;
    double distVar;
};

class AimAssist: public TaskBase
{
    private:
        int TARGET_COUNT = 50;
        int DELTA_TIME = 5;

        double TOP_RATIO = 50.0/ 330.0; //(mm)
        double BOTTOM_RATIO = 100.0 / 400.0; //(mm)
        double MAX_DIST = 50.0; //(mm)
        int OBS_TO_GET = 5;

        pros::Vision vision;
        uint8_t targetSig;
        std::queue<SubTarget> frameQueue;
        ScreenLogger logger;

        DiffDrive *drive;
        void (*fire)();

        double meanCertainty;
        double degreeMean;
        double degreeVariance;
        double distMean;
        double distVariance;

        int testCount = 0;

        //heights - in inches
        double CamHeight;
        const double BottomBasket = 21.25;
        const double TopBasket = 25;
        const double BottomCap = 35;
        const double TopCap = 36;

        void update(double deltaT);
        SubTarget checkTargeting();
        std::vector<pros::vision_object_s_t> getObjectsBySig();
        double getPairAccuracy(pros::vision_object_s_t top, pros::vision_object_s_t bottom);
        double getOffsetAccuracy(double distance);
        double getDistanceFromGoal();

    public:
        double turnSpeed = 10;
        double leftOffset = 200;
        double turnTol = 10;
        int fireDelay = 1000;

        AimAssist(pros::Vision pVision, uint8_t targetSigID, DiffDrive *drive, void (*fireFunc)());
        Target GetTarget();
        void Clear();

        void AimFire(int disksToShoot);
        
};

}
#endif