#ifndef AIM_ASSIST_H
#define AIM_ASSIST_H

#include "pros/vision.hpp"
#include "TaskBase.h"
#include <queue>
#include <vector>
#include "math.h"

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

class AimAssist: TaskBase
{
    private:
        int TARGET_COUNT = 20;

        pros::Vision *vision;
        uint8_t targetSig;
        std::queue<SubTarget> frameQueue;

        double meanCertainty;
        double degreeMean;
        double degreeVariance;
        double distMean;
        double distVariance;

        void update();
        SubTarget checkTargeting();
        std::vector<pros::vision_object_s_t> getObjectsBySig();

    public:
        AimAssist(pros::Vision pVision, uint8_t targetSigID);
        Target GetTarget();
        void Clear();
        
};

}
#endif