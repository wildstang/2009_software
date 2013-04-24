#if !defined(_WSAUTOOPPOUTPOSTALT_H)
#define _WSAUTOOPPOUTPOSTALT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoOppOutpostAlt : public WsAutoNStepBase
{
    public:
        WsAutoOppOutpostAlt();
        virtual ~WsAutoOppOutpostAlt();
        virtual void initParams(void);
};

#endif
