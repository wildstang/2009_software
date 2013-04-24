//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControllerBase.h
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#if !defined(_WSCONTROLLERBASE_H)
#define _WSCONTROLLERBASE_H

#include <stdio.h>
#include "Gamepad.h"

class Joystick;
class DriverStation;

class WsControllerBase
{
protected:
    UINT32 a_axisNum;
    UINT32 a_buttonNum;
    UINT32 a_channelNum;
    Gamepad::DPadDirection a_dpadDir;
    bool a_invert;
    Joystick *ap_joystick;
    Gamepad *ap_gamepad;
    DriverStation *ap_ds;
};

#endif  //_WSCONTROLLERBASE_H
