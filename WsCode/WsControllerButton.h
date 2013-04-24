//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControllerButton.h
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#if !defined(_WSCONTROLLERBUTTON_H)
#define _WSCONTROLLERBUTTON_H

#include <stdio.h>
#include "WsControllerBase.h"

class WsControllerButton : public WsControllerBase
{
public:
    WsControllerButton(Joystick* p_js, UINT32 button);
    WsControllerButton(Gamepad* p_pad, UINT32 button);
    WsControllerButton(Gamepad* p_pad, Gamepad::DPadDirection direction);
    WsControllerButton(UINT32 channel);
    virtual ~WsControllerButton();
    virtual bool getState(void );
    virtual bool applyInvert(bool state);
    virtual void resetState(void);
};

#endif  //_WSCONTROLLERBUTTON_H