//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControllerAnalogButton.h
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#if !defined(_WSCONTROLLERANALOGBUTTON_H)
#define _WSCONTROLLERANALOGBUTTON_H

#include <stdio.h>
#include "WsControllerButton.h"

class WsControllerAnalogButton : public WsControllerButton
{
public:
    WsControllerAnalogButton(Joystick* p_js, UINT32 axis, float thresh, bool aboveOn);
    virtual ~WsControllerAnalogButton();
    virtual bool getState(void );
protected:
    float a_threshold;
    bool a_aboveOn;
};

#endif  //_WSCONTROLLERANALOGBUTTON_H
