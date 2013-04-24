//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsAccumulator.h
//  @ Date : 1/29/2009
//  @ Author : 
//
//


#if !defined(_WSACCUMULATOR_H)
#define _WSACCUMULATOR_H

#include <stdio.h>

class WsSc;
class WsDashboard;

class WsAccumulator
{
public:

    typedef enum
    {
        ACCUM_STATE_OFF = 0,
        ACCUM_STATE_IN,
        ACCUM_STATE_OUT,
    } WsAccumulatorStateT;

    WsAccumulator(WsSc* p_sc);
    ~WsAccumulator();
    float setState(WsAccumulatorStateT state);
protected:
    WsSc* ap_sc;
    float a_accumSpeedIn;
    float a_accumSpeedOut;

    WsDashboard* ap_dashboard;
};

#endif  //_WSACCUMULATOR_H