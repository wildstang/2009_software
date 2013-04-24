//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsCrabController.h
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#if !defined(_WSCRABCONTROLLER_H)
#define _WSCRABCONTROLLER_H

#include <stdio.h>

class WsCalibration;
class WsSc;
class WsPid;
class WsDashboard;
class WsPot;

#define CRAB_ANGLE_MAX  90
#define CRAB_ANGLE_MIN  -90

class WsCrabController
{
public:
    WsCrabController(WsSc* p_sc, WsPot* p_pot);
    WsCrabController(WsSc* p_scL, WsSc* p_scR, WsPot* p_pot);
    virtual ~WsCrabController();
    void assignPid(WsPid* p_pid);
    void setOutputSpeed(float speed);
    void setAngle(float angle);
protected:
    UINT32 convertDegToPot(float angle);

    WsPid* ap_pid;
    WsCalibration* ap_calib;
    WsPot* ap_crabPot;
    WsSc* ap_crabScLeft;
    WsSc* ap_crabScRight;
    WsDashboard* ap_dashboard;
};

#endif  //_WSCRABCONTROLLER_H