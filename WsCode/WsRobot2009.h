//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : WsRobot2009.h
//  @ Date : 1/31/2009
//  @ Author : 
//
//


#if !defined(_WSROBOT2009_H)
#define _WSROBOT2009_H

#include <stdio.h>
#include "IterativeRobot.h"


class DriverStationLCD;
class Joystick;
class Gamepad;
class DigitalInput;
class DigitalOutput;
class WsControllerAxis;
class WsControllerPolarStick;
class WsControllerButton;
class SpeedController;
class Relay;
class WsSc;
class WsTractionWheel;
class WsRelay;
class WsPot;
class WsPid;
class WsElevator;
class WsDashboard;
class WsLogger;
class WsCalibration;
class WsControlMethodCrab;
class WsCrabController;
class WsDriveBaseCrabSingle;
class WsMotorManager;
class WsAccumulator;
class WsEscalator;
class WsShooter;
class WsAppendageControl;
class WsEncoderManager;
class WsEncoder;
class WsDsAnalog;
class WsAutonomousMgr;
class WsDriverStationLED;

class WsRobot2009 : public IterativeRobot
{
public:
    void RobotInit(void );
    void DisabledInit(void );
    void AutonomousInit(void );
    void TeleopInit(void );
    void DisabledPeriodic(void );
    void AutonomousPeriodic(void );
    void TeleopPeriodic(void );
    void AutonomousContinuous(void );
    void TeleopContinuous(void );
    void DisabledContinuous(void );
protected:
    typedef enum
    {
      DISCOVER_OFF,
      DISCOVER_FL,
      DISCOVER_FL_DONE,
      DISCOVER_FR,
      DISCOVER_FR_DONE,
      DISCOVER_BL,
      DISCOVER_BL_DONE,
      DISCOVER_BR,
      DISCOVER_DONE,
    } EncoderDiscoveryStateT;

    Gamepad* ap_driveGamepad;
    Gamepad* ap_appendageGamepad;
    WsControllerAxis* ap_driveAxisX;
    WsControllerAxis* ap_driveAxisY;
    WsControllerAxis* ap_crabAxisX;
    WsControllerAxis* ap_crabAxisY;
    WsControllerAxis* ap_elevatorAxisX;
    WsControllerAxis* ap_elevatorAxisY;
    WsControllerAxis* ap_escalatorAxisX;
    WsControllerAxis* ap_escalatorAxisY;
    WsControllerPolarStick* ap_driveStick;
    WsControllerPolarStick* ap_crabStick;
    WsControllerPolarStick* ap_elevatorStick;
    WsControllerPolarStick* ap_escalatorStick;
    WsControllerButton* ap_turboButton;
    WsControllerButton* ap_tractionToggleButton;
    WsControllerButton* ap_crabDisableButton;
    WsControllerButton* ap_crabManualButton;
    WsControllerButton* ap_crabNudgeLeftButton;
    WsControllerButton* ap_crabNudgeRightButton;
    WsControllerButton* ap_shooterOutFastButton;
    WsControllerButton* ap_shooterOutSlowButton;
    WsControllerButton* ap_shooterInButton;
    WsControllerButton* ap_accumulatorOutButton;
    WsControllerButton* ap_accumulatorInButton;
    WsControllerButton* ap_accumLoadButton;
    WsControllerButton* ap_raiseShootLeftButton;
    WsControllerButton* ap_raiseShootBothButton;
    WsControllerButton* ap_raiseShootRightButton;
    WsControllerButton* ap_discoverEncodersButton;
    WsControllerButton* ap_downOutButton;
    WsControllerButton* ap_elevDisableButton;
    WsControllerButton* ap_tractionDisableButton;
    WsControllerButton* ap_extraButton2;
    WsAppendageControl* ap_appendageControl;
    SpeedController* ap_scDriveFL;
    SpeedController* ap_scDriveBL;
    SpeedController* ap_scDriveFR;
    SpeedController* ap_scDriveBR;
    SpeedController* ap_scCrabL;
    SpeedController* ap_scCrabR;
    SpeedController* ap_scAccumulator;
    SpeedController* ap_scEscalatorF;
    SpeedController* ap_scEscalatorB;
    Relay* ap_rlyElevatorL;
    Relay* ap_rlyElevatorR;
    SpeedController* ap_scShooter;
    WsTractionWheel* ap_wScDriveFL;
    WsTractionWheel* ap_wScDriveFR;
    WsTractionWheel* ap_wScDriveBL;
    WsTractionWheel* ap_wScDriveBR;
    WsSc* ap_wScCrabL;
    WsSc* ap_wScCrabR;
    WsSc* ap_wScAccumulator;
    WsSc* ap_wScEscalatorF;
    WsSc* ap_wScEscalatorB;
    WsRelay* ap_wRlyElevatorL;
    WsRelay* ap_wRlyElevatorR;
    WsSc* ap_wScShooter;
    WsPot* ap_crabPot;
    DigitalInput* ap_elevatorLimitRightTop;
    DigitalInput* ap_elevatorLimitRightBottom;
    DigitalInput* ap_elevatorLimitLeftTop;
    DigitalInput* ap_elevatorLimitLeftBottom;
    WsPid* ap_crabPID;
    WsDashboard* ap_dashboard;
    WsLogger* ap_logger;
    WsCalibration* ap_calib;
    WsControllerButton* ap_calibrateEnableButton;
    WsControllerButton* ap_calibrateCrabPotLeftButton;
    WsControllerButton* ap_calibrateCrabPotMidButton;
    WsControllerButton* ap_calibrateCrabPotRightButton;
    WsControlMethodCrab* ap_controlMethodCrab;
    WsCrabController* ap_crabController;
    WsDriveBaseCrabSingle* ap_driveBase;
    WsMotorManager* ap_mmgrDriveBase;
    WsMotorManager* ap_mmgrRobot;
    WsAccumulator* ap_accumulator;
    WsElevator* ap_elevatorL;
    WsElevator* ap_elevatorR;
    WsEscalator* ap_escalator;
    WsShooter* ap_shooter;
    WsEncoderManager* ap_encoderManager;
    WsEncoder* ap_encoderFL;
    WsEncoder* ap_encoderFR;
    WsEncoder* ap_encoderBL;
    WsEncoder* ap_encoderBR;
    WsDsAnalog* ap_autoProgSelector;
    WsDsAnalog* ap_autoPositionSelector;
    WsControllerButton* ap_autoLockinSwitch;
    WsAutonomousMgr* ap_autonMgr;
    int a_continuousLoopCounter;
    DriverStationLCD *ap_dsLcd;
    WsDriverStationLED *ap_dsLockInLed;
    WsDriverStationLED *ap_dsTractionLed;
    WsDriverStationLED *ap_dsLED3;
    WsDriverStationLED *ap_dsLED4;
    DigitalOutput* ap_emptyCellSigLed;
    WsControllerButton* ap_emptyCellSigButton;

    bool a_calibrationMode;
    bool a_crabCalibrationOn;
    bool a_tcState;

    bool processCalibration(void );
    bool discoverEncoders(void );
private:
    ~WsRobot2009();
    void dashboardDisplayInputs(void);
    void dashboardDisplaySensors(void);
    void dashboardDisplayGeneral(void);
    void runOiTest(void);
    void printLcdRegularData(void);
};

START_ROBOT_CLASS(WsRobot2009);

#endif  //_WSROBOT2009_H
