//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsShmEncoder.cpp
//  @ Date : 2/13/2009
//  @ Author : 
//
//


#include <semLib.h>
#include <errno.h>

#include "WsShmEncoder.h"
#include "WsEncoderTask.h"

WsShmEncoder::WsShmEncoder(UINT8 addr, bool invert) :
    WsEncoder(addr)
{
  a_invert = invert;
}

WsShmEncoder::~WsShmEncoder()
{

}

bool WsShmEncoder::isValid(void )
{
  bool valid = false;
  int status;

  status = semTake(g_encoderSemaphore, kTimeout);

  if (status == OK)
  {
    if ((g_encoderData.validConfig == true) &&
        (g_encoderData.encoderData[a_addr].valid == true))
    {
      valid = true;
    }
    semGive(g_encoderSemaphore);
  }

  return valid;
}

INT16 WsShmEncoder::getDrivenWheelSpeed(void )
{
  int status;
  INT16 wheelSpeed = 0;

  status = semTake(g_encoderSemaphore, kTimeout);

  if (status == OK)
  {
    wheelSpeed = g_encoderData.encoderData[a_addr].drivenWheelSpeed;
    semGive(g_encoderSemaphore);

    if (a_invert == true)
    {
      wheelSpeed = -wheelSpeed;
    }
  }
  else
  {
    printf("problem taking semaphore: %s (%d)\n", strerror(errno), errno);
  }

  return wheelSpeed;
}

INT16 WsShmEncoder::getIdlerWheelSpeed(void )
{
  int status;
  INT16 wheelSpeed = 0;

  status = semTake(g_encoderSemaphore, kTimeout);

  if (status == OK)
  {
    wheelSpeed = g_encoderData.encoderData[a_addr].idlerWheelSpeed;
    semGive(g_encoderSemaphore);

    if (a_invert == true)
    {
      wheelSpeed = -wheelSpeed;
    }
  }
  else
  {
    printf("problem taking semaphore: %s (%d)\n", strerror(errno), errno);
  }

  return wheelSpeed;
}

INT16 WsShmEncoder::getSpeedDiff(void )
{
  int status;
  INT16 speedDiff = 0;

  status = semTake(g_encoderSemaphore, kTimeout);

  if (status == OK)
  {
    speedDiff = g_encoderData.encoderData[a_addr].speedDiff;
    semGive(g_encoderSemaphore);

    if (a_invert == true)
    {
      speedDiff = -speedDiff;
    }
  }
  else
  {
    printf("problem taking semaphore: %s (%d)\n", strerror(errno), errno);
  }

  return speedDiff;
}

INT16 WsShmEncoder::getSlipRatio(void )
{
  int status;
  INT16 slipRatio = 0;

  status = semTake(g_encoderSemaphore, kTimeout);
  if (status == OK)
  {
    slipRatio = g_encoderData.encoderData[a_addr].slipRatio;
    semGive(g_encoderSemaphore);
  }
  else
  {
    printf("problem taking semaphore: %s (%d)\n", strerror(errno), errno);
  }

  return slipRatio;
}

