#include "WsAutoDriveCrawl.h"


WsAutoDriveCrawl::WsAutoDriveCrawl(UINT8 driveTime)
{
  a_driveTime = driveTime;
  a_crawlTime = 15 - a_driveTime;
}

WsAutoDriveCrawl::~WsAutoDriveCrawl()
{
}

void WsAutoDriveCrawl::initParams(void)
{
    WsAutoNStepBase::WsAutoNStepCmdT drive1;
    WsAutoNStepBase::WsAutoNStepCmdT drive2;

    WsAutoNStepBase::initParams();

    // Attributes for drive 1
    drive1.crabAngle = 0;
    drive1.driveVector.a_speed = 1;
    drive1.driveVector.a_direction = 0;
    drive1.timeout = a_driveTime;

    // Attributes for drive 2
    drive2.crabAngle = 0;
    drive2.driveVector.a_speed = .2;
    drive2.driveVector.a_direction = 0;
    drive2.timeout = a_crawlTime;

    // Add the steps to the program...order matters
    addStep(drive1);
    addStep(drive2);

}
