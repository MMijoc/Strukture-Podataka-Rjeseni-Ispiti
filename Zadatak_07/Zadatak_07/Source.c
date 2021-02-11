/*
Zadatak_07
izvanredni ispitni rok 22. rujna 2020.


Napisati program koji generira 30 puta dva slučajna broja. Prvi broj je vrijednost i ona je u opsegu od 100 do 200, a drugi je prioritet u opsegu od 1 do 5.
Te podatke se sprema u strukturu od koje se gradi red s prioritetom. Što je veći prioritet to je podatak bliže vrhu (početku) reda. Ispisati red.

Izmijeniti unos na način da podaci unutar istog prioriteta moraju biti sortirani po veličini od najmanjeg prema najvećem (koristiti sortirani unos, a ne sortiranje). 
Ispisati red.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//for debugging memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define N 30

typedef struct _priorityQueue {
	int value;
	int priority;

	struct _priorityQueue *next;
} PriorityQueue;

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);
int GetRandomNumber(int min, int max);
PriorityQueue *CreateNewNode(int value, int priority);
int Push(PriorityQueue *queueHead, PriorityQueue *toInsert);
int Pop(PriorityQueue *queueHead, int *toPop);
int PrintList(PriorityQueue *queueHead);

int main()
{
	int value;
	int priority;
	int i, tmp;
	PriorityQueue Queue = {0, 0, NULL};

	//for debugging memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	printf("Values and priority generated in order:");
	for (i = 0; i < N; i++) {
		value = GetRandomNumber(100, 200);
		priority = GetRandomNumber(1, 5);
		printf("\n%d %d", value, priority);
		Push(&Queue, CreateNewNode(value, priority));
	}

	printf("\n\nPriority Queue:");
	PrintList(&Queue);

	printf("\n\nPoping all values form Priority Queue:");
	while (Pop(&Queue, &tmp) != FAILURE) {
		printf("%d -> ", tmp);
	}

	puts("");
	return SUCCESS;
}

int ExecutionFailure(char *message)
{
	if (errno != 1)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return FAILURE;
}

void *ExecutionFailureNull(char *message)
{
	if (errno != 1)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return NULL;
}

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min + 1);
}

PriorityQueue *CreateNewNode(int value, int priority)
{
	PriorityQueue *newNode = NULL;
	
	newNode = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	if (!newNode) return (PriorityQueue *)ExecutionFailureNull("Error");

	newNode->value = value;
	newNode->priority = priority;
	newNode->next = NULL;

	return newNode;
}

int Push(PriorityQueue *queueHead, PriorityQueue *toInsert)
{
	PriorityQueue *tmp = NULL;
	
	if (!queueHead || !toInsert) return ExecutionFailure("Invalid function arguments");

	tmp = queueHead;
	while (tmp->next && tmp->next->priority < toInsert->priority)
		tmp = tmp->next;

	while (tmp->next && tmp->next->priority == toInsert->priority && tmp->next->value < toInsert->value)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int Pop(PriorityQueue *queueHead, int *toPop)
{
	PriorityQueue *tmp = NULL;

	tmp = queueHead->next;
	if (tmp == NULL) return FAILURE;

	queueHead->next = tmp->next;
	*toPop = tmp->value;
	free(tmp);

	return SUCCESS;
}

int PrintList(PriorityQueue *queueHead)
{
	PriorityQueue *tmp = queueHead->next;
	while (tmp) {
		printf("\n%d %d", tmp->value, tmp->priority);
		tmp = tmp->next;
	}

	return SUCCESS;
}




