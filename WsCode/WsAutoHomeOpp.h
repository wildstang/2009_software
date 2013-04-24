#if !defined(_WSAUTOHOMEOPP_H)
#define _WSAUTOHOMEOPP_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoHomeOpp : public WsAutoNStepBase
{
    public:
        WsAutoHomeOpp();
        virtual ~WsAutoHomeOpp();
        virtual void initParams(void);
};

#endif
