#pragma once

typedef struct DataBuffer_t{
    char* data;
    unsigned long iSize;
    unsigned long offset;
}DataBuffer;

typedef struct Dict{
	char* key;
	char* value;
	struct Dict* next;
}Dict;
