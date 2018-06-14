#include "../request.h"
#include "../types.h"
#include <stdio.h>

int main(void)
{
    char string1[] = "GET /?a=2&b=3&c=4 \r\n";
    char string2[] = "POST /a?b=33&cc=3 \r\n";
    DataBuffer s1 = {string1, 0, 0};
    DataBuffer s2 = {string2, 0, 0};

    Request* request1 = init_Request(&s1);
//    Request* request2 = init_Request(&s2);

    printf("method:%s\n", request1->method);
    printf("path:%s\n", request1->path);
    Dict* dict = request1->parmeters;
    while(dict)
    {
        printf("key:%s\tvalue:%s\n", dict->key, dict->value);
        dict = dict->next;
    }

    //printf("method:%s\n", request2->method);
    //printf("path:%s\n", request2->path);
    // dict = request2->parmeters;
    // while(dict)
    // {
    //     printf("key:%s.value:%s\n", dict->key, dict->value);
    // }
    
    return 0;
}