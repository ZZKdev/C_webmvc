#include "request.h"
#include "types.h"
#include "request_parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void uri_decode(char *str){
	char *r=str;
	char *w=str;
	char tmp[3]={0,0,0};
	while (*r){
		if (*r == '%'){
			r++;
			tmp[0]=*r++;
			tmp[1]=*r;
			*w=strtol(tmp, (char **)NULL, 16);
		}
		else if (*r=='+'){
			*w=' ';
		}
		else{
			*w=*r;
		}
		r++;
		w++;
	}
	*w='\0';
}

void Dict_add(Dict** dict, char *key, char *value)
{
    Dict* temp = (*dict);
    if(*dict == NULL)
    {
        *dict = malloc(sizeof(Dict));
        temp = *dict;
    }
    else
    {
        while(temp->next)
        {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(Dict));
        temp = temp->next;
    }
    temp->key = key;
    temp->value = value;
    temp->next = NULL;
	printf("add key:%s\tvalue:%s\n", key, value);
}

Dict* new_parameter(char* string)
{
    if(string == NULL)
    {
        return NULL;
    }

    int state = 0; //0 key, 1 value
    char *key = NULL, *value = NULL;
    key = string;
    Dict* dict = NULL;

    while(*string)
    {
        if(state == 0)
        {
            if(*string == '=')
            {
                *string = '\0';
                value = string + 1;
                state = 1;
            }
        }
        else
        {
            if(*string == '&')
            {
                *string = '\0';
                uri_decode(key);
                uri_decode(value);
                Dict_add(&dict, key, value);
                key = string + 1;
                state = 0;
            }
        }
        string++;
    }
    if(state == 1)
    {
        uri_decode(key);
        uri_decode(value);
        Dict_add(&dict, key, value);
    }
    return dict;
}

Request* init_Request(DataBuffer* buffer)
{
    Request* request = malloc(sizeof(Request));
    if(request == NULL)
    {
        fprintf(stderr, "malloc error!\n");
        return request;
    }
    memset(request, 0, sizeof(Request));

    char* start = readLine(buffer);
    int readIndex = 0;

    /*************Get the method from requestline**********/
    while(isSpace(start[readIndex])) readIndex++;
    while(!isSpace(start[readIndex])) readIndex++; 
    start[readIndex++] = '\0';
    request->method = getMethod(start);
    start = &start[readIndex];
    readIndex = 0;

    /************Get the path from requestline*************/
    int query_status = 0;
    while(!isSpace(start[readIndex]))
    {
        if(start[readIndex] == '?')
        {
            query_status = 1;
            break;
        }
        readIndex++;
    }
    start[readIndex++] = '\0';
    request->path = start;
    start = &start[readIndex];
    readIndex = 0;

    /**If have query parmeters, get the dict parmeters**/
    if(query_status == 1)
    {
        while(!isSpace(start[readIndex]))
        {
            readIndex++;
        }
        start[readIndex++] = '\0';
        request->parmeters = new_parameter(start);
    }
    /****parse the header************/
    while(*(start = readLine(buffer)) != '\0')
    {
        char *key = start, *value = NULL;
        while(*start != ':')
        {
            start++;
        }
        *(start++) = '\0';
        while(!isSpace(*start)) start++;
        *(start++) = '\0';
        value = start;
        Dict_add(&(request->header), key, value);
    }
    return request;
}