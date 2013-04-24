#if !defined(_WSAUTOPARKEROPP_H)
#define _WSAUTOPARKEROPP_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoParkerOpp : public WsAutoNStepBase
{
    public:
        WsAutoParkerOpp();
        virtual ~WsAutoParkerOpp();
        virtual void initParams(void);
};

#endif
