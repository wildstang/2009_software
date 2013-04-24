#if !defined(_WSAUTOOUTPOSTHOME_H)
#define _WSAUTOOUTPOSTHOME_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoOutpostHome : public WsAutoNStepBase
{
    public:
        WsAutoOutpostHome();
        virtual ~WsAutoOutpostHome();
        virtual void initParams(void);
};

#endif
