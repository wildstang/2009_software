//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsTractionWheel.cpp
//  @ Date : 2/7/2009
//  @ Author : 
//
//


#include "WsTractionWheel.h"
#include "WsEncoder.h"
#include "WsPid.h"
#include "WsDashboard.h"

WsTractionWheel::WsTractionWheel(SpeedController* p_sc,
                                  WsEncoder* p_encoder,
                                  WheelIndexT wheel):
                 WsSc(p_sc)
{
    ap_encoder = p_encoder;
    a_wheel = wheel;
    //ap_tractionPID = new WsPid(.00080, .00000, 0, 5);
    ap_tractionPID = new WsPid(.00005, .00000, 0, 5);
    a_tractionControlEnabled = true;
    a_lastSpeed = 0;
}

WsTractionWheel::~WsTractionWheel()
{
    delete ap_tractionPID;
    ap_tractionPID = NULL;
}

INT16 WsTractionWheel::GetDrivenWheelSpeed(void)
{
    return a_drivenWheelSpeed;
}

INT16 WsTractionWheel::GetIdlerWheelSpeed(void)
{
    return a_idlerWheelSpeed;
}

INT16 WsTractionWheel::GetSlipRatio(void)
{
    return a_slipRatio;
}

float WsTractionWheel::GetDesOutputSpeed(void)
{
    return a_desOutputSpeed;
}

float WsTractionWheel::GetActOutputSpeed(void)
{
    return a_actOutputSpeed;
}

void WsTractionWheel::SetTractionControlState(bool state)
{
    a_tractionControlEnabled = state;
}

bool WsTractionWheel::ReadEncoders(void)
{
    bool ret = false;

    a_drivenWheelSpeed = 0;
    a_idlerWheelSpeed = 0;
    a_slipRatio = 0;
    a_desOutputSpeed = 0;
    a_actOutputSpeed = 0;

    if ((ap_encoder != NULL) && (ap_encoder->isValid() == true))
    {
      a_drivenWheelSpeed = ap_encoder->getDrivenWheelSpeed();
      a_idlerWheelSpeed = ap_encoder->getIdlerWheelSpeed();
      a_slipRatio = ap_encoder->getSlipRatio();
      ret = true;
    }

    return ret;
}

float WsTractionWheel::Get(void)
{
    return WsSc::Get();
}

void WsTractionWheel::Set(float inSpeed)
{
    float finalSpeed = inSpeed;
    float newSpeed = inSpeed;
    float pidRet = 0;
    float scaledSpeed;
    float accelRate;
    float decelRate;
    float p;


    if (ReadEncoders() == true)
    {
      a_desOutputSpeed = inSpeed;

      if (a_tractionControlEnabled == true)
      {
        scaledSpeed = (float)a_idlerWheelSpeed / 140.0;

        p = .00005;

#define SPEED_1 .125
#define SPEED_2 .5
#define RATE_1  .20
#define RATE_2  .35

        if ((scaledSpeed < SPEED_1) && (scaledSpeed > -SPEED_1))
        {
          accelRate = RATE_1;
        }
        else if ((scaledSpeed < SPEED_2) && (scaledSpeed > -SPEED_2))
        {
          if (scaledSpeed > 0)
          {
            accelRate = RATE_1 + ((scaledSpeed - SPEED_1) *
                                  ((RATE_2 - RATE_1) / (SPEED_2 - SPEED_1)));
          }
          else
          {
            accelRate = RATE_1 + ((-scaledSpeed - SPEED_1) *
                                  ((RATE_2 - RATE_1) / (SPEED_2 - SPEED_1)));
          }
        }
        else
        {
          accelRate = RATE_2;
        }

#define DECEL_SPEED .20
#define DECEL_RATE  .1

        if ((scaledSpeed < DECEL_SPEED) && (scaledSpeed > -DECEL_SPEED))
        {
          float tmpScaledSpeed = scaledSpeed;
          if (scaledSpeed < 0)
          {
            tmpScaledSpeed = -scaledSpeed;
          }

          decelRate =
            ((DECEL_RATE - RATE_1) / (DECEL_SPEED - 0)) * tmpScaledSpeed - RATE_1;
        }
        else
        {
          decelRate = DECEL_RATE;
        }

        /*
        if ((scaledSpeed < .1) && (scaledSpeed > -.1))
        {
          decelRate = .15;
        }
        else if ((scaledSpeed < .2) && (scaledSpeed > -.2))
        {
          decelRate = .20;
        }
        else if ((scaledSpeed < .3) && (scaledSpeed > -.3))
        {
          decelRate = .40;
        }
        else
        {
          decelRate = .50;
        }
        */

        if (scaledSpeed < 0)
        {
          /* scale the .1 with the speed, i think */
          decelRate = -scaledSpeed + .1;
        }
        else
        {
          decelRate = scaledSpeed + .1;
        }

        if (a_debug == true)
          printf("%.3f %.3f ", accelRate, decelRate);


        /* default to moving at inSpeed so I don't need 10 else cases that set
           newSpeed to inSpeed */
        newSpeed = inSpeed;

        if (scaledSpeed == 0)
        {
          /* stopped */
          if (inSpeed > scaledSpeed)
          {
            /* trying to accelerate forward */
            if (inSpeed > (scaledSpeed + accelRate))
            {
              /* trying to accelerate too fast, scale it back */
              newSpeed = scaledSpeed + accelRate;
            }
          }
          else if (inSpeed < scaledSpeed)
          {
            /* trying to accelerate backward */
            if (inSpeed < (scaledSpeed - accelRate))
            {
              /* trying to accelerate too fast, scale it back */
              newSpeed = scaledSpeed - accelRate;
            }
          }
        }
        else if (scaledSpeed > 0)
        {
          /* moving forward */
          if (inSpeed > scaledSpeed)
          {
            /* moving forward & accelerating */
            if (inSpeed > (scaledSpeed + accelRate))
            {
              /* trying to accelerate too fast, scale it back */
              newSpeed = scaledSpeed + accelRate;
            }
          }
          else if (inSpeed < scaledSpeed)
          {
            /* moving forward & decelerating */
            if (inSpeed < (scaledSpeed - decelRate))
            {
              /* trying to slow down too fast, scale it back */
              newSpeed = scaledSpeed - decelRate;
              //newSpeed = -.1;
            }
          }
        }
        else if (scaledSpeed < 0)
        {
          /* moving backward */
          if (inSpeed < scaledSpeed)
          {
            /* moving backward & accelerating */
            if (inSpeed < (scaledSpeed - accelRate))
            {
              /* trying to accelerate too fast, scale it back */
              newSpeed = scaledSpeed - accelRate;
            }
          }
          else if (inSpeed > scaledSpeed)
          {
            /* moving backward & decelerating */
            if (inSpeed > (scaledSpeed + decelRate))
            {
              /* trying to decelerate too fast, scale it back */
              newSpeed = scaledSpeed + decelRate;
              //newSpeed = .1;
            }
          }
        }

        /*
        ap_tractionPID->setConstants(p, 0, 0);
        ap_tractionPID->setDesiredValue(0);
        pidRet = ap_tractionPID->calcPid(a_slipRatio);
        */

        if (newSpeed > 0)
        {
          finalSpeed = newSpeed + pidRet;
        }
        else
        {
          finalSpeed = newSpeed - pidRet;
        }

        a_actOutputSpeed = finalSpeed;

        if (a_debug == true)
        {
          printf("%d v %d dw %5d iw %5d sr %5d ss %.3f s %.3f "
              "ns %.3f fs %.3f\n", ap_encoder->getAddress(),
              ap_encoder->isValid(), a_drivenWheelSpeed, a_idlerWheelSpeed,
              a_slipRatio, scaledSpeed, inSpeed, newSpeed, finalSpeed);
        }
      }
    }

    WsSc::Set(finalSpeed);
}

