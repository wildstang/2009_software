#if !defined(_WSAUTOPARKERHOME_H)
#define _WSAUTOPARKERHOME_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoParkerHome : public WsAutoNStepBase
{
    public:
        WsAutoParkerHome();
        virtual ~WsAutoParkerHome();
        virtual void initParams(void);
};

#endif
