#if !defined(_WSAUTOHOMEOUTPOST_H)
#define _WSAUTOHOMEOUTPOST_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoHomeOutpost : public WsAutoNStepBase
{
    public:
        WsAutoHomeOutpost();
        virtual ~WsAutoHomeOutpost();
        virtual void initParams(void);
};

#endif
