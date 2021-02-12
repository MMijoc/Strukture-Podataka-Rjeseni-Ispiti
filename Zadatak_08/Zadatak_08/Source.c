/*


*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FALIURE (-1)
#define BUFFER_LENGTH 1024

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);

int main()
{
	puts("Hello world");

	return SUCCESS;
}