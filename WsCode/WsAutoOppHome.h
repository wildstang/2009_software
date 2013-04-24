#if !defined(_WSAUTOOPPHOME_H)
#define _WSAUTOOPPHOME_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoOppHome : public WsAutoNStepBase
{
    public:
        WsAutoOppHome();
        virtual ~WsAutoOppHome();
        virtual void initParams(void);
};

#endif
