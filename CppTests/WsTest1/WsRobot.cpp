#include "WsRobot.h"
#include "WsControllerAxis.h"
#include "WsControllerButton.h"
#include "WsControllerStickyButton.h"


WsRobot::WsRobot()
{
    autoLoopCount = 0;

    GetWatchdog().SetExpiration(100);
}

WsRobot::~WsRobot(void)
{
	delete ap_turboButton;
	delete ap_accumButton;
	delete ap_driveX;
	delete ap_driveY;
	delete driveStick;
}

// Called once when the robot is turned on, before operation begins.
void WsRobot::RobotInit(void)
{
    driveStick = new Joystick(1); // USB port 1
    
    ap_turboButton = new WsControllerButton(driveStick, 1);
    ap_accumButton = new WsControllerStickyButton(driveStick, 2);
    
    ap_driveX = new WsControllerAxis(driveStick, 1);
    ap_driveY = new WsControllerAxis(driveStick, 2);
}

void WsRobot::DisabledPeriodic()
{
    GetWatchdog().Feed();
    DisableMotors();
    
    // Print out a message indicating the state of a joystick button.
#if 0
    for(int i = 0; i < 12; i++)
    {
    	printf("%d:%d ", i + 1, driveStick->GetRawButton(i + 1));
    }
#endif
    
    // Print out a message indicating the axes of a joystick
#if 0
    for(int i = 0; i < 5; i++)
    {
    	printf("%d:%f ", i + 1, driveStick->GetRawAxis(i + 1));
    }
#endif
    
    printf("X: %f ", ap_driveX->getValue());
    printf("Y: %f ", ap_driveY->getValue());
    
    //UpdateDashboard();
    
    printf("\n");
}

void WsRobot::TeleopInit()
{
    GetWatchdog().Feed();
    DisableMotors();
}

void WsRobot::TeleopPeriodic()
{
    GetWatchdog().Feed();
    //DisableMotors();
    
    
    if(ap_turboButton->getState() == true)
    {
    	printf("I'm going fast!!!\n");
    }
    
    
    if(ap_accumButton->getState() == true)
    {
        printf("Accumulate on\n");
    }
    else
    {
        printf("Accumulate off\n");
    }
}

void WsRobot::AutonomousInit()
{
    autoLoopCount = 0;
    DisableMotors();
}

void WsRobot::AutonomousPeriodic()
{
    GetWatchdog().Feed();
    autoLoopCount++;
}

void WsRobot::DisableMotors()
{
}

void WsRobot::UpdateDashboard()
{
    /*
    static float num = 0.0;
    a_dashboardDataFormat.m_AnalogChannels[0][0] = num;
    a_dashboardDataFormat.m_AnalogChannels[0][1] = 5.0 - num;
    
    if(ap_turboButton->getState() == true)
    {
        a_dashboardDataFormat.m_DIOChannels[0] = 1;
    }
    else
    {
        a_dashboardDataFormat.m_DIOChannels[0] = 0;
    }
    
    if(ap_accumButton->getState() == true)
    {
        a_dashboardDataFormat.m_DIOChannels[0] = 1;
    }
    else
    {
        a_dashboardDataFormat.m_DIOChannels[0] = 0;
    }
    
    
    
    a_dashboardDataFormat.m_DIOChannels[0]++;
    a_dashboardDataFormat.m_DIOChannelsOutputEnable[0]--;
    num += 0.01;
    if (num > 5.0) num = 0.0;
    a_dashboardDataFormat.PackAndSend();
    */
}




