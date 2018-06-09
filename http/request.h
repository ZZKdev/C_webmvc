#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

enum method{GET, POST};

typedef struct Parameter{
	char* key;
	char* value;
	struct Parameter* next;
}Parameter;

typedef struct Request{
	char* requsetHeader;
	char* requestBody;
	enum method;
	short parametersParsed;
	Parameter* parmeters;
};

typedef struct Response{
	char* responseHeader;
	char* responseBody;

}Response;

/*Request fuction*/
Request* init_Request(char* string);
char* getPath(Request request);
enum method getMethod(Request request);
void parseParaemters(Request request);
char* getParameter(Request request);

/*Response function*/
void setResponseHeader(Response response, char* key, char* value);
void setResponseBody(Response response, char* body);
void free_response(Response response);
char* reponse_toString(Response response);
#endif
