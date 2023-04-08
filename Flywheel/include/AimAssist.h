#ifndef AIM_ASSIST_H
#define AIM_ASSIST_H

#include "pros/vision.hpp"
#include "TaskBase.h"
#include <queue>
#include <vector>
#include "math.h"
#include "Logger.h"

namespace Mines{

struct SubTarget
{
    double degrees;
    double distance;
    double certainty; //between 0 and 1
};

struct Target
{
    double degrees;
    double distance;
    double certainty; //between 0 and 1
    double degVar;
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

        double meanCertainty;
        double degreeMean;
        double degreeVariance;
        double distMean;
        double distVariance;

        int testCount = 0;

        void update(double deltaT);
        SubTarget checkTargeting();
        std::vector<pros::vision_object_s_t> getObjectsBySig();
        double getPairAccuracy(pros::vision_object_s_t top, pros::vision_object_s_t bottom);
        double getDistanceAccuracy(double distance);

    public:
        AimAssist(pros::Vision pVision, uint8_t targetSigID);
        Target GetTarget();
        void Clear();
        
};

}
#endif