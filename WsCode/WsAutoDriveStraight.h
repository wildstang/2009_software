#if !defined(_WSAUTODRIVESTRAIGHT_H)
#define _WSAUTODRIVESTRAIGHT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoDriveStraight : public WsAutoNStepBase
{
    public:
        WsAutoDriveStraight(UINT8 driveTime);
        virtual ~WsAutoDriveStraight();
        virtual void initParams(void);

    protected:
        UINT8 a_driveTime;
};

#endif
