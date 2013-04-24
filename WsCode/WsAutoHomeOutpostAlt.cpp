#include "WsAutoHomeOutpostAlt.h"


WsAutoHomeOutpostAlt::WsAutoHomeOutpostAlt()
{
}

WsAutoHomeOutpostAlt::~WsAutoHomeOutpostAlt()
{
}

void WsAutoHomeOutpostAlt::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;
    WsAutoNStepBase::WsAutoNStepCmdT coast2;
    WsAutoNStepBase::WsAutoNStepCmdT drive3;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = 0;
    drive1.driveVector.a_speed = .5;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = 2.5;

    // Attributes for drive 2
    drive2.crabAngle = -90;
    drive2.driveVector.a_speed = .5;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = 2.5;

    // Attributes for drive 3
    drive3.crabAngle = 0;
    drive3.driveVector.a_speed = .75;
    drive3.driveVector.a_direction = -90;
    drive3.timeout = 1;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(drive2);
    addStep(drive3);
}
