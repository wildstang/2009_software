//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControlMethodArcade.cpp
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#include "WsControlMethodArcade.h"
#include "WsDriveVector.h"
#include "WsControllerAxis.h"
#include "WsControllerButton.h"
#include "WsDashboard.h"

WsControlMethodArcade::WsControlMethodArcade()
{
    ap_driveStick = NULL;
    ap_turboButton = NULL;
    a_turboScaleFactor = 0.5;
    ap_dashboard = WsDashboard::getInstance();
}

WsControlMethodArcade::~WsControlMethodArcade()
{
}

void WsControlMethodArcade::assignDriveStick(WsControllerPolarStick* p_stick)
{
    ap_driveStick = p_stick;
}

void WsControlMethodArcade::assignTurboButton(WsControllerButton* p_turbo)
{
    ap_turboButton = p_turbo;
}

WsDriveVector WsControlMethodArcade::getDriveVector(void )
{
    WsDriveVector v;
    float driveX = 0;
    float driveY = 0;
    float driveR = 0;
    float driveA = 0;

    a_turboState = true;

    if(ap_driveStick != NULL)
    {
          driveX = ap_driveStick->getX();
          driveY = ap_driveStick->getY();
          driveR = ap_driveStick->getRadius();
          driveA = ap_driveStick->getAngle();
    }

    if(ap_turboButton != NULL)
    {
        a_turboState = !ap_turboButton->getState();
    }

    v.a_speed = driveR;
    v.a_direction = driveA;

    if(a_turboState == false)
    {
        v.a_speed *= a_turboScaleFactor;
    }

    return v;
}

/* The get and clear are used to get info up to the dashboard */
bool WsControlMethodArcade::getTurboState(void)
{
    return a_turboState;
}

void WsControlMethodArcade::clearTurboState(void)
{
    a_turboState = false;
}
