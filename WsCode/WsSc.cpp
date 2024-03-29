//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsSc.cpp
//  @ Date : 1/14/2009
//  @ Author : 
//
//


#include "WsSc.h"
#include "WsOutput.h"
#include "SpeedController.h"
#include "WsDashboard.h"

WsSc::WsSc(SpeedController* p_sc)
{
    ap_sc = p_sc;
    a_debug = false;
    ap_dashboard = WsDashboard::getInstance();
}

WsSc::~WsSc()
{
}

float WsSc::Get(void)
{
    if(a_enabled == true)
    {
        return ap_sc->Get();
    }
    else
    {
        return 0;
    }
}


void WsSc::Set(float speed)
{
    if(a_enabled == true)
    {
        ap_sc->Set(speed);
    }
    else
    {
        ap_sc->Set(0);
    }
}
