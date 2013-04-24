#ifndef _WSROBOT_H_
#define _WSROBOT_H_

#include "WPILib.h"
#include "DashboardDataFormat.h"

class WsControllerAxis;
class WsControllerButton;
class WsControllerStickyButton;

class WsRobot : public IterativeRobot
{
public:
    WsRobot(void);
    ~WsRobot(void);
    virtual void DisabledPeriodic();
    virtual void TeleopInit();
    virtual void TeleopPeriodic();
    virtual void AutonomousInit();
    virtual void AutonomousPeriodic();
    
    virtual void RobotInit(void);

    void DisableMotors();
    void UpdateDashboard();

private:
    Joystick *driveStick;
    //Joystick *joystick2;
    
    WsControllerAxis* ap_driveX;
    WsControllerAxis* ap_driveY;
    
    WsControllerButton* ap_turboButton;
    WsControllerButton* ap_accumButton;

	//DashboardDataFormat a_dashboardDataFormat;
	//Dashboard* ap_dashboard;
    int autoLoopCount;
    
};

START_ROBOT_CLASS(WsRobot);




#endif
