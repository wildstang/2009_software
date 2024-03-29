//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsElevator.h
//  @ Date : 1/29/2009
//  @ Author : 
//
//


#if !defined(_WSELEVATOR_H)
#define _WSELEVATOR_H

#include <stdio.h>
#include "Relay.h"

class WsRelay;
class DigitalInput;

class WsElevator
{
public:
    typedef enum
    {
        ELEVATOR_POS_BOTTOM,
        ELEVATOR_POS_TOP,
    } WsElevatorPosT;

    typedef enum
    {
        ELEVATOR_STATE_OFF,
        ELEVATOR_STATE_UP,
        ELEVATOR_STATE_DOWN,
    } WsElevatorStateT;


    WsElevator(WsRelay* p_relay);
    void assignLimitSwitches(DigitalInput* p_topLimit, DigitalInput* p_bottomLimit);
    int moveUp(void );
    int moveDown(void );
    int turnOff(void );
    int setState(WsElevatorStateT state);
    void setUseLimitSwitches(bool state);
    bool moveToPosition(WsElevatorPosT position);
protected:
    UINT32 a_switchPressed;
    UINT32 a_switchNotPressed;
    WsRelay* ap_relay;
    DigitalInput* ap_topSwitch;
    DigitalInput* ap_bottomSwitch;
    Relay::Value a_elevatorOffValue;
    Relay::Value a_elevatorUpValue;
    Relay::Value a_elevatorDownValue;
    bool a_useLimitSwitches;
};

#endif  //_WSELEVATOR_H
