#include "WsAutoOppHome.h"


WsAutoOppHome::WsAutoOppHome()
{
}

WsAutoOppHome::~WsAutoOppHome()
{
}

void WsAutoOppHome::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT coast1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;
    WsAutoNStepBase::WsAutoNStepCmdT drive3;
    WsAutoNStepBase::WsAutoNStepCmdT drive4;
    WsAutoNStepBase::WsAutoNStepCmdT drive5;
    WsAutoNStepBase::WsAutoNStepCmdT drive6;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = 50;
    //drive1.crabAngle = 45;
    drive1.driveVector.a_speed = .5;
    drive1.driveVector.a_direction = 0;
    //drive1.timeout = 2;
    drive1.timeout = 2;

    // Attributes for coast 1
    coast1.crabAngle = 45;
    coast1.driveVector.a_speed = 0;
    coast1.driveVector.a_direction = 0;
    coast1.timeout = .25;

    // Attributes for drive 2
    //drive2.crabAngle = 10;
    drive2.crabAngle = 25;
    drive2.driveVector.a_speed = .5;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = 1;

    // Attributes for drive 3
    drive3.crabAngle = 5;
    drive3.driveVector.a_speed = .4;
    drive3.driveVector.a_direction = 0;
    drive3.timeout = 1;

    // Attributes for drive 4
    drive4.crabAngle = 0;
    drive4.driveVector.a_speed = .4;
    drive4.driveVector.a_direction = 0;
    drive4.timeout = 1.5;

    // Attributes for drive 5
    drive5.crabAngle = -45;
    drive5.driveVector.a_speed = .4;
    drive5.driveVector.a_direction = -0;
    drive5.timeout = 3.5;

    // Attributes for drive 6
    drive6.crabAngle = 0;
    drive6.driveVector.a_speed = .2;
    drive6.driveVector.a_direction = -0;
    drive6.timeout = 1;

    a_initEscFrontSpeed = WsEscalator::a_escFullUp;
    a_initEscBackSpeed = WsEscalator::a_escFullDown;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(coast1);
    addStep(drive2);
    addStep(drive3);
    addStep(drive4);
    addStep(drive5);
    addStep(drive6);
}
