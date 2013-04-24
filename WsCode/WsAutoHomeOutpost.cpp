#include "WsAutoHomeOutpost.h"


WsAutoHomeOutpost::WsAutoHomeOutpost()
{
}

WsAutoHomeOutpost::~WsAutoHomeOutpost()
{
}

void WsAutoHomeOutpost::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT coast1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;
    WsAutoNStepBase::WsAutoNStepCmdT coast2;
    WsAutoNStepBase::WsAutoNStepCmdT drive3;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = -45;
    drive1.driveVector.a_speed = .5;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = 2;
    
    /*** ATLANTA NUMBER **
     * drive1.timeout = 1.5;
     */

    // Attributes for coast 1
    coast1.crabAngle = -45;
    coast1.driveVector.a_speed = 0;
    coast1.driveVector.a_direction = 0;
    coast1.timeout = .25;

    // Attributes for drive 2
    drive2.crabAngle = -10;
    drive2.driveVector.a_speed = .5;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = 2;
    /** ATLANTA **
     *  drive2.timeout = 1.25;
     */

    // Attributes for coast 2
    coast1.crabAngle = 0;
    coast1.driveVector.a_speed = 0;
    coast1.driveVector.a_direction = 0;
    coast1.timeout = .25;

    // Attributes for drive 3
    drive3.crabAngle = 0;
    drive3.driveVector.a_speed = .75;
    drive3.driveVector.a_direction = -90;
    drive3.timeout = 1;
    
    a_initEscFrontSpeed = WsEscalator::a_escFullUp;
    a_initEscBackSpeed = WsEscalator::a_escFullDown;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(coast1);
    addStep(drive2);
    addStep(coast2);
    addStep(drive3);
}
