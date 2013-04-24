#ifndef SIMBOT_PRIME_H_
#define SIMBOT_PRIME_H_

#include "DoubleSolenoid.h"
#include "LogitechGamepad.h"
#include "SimLib.h"
#include "SimPID.h"
#include "TrackAPI.h"
#include "WPILib.h"

class SimbotPrime : public IterativeRobot
{
    public:
        SimbotPrime();
        virtual void DisabledPeriodic();
        virtual void TeleopInit();
        virtual void TeleopPeriodic();
        virtual void AutonomousInit();
        virtual void AutonomousPeriodic();

    private:
        // Driver joystick
        Joystick *driveJoystick;

        // Operator gamepad
        LogitechGamepad *operatorPad;

        // Drive motors
        Victor *driveLeftFront;
        Victor *driveLeftBack;
        Victor *driveRightFront;
        Victor *driveRightBack;

        // Arm motors
        Victor *elevator;
        Victor *fourBar;

        // Window motor on arm gripper
        Relay *gripper;

        Compressor *compressor;

        // Andy-Mark two speed transmission
        DoubleSolenoid *shifter;

        // Robot sensors
        Gyro *gyro;  
        AnalogChannel *elevatorPot;
        AnalogChannel *fourbarPot;
        Encoder *leftEncoder;
        Encoder *rightEncoder;

        // Camera
        TrackingThreshold tdata;
        SimPID *cameraYCtrl;
        SimPID *cameraXCtrl;

        // Robot PID controls
        SimPID *driveEncoderCtrl;
        SimPID *driveGyroCtrl;
        SimPID *elevatorCtrl;
        SimPID *fourBarCtrl;

        // Autonomous mode variables
        int autonStep;
        int gripperLoops;
        bool gripperOpening;
};

START_ROBOT_CLASS(SimbotPrime);

#endif // SIMBOT_PRIME_H_
