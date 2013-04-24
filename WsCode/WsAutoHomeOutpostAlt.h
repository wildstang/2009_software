#if !defined(_WSAUTOHOMEOUTPOSTALT_H)
#define _WSAUTOHOMEOUTPOSTALT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoHomeOutpostAlt : public WsAutoNStepBase
{
    public:
        WsAutoHomeOutpostAlt();
        virtual ~WsAutoHomeOutpostAlt();
        virtual void initParams(void);
};

#endif
