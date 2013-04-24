#include "WsAutoParkerHomeAlt.h"


WsAutoParkerHomeAlt::WsAutoParkerHomeAlt()
{
}

WsAutoParkerHomeAlt::~WsAutoParkerHomeAlt()
{
}

void WsAutoParkerHomeAlt::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;
    WsAutoNStepBase::WsAutoNStepCmdT drive3;
    WsAutoNStepBase::WsAutoNStepCmdT drive4;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = 0;
    drive1.driveVector.a_speed = .5;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = 2;

    // Attributes for coast 1
    drive2.crabAngle = 90;
    drive2.driveVector.a_speed = .5;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = .5;

    // Attributes for drive 2
    drive3.crabAngle = 75;
    drive3.driveVector.a_speed = .4;
    drive3.driveVector.a_direction = 0;
    drive3.timeout = 2;

    // Attributes for drive 3
    drive4.crabAngle = -15;
    drive4.driveVector.a_speed = .3;
    drive4.driveVector.a_direction = 0;
    drive4.timeout = 1;


    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(drive2);
    addStep(drive3);
    addStep(drive4);
}
