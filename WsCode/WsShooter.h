//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsShooter.h
//  @ Date : 1/29/2009
//  @ Author : 
//
//


#if !defined(_WSSHOOTER_H)
#define _WSSHOOTER_H

#include <stdio.h>

class WsSc;
class WsDashboard;

class WsShooter
{
public:
    typedef enum
    {
        SHOOTER_STATE_OFF,
        SHOOTER_STATE_IN,
        SHOOTER_STATE_OUT_FAST,
        SHOOTER_STATE_OUT_SLOW,
    } WsShooterStateT;

    WsShooter(WsSc* p_sc);
    float setState(WsShooterStateT state);
protected:
    WsSc* ap_sc;
    float a_shooterSpeedIn;
    float a_shooterSpeedOut;
    float a_shooterSpeedOutSlow;
    WsDashboard* ap_dashboard;
};

#endif  //_WSSHOOTER_H