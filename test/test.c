#include "request.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char string1[] = "GET /?a=2&b=3&c=4 \r\nhost: baidu.com\r\nconnection: keep-alive\r\n\r\n";

	DataBuffer s1 = {string1, 0, 0};

	Request* request1 = init_Request(&s1);
	while(request1->header)
	{
		printf("header:\tkey: %s\tvalue: %s\n", request1->header->key, request1->header->value);
		request1->header = request1->header->next;
	}
	while(request1->parmeters)
	{
		printf("get:\tkey: %s\tvalue: %s\n", request1->parmeters->key, request1->parmeters->value);
		request1->parmeters = request1->parmeters->next;
	}
	printf("method:%s\n", request1->method);
	printf("path:%s\n", request1->path);
	system("pause");
	return 0;
}
