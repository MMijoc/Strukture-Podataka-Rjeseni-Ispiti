/*
Zadatak_22
12.02.2013. Grupa 2


Napisati program koji
a) iz datoteke čita podatke (dva int, prvi je vrijednost a drugi prioritet (od 1- 5)) i sprema ih u red s prioritetom.
Što je veći prioritet to je podatak bliže vrhu reda.
b) Podaci unutar istog prioriteta moraju biti sortirani po veličini od najmanjeg prema najvećem.
(Napomena: U datoteci treba biti najmanje 20 parova.)

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0
#define BUFFER_LENGTH 1024

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _priorityQueue {
	int value;
	int priority;

	struct _priorityQueue *next;
} PriorityQueue;

void PrintError(char *message);
char *GetFileContent(char *fileName);
PriorityQueue *CreateNewNode(int value, int priority);
PriorityQueue *CreateNewNode(int value, int priority);
int Push(PriorityQueue *queueHead, PriorityQueue *toInsert);
int Pop(PriorityQueue *queueHead, int *toPop);
int BuildQueueFromString(PriorityQueue *queueHead, char *source);
int PrintList(PriorityQueue *queueHead);

int main()
{
	char fileName[BUFFER_LENGTH] = {"Zad_22"};
	char *fileContent = NULL;
	PriorityQueue queue = {0, 0, NULL};
	int tmp = 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;

	BuildQueueFromString(&queue, fileContent);
	PrintList(&queue);
	
	printf("\n\nPoping all values form Priority Queue:");
	while (Pop(&queue, &tmp) != FAILURE) {
		printf("%d -> ", tmp);
	}

	free(fileContent);
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

char *GetFileContent(char *fileName)
{
	FILE *fp = NULL;
	size_t length = 0;
	char *content = NULL;

	if (!fileName || strlen(fileName) <= 0) RETURN_NULL("Invalid arguments");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_NULL("Error");


	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	content = (char *)calloc(length + 1, sizeof(char));
	if (!content) RETURN_NULL("Error");

	fread(content, sizeof(char), length, fp);

	fclose(fp);
	return content;
}

PriorityQueue *CreateNewNode(int value, int priority)
{
	PriorityQueue *newNode = NULL;

	newNode = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	if (!newNode) RETURN_NULL("Error");

	newNode->value = value;
	newNode->priority = priority;
	newNode->next = NULL;

	return newNode;
}

int Push(PriorityQueue *queueHead, PriorityQueue *toInsert)
{
	PriorityQueue *tmp = NULL;

	if (!queueHead || !toInsert) RETURN_FAILURE("Invalid function arguments");

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

int BuildQueueFromString(PriorityQueue *queueHead, char *source)
{
	int argTaken = 1, offset = 0;
	int value = 0, priority = 0;

	if (!source) RETURN_FAILURE("BuildListFromString: Invalid arguments!");

	while (argTaken > 0) {
		argTaken = sscanf(source, " %d%d%n", &value, &priority, &offset);
		if (argTaken == 2)
			Push(queueHead, CreateNewNode(value, priority));

		source += offset;
	}

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
