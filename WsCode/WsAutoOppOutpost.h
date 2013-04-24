#if !defined(_WSAUTOOPPOUTPOST_H)
#define _WSAUTOOPPOUTPOST_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoOppOutpost : public WsAutoNStepBase
{
    public:
        WsAutoOppOutpost();
        virtual ~WsAutoOppOutpost();
        virtual void initParams(void);
};

#endif
