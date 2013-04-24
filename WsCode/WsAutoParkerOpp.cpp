#include "WsAutoParkerOpp.h"


WsAutoParkerOpp::WsAutoParkerOpp()
{
}

WsAutoParkerOpp::~WsAutoParkerOpp()
{
}

void WsAutoParkerOpp::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT coast1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = -45;
    drive1.driveVector.a_speed = .5;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = 3.5;

    // Attributes for coast 1
    coast1.crabAngle = -60;
    coast1.driveVector.a_speed = 0;
    coast1.driveVector.a_direction = 0;
    coast1.timeout = .5;

    // Attributes for drive 2
    drive2.crabAngle = -60;
    drive2.driveVector.a_speed = .3;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = 1.5;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(coast1);
    addStep(drive2);
}
