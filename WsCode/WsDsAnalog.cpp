//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsDsAnalog.cpp
//  @ Date : 2/7/2009
//  @ Author : 
//
//


#include "WsDsAnalog.h"
#include "DriverStation.h"

WsDsAnalog::WsDsAnalog(UINT32 channel)
{
    ap_joystick = NULL;
    ap_gamepad = NULL;
    ap_ds = DriverStation::GetInstance();
    a_axisNum = 0;
    a_buttonNum = 0;
    a_channelNum = channel;
    a_invert = false;
}

UINT32 WsDsAnalog::getValue()
{
    UINT32 value = 0;

    if((ap_ds != NULL) && (a_channelNum != 0))
    {
        value = (UINT32) ap_ds->GetAnalogIn(a_channelNum);
    }

    return value;
}

