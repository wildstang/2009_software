#if !defined(_WSAUTOPARKERHOMEALT_H)
#define _WSAUTOPARKERHOMEALT_H

#include <stdio.h>
#include "WsAutoNStepBase.h"

class WsAutoParkerHomeAlt : public WsAutoNStepBase
{
    public:
        WsAutoParkerHomeAlt();
        virtual ~WsAutoParkerHomeAlt();
        virtual void initParams(void);
};

#endif
