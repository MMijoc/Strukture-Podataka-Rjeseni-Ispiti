#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;}while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;}while(0);

void PrintError(char *message);

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	puts("Hello world");

	return SUCCESS;
}

void PrintError(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);
	
	return;
}