#include "SimbotPrime.h"

#include "AxisCamera.h"
#include "FrcError.h"

// Camera tracking target size parameters
#define MIN_PARTICLE_TO_IMAGE_PERCENT 0.25
#define MAX_PARTICLE_TO_IMAGE_PERCENT 10.0

SimbotPrime::SimbotPrime()
{
    driveJoystick = new Joystick(1); // USB port 1
    operatorPad = new LogitechGamepad(2);  // USB port 2

    driveLeftFront = new Victor(1); // PWM 1
    driveLeftBack = new Victor(2); // PWM 2
    driveRightFront = new Victor(3); // PWM 3
    driveRightBack = new Victor(4); // PWM 4

    elevator = new Victor(5); // PWM 5
    fourBar = new Victor(6); // PWM 6

    // Initialize all motors to neutral.
    // NOTE: If not initialized, they will blink even when enabled.
    driveLeftFront->Set(0);
    driveLeftBack->Set(0);
    driveRightFront->Set(0);
    driveRightBack->Set(0);
    elevator->Set(0);
    fourBar->Set(0);

    gripper = new Relay(1); // Relay 1

    // Pressure sensor in digital I/O 1, compressor on relay 2
    compressor = new Compressor(1, 2);
    compressor->Start();

    // Double solenoid in ports 1 and 2
    shifter = new DoubleSolenoid(1, 2);

    // Start in low gear.
    shifter->Set(DoubleSolenoid::kOnA);

    gyro = new Gyro(1); // Analog port 1
    gyro->SetSensitivity(0.0122); // ADXRS150

    elevatorPot = new AnalogChannel(2); // Analog port 2
    fourbarPot = new AnalogChannel(3); // Analog port 3

    // A-channel on digital I/O 11, B on digital I/O 12
    leftEncoder = new Encoder(11, 12, true);
    // A-channel on digital I/O 13, B on digital I/O 14
    rightEncoder = new Encoder(13, 14);

    leftEncoder->Start();
    rightEncoder->Start();


    // Set up PID controls.
    cameraYCtrl = new SimPID(0.0, 0.0, 0.0);
    cameraXCtrl = new SimPID(0.0, 0.0, 0.0);
    driveEncoderCtrl = new SimPID(0.0, 0.0, 0.0);
    driveGyroCtrl = new SimPID(0.0, 0.0, 0.0);
    elevatorCtrl = new SimPID(0.0, 0.0, 0.0);
    fourBarCtrl = new SimPID(0.0, 0.0, 0.0);

    // Start the camera.
    if (StartCameraTask(10, 0, k160x120, ROT_0) == -1)
    {
        printf("Failed to spawn camera task: %s\n",
                GetVisionErrorText(GetLastVisionError()));
    }

    // Set up camera tracking parameters.
    tdata = GetTrackingData(GREEN, PASSIVE_LIGHT);
    tdata.hue.minValue = 67;
    tdata.hue.maxValue = 114;
    tdata.saturation.minValue = 161;
    tdata.saturation.maxValue = 255;
    tdata.luminance.minValue = 24;
    tdata.luminance.maxValue = 101;

    // Require the watchdog to be fed every 100 ms.
    GetWatchdog().SetExpiration(100);
}

/**
 * Runs periodically while the robot is disabled.
 */
void SimbotPrime::DisabledPeriodic()
{
    GetWatchdog().Feed();

    // Look for the green light while disabled and printf the result.
    ParticleAnalysisReport par;
    if (FindColor(IMAQ_HSL, &tdata.hue, &tdata.saturation, &tdata.luminance, &par)
            && par.particleToImagePercent < MAX_PARTICLE_TO_IMAGE_PERCENT
            && par.particleToImagePercent > MIN_PARTICLE_TO_IMAGE_PERCENT) 
    {
        int lightX = (int)(par.center_mass_x_normalized * 1000.0);
        int lightY = (int)(par.center_mass_y_normalized * 1000.0);
        printf("(Disabled) Light found: x: %i y: %i\n", lightX, lightY);
    } 
    else 
    {
        printf("(Disabled) Light NOT found\n");
    }
}

/**
 * Initializes all motors to neutral to begin teleop.
 * NOTE: This is important to prevent motors from retaining values from
 * autonomous.
 */
void SimbotPrime::TeleopInit()
{
    driveLeftFront->Set(0);
    driveLeftBack->Set(0);
    driveRightFront->Set(0);
    driveRightBack->Set(0);

    elevator->Set(0);
    fourBar->Set(0);
}

/**
 * Runs periodically during teleoperated mode.
 * Maps joystick and gamepad input to motor output. 
 */
void SimbotPrime::TeleopPeriodic()
{
    GetWatchdog().Feed();

    // Retrieve and square the joystick values to desensitize them.
    float x = SimLib::signSquare(driveJoystick->GetX());
    float y = SimLib::signSquare(driveJoystick->GetY());

    // Calculate motor outputs for arcade drive.
    float left = SimLib::limitOutput(y - x);
    float right = -SimLib::limitOutput(y + x);  // Right side is inverted

    driveLeftFront->Set(left);
    driveLeftBack->Set(left);
    driveRightFront->Set(right);
    driveRightBack->Set(right);

    // Elevator control
    if(operatorPad->GetNumberedButton(4))
    {
        // Go to a preset position.
        elevatorCtrl->setDesiredValue(550);
        elevatorCtrl->setConstants(0.004, 0.0001, 0.001);
        elevator->Set(elevatorCtrl->calcPID(elevatorPot->GetAverageValue()));
    }
    else
    {
        // Control the elevator directly with the left Y-axis.
        elevator->Set(SimLib::signSquare(operatorPad->GetLeftY()));
    }

    // Four-bar control
    if (operatorPad->GetNumberedButton(2))
    {
        // Go to a preset position.
        fourBarCtrl->setDesiredValue(400);
        fourBarCtrl->setConstants(0.006, 0.007, 0.008);
        fourBar->Set(-fourBarCtrl->calcPID(fourbarPot->GetAverageValue()));
    }
    else
    {
        // Control the four-bar directly with the right Y-axis.
        fourBar->Set(SimLib::signSquare(operatorPad->GetRightY()));
    }

    if(operatorPad->GetNumberedButton(6)) {
        // Open gripper.
        gripper->Set(Relay::kForward);
    }
    else if(operatorPad->GetNumberedButton(8)) {
        // Close gripper.
        gripper->Set(Relay::kReverse);
    }
    else 
    {
        // Don't move gripper.
        gripper->Set(Relay::kOff);
    }

    // Set the shifter speed according to the buttons on the joystick base.
    if (driveJoystick->GetRawButton(7))
    {
        shifter->Set(DoubleSolenoid::kOnA);
    }
    else if (driveJoystick->GetRawButton(6))
    {
        shifter->Set(DoubleSolenoid::kOnB);
    }
}

/**
 * Initializes autonomous mode settings at the beginning of autonomous.
 */
void SimbotPrime::AutonomousInit()
{
    autonStep = 1;
    gripperLoops = 0;
    gripperOpening = false;

    gyro->Reset();
    leftEncoder->Reset();
    rightEncoder->Reset();

    cameraXCtrl->resetErrorSum();
    cameraYCtrl->resetErrorSum();
    driveEncoderCtrl->resetErrorSum();
    driveGyroCtrl->resetErrorSum();
    elevatorCtrl->resetErrorSum();
    fourBarCtrl->resetErrorSum();
}

/**
 * Runs periodically during autonomous mode.
 * Uses sensor inputs and PID to control motor outputs directly.
 */
void SimbotPrime::AutonomousPeriodic(void)
{
    GetWatchdog().Feed();

    // Look for the green light.
    ParticleAnalysisReport par;
    bool seeLight = false;
    if (FindColor(IMAQ_HSL, &tdata.hue, &tdata.saturation, &tdata.luminance, &par)
            && par.particleToImagePercent < MAX_PARTICLE_TO_IMAGE_PERCENT
            && par.particleToImagePercent > MIN_PARTICLE_TO_IMAGE_PERCENT) 
    {
        seeLight = true;
        int lightX = (int)(par.center_mass_x_normalized * 1000.0);
        int lightY = (int)(par.center_mass_y_normalized * 1000.0);

        printf("Light found: x: %i y: %i\n", lightX, lightY);
    } 
    else 
    {
        printf("Light NOT found\n");
    }

    // Do the autonomous control, depending on what state the robot is in.
    switch(autonStep)
    {
        // Rotate the robot to lign up with the light.
        case 1:
            {
                cameraXCtrl->setConstants(0.0001, 0.01, 0.002);
                cameraXCtrl->setDesiredValue(0);
                cameraXCtrl->setErrorEpsilon(50);
                cameraXCtrl->setMinDoneCycles(0);
                cameraXCtrl->setMaxOutput(0.2);

                elevatorCtrl->setConstants(0.0, 0.0, 0.0);
                fourBarCtrl->setConstants(0.0, 0.0, 0.0);	
                cameraYCtrl->setConstants(0.0, 0.0, 0.0);
                driveEncoderCtrl->setConstants(0.0, 0.0, 0.0);
                driveGyroCtrl->setConstants(0.0, 0.0, 0.0);

                if (cameraXCtrl->isDone())
                {
                    autonStep = 2;
                }

                break;
            }
            // Move the arm up.
        case 2:
            {	
                fourBarCtrl->setConstants(0.006, 0.01, 0.008);	
                fourBarCtrl->setDesiredValue(375);
                fourBarCtrl->setErrorEpsilon(10);
                fourBarCtrl->setMinDoneCycles(0);

                elevatorCtrl->setConstants(0.0, 0.0, 0.0);
                cameraXCtrl->setConstants(0.0, 0.0, 0.0);
                cameraYCtrl->setConstants(0.0, 0.0, 0.0);
                driveEncoderCtrl->setConstants(0.0, 0.0, 0.0);
                driveGyroCtrl->setConstants(0.0, 0.0, 0.0);

                if (fourBarCtrl->isDone())
                {
                    autonStep = 3;
                }

                break;
            }
            // Drive to the scoring position in front of the spider leg.
        case 3:
            {	
                cameraXCtrl->setConstants(0.0000001, 0.0025, 0.002);
                cameraXCtrl->setDesiredValue(175);
                cameraXCtrl->setErrorEpsilon(30);
                cameraXCtrl->setMinDoneCycles(0);
                cameraXCtrl->setMaxOutput(0.5);

                cameraYCtrl->setConstants(0.0002, 0.0055, 0.00125);
                cameraYCtrl->setDesiredValue(-516);
                cameraYCtrl->setErrorEpsilon(25);
                cameraYCtrl->setMinDoneCycles(0);
                cameraYCtrl->setMaxOutput(0.4);

                if (cameraXCtrl->isDone() && cameraYCtrl->isDone())
                {
                    autonStep = 4;
                }

                break;
            }
            // Lower the arm.
        case 4:
            {	
                fourBarCtrl->setConstants(0.006, 0.03, 0.008);
                fourBarCtrl->setDesiredValue(431);

                cameraXCtrl->setConstants(0.0, 0.0, 0.0);
                cameraYCtrl->setConstants(0.0, 0.0, 0.0);

                if (fourBarCtrl->isDone())
                {
                    autonStep = 5;
                }

                break;
            }
            // Open the claw.
        case 5:
            {	
                if (!gripperOpening)
                {
                    gripperOpening = true;
                    gripperLoops = 0;
                }

                // Open the claw.
                gripper->Set(Relay::kForward);
                gripperLoops++;

                if (gripperLoops > 5) // 0.025 seconds
                {
                    gripper->Set(Relay::kOff);
                    autonStep = 6;
                }

                break;
            }
            // Stop.
        case 6:
            {	
                gripper->Set(Relay::kOff);

                fourBarCtrl->setConstants(0.006, 0.01, 0.008);
                fourBarCtrl->setDesiredValue(477);

                break;
            }
    }

    // Calculate "virtual joystick" x and y values.
    float x = 0.0; 
    if(seeLight)
    {
        // Include camera PID calculations only if we see the light.
        x += cameraXCtrl->calcPID((int)(par.center_mass_x_normalized * 1000));
    }
    else
    {
        cameraXCtrl->resetErrorSum();
    }
    x += driveGyroCtrl->calcPID((int)(gyro->GetAngle() * 10));

    float y = 0.0; 
    if(seeLight)
    {
        // Include camera PID calculations only if we see the light.
        y += cameraYCtrl->calcPID((int)(par.center_mass_y_normalized * 1000));
    }
    else
    {	
        cameraYCtrl->resetErrorSum();

        // Wander forward slowly looking for the light.
        y -= 0.2;
    }
    y += -driveEncoderCtrl->calcPID(
            (leftEncoder->Get() / 2) + (rightEncoder->Get() / 2));

    // Calculate and output drive values.
    float left = SimLib::limitOutput(y + x);
    float right = -SimLib::limitOutput(y - x);

    driveLeftFront->Set(left);
    driveLeftBack->Set(left);
    driveRightFront->Set(right);
    driveRightBack->Set(right);

    // Calculate and output arm values.
    float fbarOut = -fourBarCtrl->calcPID(fourbarPot->GetAverageValue());
    float elevOut = -elevatorCtrl->calcPID(elevatorPot->GetAverageValue());

    fourBar->Set(fbarOut);
    elevator->Set(elevOut);

    // Stay in low gear.
    shifter->Set(DoubleSolenoid::kOnA);
}
