#if !defined(_WSAUTODRIVECRAWL_H)
#define _WSAUTODRIVECRAWL_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoDriveCrawl : public WsAutoNStepBase
{
    public:
        WsAutoDriveCrawl(UINT8 driveTime);
        virtual ~WsAutoDriveCrawl();
        virtual void initParams(void);
    protected:
        UINT8 a_driveTime;
        UINT8 a_crawlTime;
};

#endif
