//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsControllerStickyButton.cpp
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#include "WsControllerStickyButton.h"
#include "Joystick.h"
#include "Gamepad.h"

WsControllerStickyButton::WsControllerStickyButton(Joystick* p_js, UINT32 button) :
                          WsControllerButton(p_js, button)
{
    resetState();
}

WsControllerStickyButton::WsControllerStickyButton(Gamepad* p_pad, UINT32 button) :
                          WsControllerButton(p_pad, button)
{
    resetState();
}

WsControllerStickyButton::~WsControllerStickyButton()
{
}

void WsControllerStickyButton::resetState(void)
{
    a_statePrev = false;
    a_stickyState = false;
}

bool WsControllerStickyButton::getState(void )
{
    bool stateCurr;
    stateCurr = WsControllerButton::getState();
    if((a_statePrev == false) && (stateCurr == true))
    {
        a_stickyState = !a_stickyState;
    }
    a_statePrev = stateCurr;

    return a_stickyState;
}

