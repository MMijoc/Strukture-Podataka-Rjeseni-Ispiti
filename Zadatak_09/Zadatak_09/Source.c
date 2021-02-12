/*
Zadatak_09
1 ispitni rok 13.2.2014.


Napisati program koji iz datoteke čita dio teksta, riječ po riječi unosi ih u red s prioritetom
(maksimalna duljina riječi 1024 znaka, prioritet=1 => riječ počinje samoglasnikom, prioritet=2 => riječ počinje suglasnikom;).
Riječi u redu moraju biti sortirane po prioritetu.

Iz tako kreiranog reda kreirati dvije datoteke, u prvoj će se nalaziti riječi sa prioritetom=1, a u drugoj riječi s prioritetom=2; 
s tim da su te riječi u datoteci zapisane sortirane po abecedi.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024

typedef struct _priorityQueue {
	char word[BUFFER_LENGTH];
	int priority;

	struct _priorityQueue *next;
} PriorityQueue;


int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);

int main()
{
	puts("Hello world");

	return SUCCESS;
}


int ExecutionFailure(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);
	
	return FAILURE;
}

void *ExecutionFailureNull(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);
	
	return NULL;
}

