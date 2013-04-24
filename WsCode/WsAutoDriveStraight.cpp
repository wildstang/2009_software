#include "WsAutoDriveStraight.h"


WsAutoDriveStraight::WsAutoDriveStraight(UINT8 driveTime)
{
  a_driveTime = driveTime;
}

WsAutoDriveStraight::~WsAutoDriveStraight()
{
}

void WsAutoDriveStraight::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;

    WsAutoNStepBase::initParams();

    drive1.crabAngle = 0;
    drive1.driveVector.a_speed = 1;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = a_driveTime;

    // Add the steps to the program...order matters
    addStep(drive1);
}
