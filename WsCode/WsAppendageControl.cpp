//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsAppendageControl.cpp
//  @ Date : 1/31/2009
//  @ Author : 
//
//


#include "WsAppendageControl.h"
#include "WsControllerButton.h"
#include "WsControllerPolarStick.h"
#include "WsAccumulator.h"
#include "WsElevator.h"
#include "WsEscalator.h"
#include "WsDashboard.h"
#include "WsTrig.h"

#define SHOOT_COUNT_THRESH 5

WsAppendageControl::WsAppendageControl()
{
    ap_elevatorStick = NULL;
    ap_elevatorDisableButton = NULL;
    ap_escalatorStick = NULL;
    ap_shootOutFastButton = NULL;
    ap_shootOutSlowButton = NULL;
    ap_shootInButton = NULL;
    ap_accumInButton = NULL;
    ap_accumOutButton = NULL;
    ap_accumLoadButton = NULL;
    ap_raiseShootLeftButton = NULL;
    ap_raiseShootBothButton = NULL;
    ap_raiseShootRightButton = NULL;
    a_escLoadSpeed = WsEscalator::a_escFullUp;

    ap_dashboard = WsDashboard::getInstance();
}

void WsAppendageControl::assignElevatorStick(WsControllerPolarStick* p_stick)
{
    ap_elevatorStick = p_stick;
}

void WsAppendageControl::assignElevatorDisableButton(WsControllerButton* p_button)
{
    ap_elevatorDisableButton = p_button;
}

void WsAppendageControl::assignEscalatorStick(WsControllerPolarStick* p_stick)
{
    ap_escalatorStick = p_stick;
}

void WsAppendageControl::assignAccumulatorButtons(WsControllerButton* p_in, WsControllerButton* p_out)
{
    ap_accumInButton = p_in;
    ap_accumOutButton = p_out;
}

void WsAppendageControl::assignShooterButtons(WsControllerButton* p_in, WsControllerButton* p_outFast, WsControllerButton* p_outSlow)
{
    ap_shootInButton = p_in;
    ap_shootOutFastButton = p_outFast;
    ap_shootOutSlowButton = p_outSlow;
}

void WsAppendageControl::assignAccumLoadButton(WsControllerButton* p_button)
{
    ap_accumLoadButton = p_button;
}

void WsAppendageControl::assignRaiseShootLeftButton(WsControllerButton* p_button)
{
    ap_raiseShootLeftButton = p_button;
}

void WsAppendageControl::assignRaiseShootBothButton(WsControllerButton* p_button)
{
    ap_raiseShootBothButton = p_button;
}

void WsAppendageControl::assignRaiseShootRightButton(WsControllerButton* p_button)
{
    ap_raiseShootRightButton = p_button;
}

void WsAppendageControl::assignDownOutButton(WsControllerButton* p_button)
{
    ap_downOutButton = p_button;
}

WsAccumulator::WsAccumulatorStateT WsAppendageControl::getAccumulatorCommand(void)
{
    WsAccumulator::WsAccumulatorStateT state = WsAccumulator::ACCUM_STATE_OFF;
    bool inState = false;
    bool outState = false;
    bool accumLoadState = false;
    bool downOutState = false;

    if (ap_accumInButton != NULL)
    {
        inState = ap_accumInButton->getState();
    }

    if (ap_accumOutButton != NULL)
    {
        outState = ap_accumOutButton->getState();
    }

    if (ap_accumLoadButton != NULL)
    {
        accumLoadState = ap_accumLoadButton->getState();
    }

    if (ap_downOutButton != NULL)
    {
        downOutState = ap_downOutButton->getState();
    }

    if ((outState == true) || (downOutState == true))
    {
        state = WsAccumulator::ACCUM_STATE_OUT;
    }
    else if ((inState == true) || (accumLoadState == true))
    {
        state = WsAccumulator::ACCUM_STATE_IN;
    }
    else
    {
        state = WsAccumulator::ACCUM_STATE_OFF;
    }

    ap_dashboard->setValue(IDX_IN_ACCUM_IN, inState);
    ap_dashboard->setValue(IDX_IN_ACCUM_OUT, outState);
    ap_dashboard->setValue(IDX_IN_ACCUM_LOAD, accumLoadState);
    ap_dashboard->setValue(IDX_IN_DOWN_OUT, downOutState);

    return state;
}

void WsAppendageControl::getEscalatorSpeeds(float* frontSpeed, float* backSpeed)
{
  float angle = 0;
  float radius = 0;
  float x = 0;
  float y = 0;
  float a_minEscRadius = 0.5;
  bool accumLoadState = false;
  bool downOutState = false;
  bool shootOutSlowState = false;
  bool shootOutFastState = false;
  bool shootInState = false;
  bool raiseShootLeftState = false;
  bool raiseShootRightState = false;
  bool raiseShootBothState = false;

  static float front = 0;
  static float back = 0;

  if(ap_escalatorStick != NULL)
  {
      x = ap_escalatorStick->getX();
      y = ap_escalatorStick->getY();
      angle = ap_escalatorStick->getAngle();
      radius = ap_escalatorStick->getRadius();
  }

  if(ap_accumLoadButton != NULL)
  {
      accumLoadState = ap_accumLoadButton->getState();
  }

  if(ap_downOutButton != NULL)
  {
      downOutState = ap_downOutButton->getState();
  }

  if(ap_shootOutSlowButton != NULL)
  {
      shootOutSlowState = ap_shootOutSlowButton->getState();
  }

  if(ap_shootOutFastButton != NULL)
  {
      shootOutFastState = ap_shootOutFastButton->getState();
  }

  if(ap_shootInButton != NULL)
  {
      shootInState = ap_shootInButton->getState();
  }

  if(ap_raiseShootLeftButton != NULL)
  {
      raiseShootLeftState = ap_raiseShootLeftButton->getState();
  }

  if(ap_raiseShootRightButton != NULL)
  {
      raiseShootRightState = ap_raiseShootRightButton->getState();
  }

  if(ap_raiseShootRightButton != NULL)
  {
      raiseShootBothState = ap_raiseShootBothButton->getState();
  }

  if(radius > a_minEscRadius)
  {
      front = (radius * (COSDEG(angle) + SINDEG(angle)));
      back = (radius * (COSDEG(angle) - SINDEG(angle)));

      if (front > 1)
      {
          front = 1;
      }
      else if (front < -1)
      {
          front = -1;
      }
      if (back > 1)
      {
          back = 1;
      }
      else if (back < -1)
      {
          back = -1;
      }
  }
  else if (downOutState == true)
  {
      front = -a_escLoadSpeed;
      back = -a_escLoadSpeed;
  }
  else if (shootInState == true)
  {
      front = -a_escLoadSpeed;
      back = a_escLoadSpeed;
  }
  else if ((accumLoadState == true))
  {
      front = a_escLoadSpeed;
      back = a_escLoadSpeed;
  }
  else if ((shootOutFastState == true) ||
           (shootOutSlowState == true) || (raiseShootLeftState == true) ||
           (raiseShootRightState == true) || (raiseShootBothState == true))
  {
      front = a_escLoadSpeed;
      back = -a_escLoadSpeed;
  }
  else
  {
      front = 0;
      back = 0;
  }

  *frontSpeed = front;
  *backSpeed = back;

  ap_dashboard->setValue(IDX_IN_ESC_X, x);
  ap_dashboard->setValue(IDX_IN_ESC_Y, y);
  ap_dashboard->setValue(IDX_IN_ESC_RADIUS, radius);
  ap_dashboard->setValue(IDX_IN_ESC_ANGLE, angle);
}

WsElevator::WsElevatorStateT WsAppendageControl::getLeftElevatorCommand(void )
{
  float angle = 0;
  float radius = 0;
  float x = 0;
  float y = 0;
  bool raiseShootLeftState = false;
  bool raiseShootBothState = false;

  WsElevator::WsElevatorStateT command = WsElevator::ELEVATOR_STATE_OFF;

  if(ap_raiseShootLeftButton != NULL)
  {
      raiseShootLeftState = ap_raiseShootLeftButton->getState();
  }

  if(ap_raiseShootBothButton != NULL)
  {
      raiseShootBothState = ap_raiseShootBothButton->getState();
  }

  if(ap_elevatorStick != NULL)
  {
      x = ap_elevatorStick->getX();
      y = ap_elevatorStick->getY();
      angle = ap_elevatorStick->getAngle();
      radius = ap_elevatorStick->getRadius();
  }

  if((raiseShootLeftState == true) || (raiseShootBothState == true))
  {
    command = WsElevator::ELEVATOR_STATE_UP;
  }
  else if(radius < 0.8)
  {
    command = WsElevator::ELEVATOR_STATE_OFF;
  }
  else if((angle <= 20) && (angle >= -70))
  {
    command = WsElevator::ELEVATOR_STATE_UP;
  }
  else if(((angle <= -110) && (angle >= -180)) ||
          ((angle >= 160) && (angle <= 180)))
  {
    command = WsElevator::ELEVATOR_STATE_DOWN;
  }

  ap_dashboard->setValue(IDX_IN_ELEV_X, x);
  ap_dashboard->setValue(IDX_IN_ELEV_Y, y);
  ap_dashboard->setValue(IDX_IN_ELEV_RADIUS, radius);
  ap_dashboard->setValue(IDX_IN_ELEV_ANGLE, angle);
  ap_dashboard->setValue(IDX_IN_RAISE_SHOOT_LEFT, raiseShootLeftState);
  ap_dashboard->setValue(IDX_IN_RAISE_SHOOT_BOTH, raiseShootBothState);

  return command;
}

WsElevator::WsElevatorStateT WsAppendageControl::getRightElevatorCommand(void )
{
  float angle = ap_elevatorStick->getAngle();
  float radius = ap_elevatorStick->getRadius();
  bool raiseShootRightState = false;
  bool raiseShootBothState = false;

  WsElevator::WsElevatorStateT command = WsElevator::ELEVATOR_STATE_OFF;

  if(ap_raiseShootRightButton != NULL)
  {
      raiseShootRightState = ap_raiseShootRightButton->getState();
  }

  if(ap_raiseShootBothButton != NULL)
  {
      raiseShootBothState = ap_raiseShootBothButton->getState();
  }

  if((raiseShootRightState == true) || (raiseShootBothState == true))
  {
    command = WsElevator::ELEVATOR_STATE_UP;
  }
  else if(radius < 0.8)
  {
    command = WsElevator::ELEVATOR_STATE_OFF;
  }
  else if((angle <= 70) && (angle >= -20))
  {
    command = WsElevator::ELEVATOR_STATE_UP;
  }
  else if(((angle <= -160) && (angle >= -180)) ||
          ((angle >= 110) && (angle <= 180)))
  {
    command = WsElevator::ELEVATOR_STATE_DOWN;
  }
  ap_dashboard->setValue(IDX_IN_RAISE_SHOOT_RIGHT, raiseShootRightState);

  return command;
}

WsShooter::WsShooterStateT WsAppendageControl::getShooterCommand(void)
{
    WsShooter::WsShooterStateT state = WsShooter::SHOOTER_STATE_OFF;

    if ((ap_raiseShootLeftButton != NULL) && (ap_raiseShootRightButton != NULL) &&
        (ap_raiseShootBothButton != NULL) && (ap_shootOutSlowButton != NULL) &&
        (ap_shootOutFastButton != NULL) && (ap_shootInButton != NULL) &&
        (ap_accumLoadButton != NULL))
    {
        if (ap_shootInButton->getState() == true)
        {
            state = WsShooter::SHOOTER_STATE_IN;
            ap_dashboard->setValue(IDX_IN_SHOOT_IN, true);
        }
        else if (ap_shootOutFastButton->getState() == true)
        {
            state = WsShooter::SHOOTER_STATE_OUT_FAST;
            ap_dashboard->setValue(IDX_IN_SHOOT_OUT, true);
        }
        else if ((ap_raiseShootLeftButton->getState() == true) || (ap_raiseShootRightButton->getState() == true) ||
                (ap_raiseShootBothButton->getState() == true) || (ap_shootOutSlowButton->getState() == true))
        {
            state = WsShooter::SHOOTER_STATE_OUT_SLOW;
            ap_dashboard->setValue(IDX_IN_SHOOT_OUT_SLOW, true);
        }
        else if (ap_accumLoadButton->getState() == true)
        {
            state = WsShooter::SHOOTER_STATE_IN;
            ap_dashboard->setValue(IDX_IN_SHOOT_IN, true);
        }
        else
        {
            state = WsShooter::SHOOTER_STATE_OFF;
        }
    }

    return state;
}

