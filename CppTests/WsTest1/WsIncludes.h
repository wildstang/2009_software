#ifndef _WS_INCLUDES_H_
#define _WS_INCLUDES_H_

#define MIN_MAX(variable, min_val, max_val) MIN((variable),(min_val));MAX((variable),(max_val))
#define MAX(variable, max_val) if((variable) > (max_val)) variable = (max_val)
#define MIN(variable, min_val) if((variable) < (min_val)) variable = (min_val)

#define MAX_RETURN(value, max_val) ((value) > (max_val) ? (max_val) : (value))
#define MIN_RETURN(value, min_val) ((value) < (min_val) ? (min_val) : (value))


#endif
