#include "request.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char string1[] = "GET /?a=2&b=3&c=4 \r\n";

	DataBuffer s1 = {string1, 0, 0};

	Request* request1 = init_Request(&s1);

	printf("method:%s\n", request1->method);
	printf("path:%s\n", request1->path);

	return 0;
}
