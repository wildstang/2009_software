#if !defined(_WSAUTOPARKEROPPALT_H)
#define _WSAUTOPARKEROPPALT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoParkerOppAlt : public WsAutoNStepBase
{
    public:
        WsAutoParkerOppAlt();
        virtual ~WsAutoParkerOppAlt();
        virtual void initParams(void);
};

#endif
