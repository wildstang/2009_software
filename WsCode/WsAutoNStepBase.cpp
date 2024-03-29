//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang
//  @ File Name : WsAutoSixStepBase.cpp
//  @ Date : 3/12/2009
//  @ Author : 
//
//


#include "Timer.h"
#include "WsAutoNStepBase.h"
#include "WsDriveBaseCrabSingle.h"
#include "WsAccumulator.h"
#include "WsEscalator.h"
#include "WsElevator.h"
#include "WsShooter.h"
#include "WsDriveVector.h"
#include "WsDashboard.h"

WsAutoNStepBase::WsAutoNStepBase()
{
    a_progState = AUTO_STATE_INIT;

    ap_dashboard = WsDashboard::getInstance();
}

WsAutoNStepBase::~WsAutoNStepBase()
{
}

void WsAutoNStepBase::initParams(void)
{
    int i;

    // Attributes for init
    a_initAccumState = WsAccumulator::ACCUM_STATE_IN;
    a_initEscFrontSpeed = WsEscalator::a_escFullUp;
    a_initEscBackSpeed = WsEscalator::a_escFullUp;
    a_initShooterState = WsShooter::SHOOTER_STATE_OFF;
    a_initElevLeftState = WsElevator::ELEVATOR_STATE_OFF;
    a_initElevRightState = WsElevator::ELEVATOR_STATE_OFF;

    // Attributes for init delay
    a_initDelay = 0;

    // Initialize all steps
    for(i = 0; i < MAX_STEPS; i++)
    {
        a_cmdList[i].crabAngle = 0;
        a_cmdList[i].driveVector.a_direction = 0;
        a_cmdList[i].driveVector.a_speed = 0;
        a_cmdList[i].timeout = 0;
    }

    // Attributes for done
    a_doneCrabAngle = 0;
    a_doneAccumState = WsAccumulator::ACCUM_STATE_IN;
    a_doneEscFrontSpeed = WsEscalator::a_escFullUp;
    a_doneEscBackSpeed = WsEscalator::a_escFullUp;
    a_doneShooterState = WsShooter::SHOOTER_STATE_OFF;
    a_doneElevLeftState = WsElevator::ELEVATOR_STATE_OFF;
    a_doneElevRightState = WsElevator::ELEVATOR_STATE_OFF;

    a_currentCmd = 0;
    a_cmdIdx = 0;
}

void WsAutoNStepBase::addStep(const WsAutoNStepCmdT& step)
{
    if(a_cmdIdx < MAX_STEPS)
    {
        a_cmdList[a_cmdIdx].crabAngle = step.crabAngle;
        a_cmdList[a_cmdIdx].driveVector.a_speed = step.driveVector.a_speed;
        a_cmdList[a_cmdIdx].driveVector.a_direction = step.driveVector.a_direction;
        a_cmdList[a_cmdIdx].timeout = step.timeout;
        a_cmdIdx++;
    }
}

bool WsAutoNStepBase::run(void )
{
    bool done = false;
    double time = 0;

    if(ap_driveBase != NULL)
    {
        ap_driveBase->setTractionControlState(true);
    }

    switch(a_progState)
    {
        case AUTO_STATE_INIT:
            if(ap_accumulator != NULL)
            {
                ap_accumulator->setState(a_initAccumState);
            }

            if(ap_escalator != NULL)
            {
                float front, back;
                ap_escalator->setSpeed(a_initEscFrontSpeed, a_initEscBackSpeed, &front, &back);
            }

            if(ap_elevatorLeft != NULL)
            {
                ap_elevatorLeft->setState(a_initElevLeftState);
            }

            if(ap_elevatorRight != NULL)
            {
                ap_elevatorRight->setState(a_initElevRightState);
            }

            if(ap_shooter != NULL)
            {
                ap_shooter->setState(a_initShooterState);
            }

            turnOffDriveBase();

            a_progState = AUTO_STATE_INIT_DELAY;

            break;
        case AUTO_STATE_INIT_DELAY:
            turnOffDriveBase();

            if (delay(a_initDelay, &time) == true)
            {
                a_progState = AUTO_STATE_RUN_CMD;
                a_currentCmd = 0;
            }
            //printf("DELAY %3.3f (%3.3f)\n", time, a_initDelay);
            break;
        case AUTO_STATE_RUN_CMD:
            if(a_currentCmd < MAX_STEPS)
            {
                printf("RUN STATE %d\n", a_currentCmd);
                if(driveByTime(&a_cmdList[a_currentCmd].driveVector,
                               a_cmdList[a_currentCmd].crabAngle,
                               a_cmdList[a_currentCmd].timeout,
                               &time) == true)
                {
                    a_currentCmd++;
                }
            }
            else
            {
                a_progState = AUTO_STATE_DONE;
            }
            break;
        case AUTO_STATE_DONE:
            turnOffDriveBase();
            done = true;
            break;
        default:
            a_progState = AUTO_STATE_DONE;
            break;
    }

    ap_dashboard->setValue(IDX_AUTO_PROGSTATE, (UINT32)a_progState);
    ap_dashboard->setValue(IDX_AUTO_DATA1, (float)time);
    ap_dashboard->setValue(IDX_AUTO_DATA2, (float)a_currentCmd);

    return done;
}

