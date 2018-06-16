#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include "types.h"

typedef struct Request{
	char* method;
	char* path;
	Dict* parmeters;
	Dict* header;
}Request;


/*Request fuction*/
Request* init_Request(DataBuffer* buffer);
#endif
