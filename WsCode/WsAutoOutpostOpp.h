#if !defined(_WSAUTOOUTPOSTOPP_H)
#define _WSAUTOOUTPOSTOPP_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoOutpostOpp : public WsAutoNStepBase
{
    public:
        WsAutoOutpostOpp();
        virtual ~WsAutoOutpostOpp();
        virtual void initParams(void);
};

#endif
