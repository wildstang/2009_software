
#include <stdio.h>
#include <semLib.h>

#include "WsEncoderTask.h"
#include "Timer.h"
#include "DigitalModule.h"
#include "WsI2cEncoder.h"
#include "WsCalibration.h"

#define WHEEL_SPEED_DIFF 100
#define MAX_BAD_DATA_LOOPS 3

SEM_ID g_encoderSemaphore;
SharedEncoderDataT g_encoderData;
int g_encoderTaskPrintEnable = 0;

/* create a new WsI2cEncoder instance for the address passed in and return the
   instance if it is valid, otherwise return NULL. */
WsI2cEncoder *getValidEncoder(UINT8 address)
{
  int retries = 0;
  WsI2cEncoder *encoder = NULL;

  printf("trying address %d\n", address);
  if ((address > 0) && (address <= MAX_ENCODER_ADDRESS))
  {
    while (retries < 5)
    {
      encoder = new WsI2cEncoder(ENCODER_SLOT_NUM, address);

      if (encoder->isValid())
      {
        return encoder;
      }

      delete encoder;
      encoder = NULL;
      retries++;
    }
  }

  return NULL;
}


int encoder_task_main()
{
  int status;
  WsCalibration *p_calib;
  WsI2cEncoder *foundEncoders[ENCODER_DATA_SIZE];
  WsI2cEncoder *encoder = NULL;
  int numMatchedEncoders = 0;
  UINT8 address;
  bool keepGoing = true;
  INT16 drivenWheelSpeed;
  INT16 idlerWheelSpeed;
  INT16 speedDiff;
  INT16 slipRatio;
  static int badDataCountDriven[ENCODER_DATA_SIZE];
  static int badDataCountIdler[ENCODER_DATA_SIZE];

  /* try to connect to all the addresses & mark the addresses that were found
     as valid encoders */
  for (address = 1; address <= MAX_ENCODER_ADDRESS; address++)
  {
    encoder = getValidEncoder(address);

    semTake(g_encoderSemaphore, WAIT_FOREVER);
    if (encoder != NULL)
    {
      printf("-- found encoder %d\n", address);
      foundEncoders[address] = encoder;
      g_encoderData.encoderData[address].valid = true;
    }
    else
    {
      foundEncoders[address] = NULL;
      g_encoderData.encoderData[address].valid = false;
    }
    semGive(g_encoderSemaphore);
  }

  /* count the number of calibrated addresses that were found */
  p_calib = WsCalibration::getInstance();

  for (address = 1; address <= MAX_ENCODER_ADDRESS; address++)
  {
    if ((foundEncoders[address] != NULL) &&
        ((address == p_calib->getValue(WsCalibration::ENCODER_FL)) ||
         (address == p_calib->getValue(WsCalibration::ENCODER_FR)) ||
         (address == p_calib->getValue(WsCalibration::ENCODER_BL)) ||
         (address == p_calib->getValue(WsCalibration::ENCODER_BR))))
    {
      numMatchedEncoders++;
    }
  }

#define HACK 0
#if HACK
  numMatchedEncoders = NUM_WHEELS;
#endif

  /* mark valid or invalid based on encoder count */
  semTake(g_encoderSemaphore, WAIT_FOREVER);
  if (numMatchedEncoders == NUM_WHEELS)
  {
    g_encoderData.validConfig = true;
    printf("Valid configuration\n");
  }
  else
  {
    g_encoderData.validConfig = false;
    printf("Invalid configuration\n");
  }
  semGive(g_encoderSemaphore);

  memset(badDataCountDriven, 0, sizeof(badDataCountDriven));
  memset(badDataCountIdler, 0, sizeof(badDataCountIdler));

  /* loop fooooooorrrrrrreeeeeevvvvvveeeeerrrrrrr */
  while (keepGoing == true)
  {
    for (address = 1; address <= MAX_ENCODER_ADDRESS; address++)
    {
      encoder = foundEncoders[address];
      if (encoder != NULL)
      {
        /* get info from each encoder */
        drivenWheelSpeed = encoder->getDrivenWheelSpeed();
        idlerWheelSpeed = encoder->getIdlerWheelSpeed();
        speedDiff = encoder->getSpeedDiff();
        slipRatio = encoder->getSlipRatio();
        address = encoder->getAddress();

        if (g_encoderTaskPrintEnable == 1)
        {
          printf("%d dw %5d iw %5d sd %5d sr %5d\n", address, drivenWheelSpeed,
              idlerWheelSpeed, speedDiff, slipRatio);
        }

        status = semTake(g_encoderSemaphore, WAIT_FOREVER);
        if (status == OK)
        {
          if ((drivenWheelSpeed <
               (g_encoderData.encoderData[address].drivenWheelSpeed +
                WHEEL_SPEED_DIFF)) &&
              (drivenWheelSpeed >
               (g_encoderData.encoderData[address].drivenWheelSpeed -
                WHEEL_SPEED_DIFF)))
          {
            /* speed didn't jump by too much, it's probably not bogus */
            g_encoderData.encoderData[address].drivenWheelSpeed =
              drivenWheelSpeed;
            badDataCountDriven[address] = 0;
          }
          else if (badDataCountDriven[address] > MAX_BAD_DATA_LOOPS)
          {
            /* we've received the bad data for a while, it may actually be good
               data, so we'll allow it */
            g_encoderData.encoderData[address].drivenWheelSpeed =
              drivenWheelSpeed;
            badDataCountDriven[address] = 0;
          }
          else
          {
            /* we just started getting bad data, keep the old data and
               increment the bad data counter */
            badDataCountDriven[address]++;
          }

          if ((idlerWheelSpeed <
               (g_encoderData.encoderData[address].idlerWheelSpeed +
                WHEEL_SPEED_DIFF)) &&
              (idlerWheelSpeed >
               (g_encoderData.encoderData[address].idlerWheelSpeed -
                WHEEL_SPEED_DIFF)))
          {
            /* speed didn't jump by too much, it's probably not bogus */
            g_encoderData.encoderData[address].idlerWheelSpeed =
              idlerWheelSpeed;
            badDataCountIdler[address] = 0;
          }
          else if (badDataCountIdler[address] > MAX_BAD_DATA_LOOPS)
          {
            /* we've received the bad data for a while, it may actually be good
               data, so we'll allow it */
            g_encoderData.encoderData[address].idlerWheelSpeed =
              idlerWheelSpeed;
            badDataCountIdler[address] = 0;
          }
          else
          {
            /* we just started getting bad data, keep the old data and
               increment the bad data counter */
            badDataCountIdler[address]++;
          }

          g_encoderData.encoderData[address].speedDiff = speedDiff;
          g_encoderData.encoderData[address].slipRatio = slipRatio;

          semGive(g_encoderSemaphore);
        }
        else
        {
          printf("problem taking semaphore: %s (%d)\n", strerror(errno), errno);
        }
      }
    }
  }

  return 0;
}

