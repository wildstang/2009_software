//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsAutoOutpostOutpostLeft.cpp
//  @ Date : 2/8/2009
//  @ Author : 
//
//


#include "WsAutoOutpostOutpostLeft.h"

WsAutoOutpostOutpostLeft::WsAutoOutpostOutpostLeft()
{
}

WsAutoOutpostOutpostLeft::~WsAutoOutpostOutpostLeft()
{
}

void WsAutoOutpostOutpostLeft::initParams()
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT coast1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;
    WsAutoNStepBase::WsAutoNStepCmdT coast2;
    WsAutoNStepBase::WsAutoNStepCmdT drive3;
    WsAutoNStepBase::WsAutoNStepCmdT coast3;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = -45;
    drive1.driveVector.a_speed = 1;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = 2;
    /*** ATLANTA NUMBER ***
     *  drive1.timeout = 1.5;
     */

    // Attributes for coast 1
    coast1.crabAngle = -45;
    coast1.driveVector.a_speed = 0;
    coast1.driveVector.a_direction = 0;
    coast1.timeout = .25;

    // Attributes for drive 2
    drive2.crabAngle = 30;
    drive2.driveVector.a_speed = 1;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = 2;

    // Attributes for coast 2
    coast2.crabAngle = 0;
    coast2.driveVector.a_speed = 0;
    coast2.driveVector.a_direction = 0;
    coast2.timeout = 0;

    // Attributes for drive 3
    drive3.crabAngle = 0;
    drive3.driveVector.a_speed = 1;
    drive3.driveVector.a_direction = 90;
    drive3.timeout = 1.75;

    // Attributes for coast 3
    coast3.crabAngle = 0;
    coast3.driveVector.a_speed = 0;
    coast3.driveVector.a_direction = 0;
    coast3.timeout = 1;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(coast1);
    addStep(drive2);
    addStep(coast2);
    addStep(drive3);
    addStep(coast3);
}
