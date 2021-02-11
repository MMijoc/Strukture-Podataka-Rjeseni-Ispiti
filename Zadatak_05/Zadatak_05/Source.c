#define _CRT_SECURE_NO_WARNING
/*
Zadatak_05
3 ispitni rok - dodatni 10.9.2020


Napisati program koji generira 30 slučajnih brojeve u opsegu od 120-150.
Sve brojeve spremiti u vezanu listu tako da redoslijed brojeva u listi odgovara redoslijedu generiranja brojeva.
Ispisati listu i nakon toga izbrisati iz liste sve vrijednosti koje se ponavljaju uz uvjet da u čvoru koji ostane u listi se zapiše koliko je ukupno bilo tih vrijednosti.
Ispisati novu vezanu listu kao i broj ponavljanja svakog čvora.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//for debuging memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define N 30

typedef struct _node {
	int value;
	int nDuplicates;

	struct _node *next;
} node;

int GetRandomNumber(int min, int max);
node *CreateNewNode(int value);
node *FindTail(node *listHead);
int InsertAtTail(node *listHead, node *toInsert);
int PrintList(node *listHead);
int DeleteDuplicates(node *listHead);
int SotredInsert(node *listHead, node *toInsert);
int FreeList(node *node);
int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);

int main()
{
	node List = {0, 0, NULL};
	int numbers[N];
	int i = 0;

	//for debuging memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	printf("Randomly generated numbers are:\n\t");
	for (i = 0; i < N; i++) {
		numbers[i] = GetRandomNumber(120, 150);
		printf("%d ", numbers[i]);
	}

	for (i = 0; i < N; i++)
		InsertAtTail(&List, CreateNewNode(numbers[i]));

	printf("\nRandom numbers in the list:\n\t");
	PrintList(&List);

	DeleteDuplicates(&List);
	printf("\nList with no duplicate values in it (number in the brackets is the number of duplicate values in the original list):\n\t");
	PrintList(&List);

	FreeList(List.next);
	puts("");
	return SUCCESS;
}

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}

node *CreateNewNode(int value)
{
	node *newNode = NULL;

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) return (node *)ExecutionFailureNull("Error");

	newNode->value = value;
	newNode->nDuplicates = 1;
	newNode->next = NULL;

	return newNode;
}

node *FindTail(node *listHead)
{
	node *tmp = listHead;

	while (tmp->next)
		tmp = tmp->next;

	return tmp;
}

int InsertAtTail(node *listHead, node *toInsert)
{
	node *tail = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid function paramaters");

	tail = FindTail(listHead);
	tail->next = toInsert;

	return SUCCESS;
}

int PrintList(node *listHead)
{
	node *tmp = listHead->next;

	while (tmp) {
		printf("%d", tmp->value);
		if (tmp->nDuplicates != 1)
			printf("(%d)",tmp->nDuplicates);
		printf(" ");
		tmp = tmp->next;
	}

	return SUCCESS;
}

int DeleteDuplicates(node *listHead)
{
	node *tmp = NULL;
	node *nextOne = NULL;
	node *tmpList = NULL;

	tmp =  listHead->next;
	listHead->next = NULL; //break list

	while (tmp) {
		nextOne = tmp->next;
		SotredInsert(listHead, tmp);
		tmp = nextOne;
	}

	return SUCCESS;
}

int SotredInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;
	node *toFree = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid function paramters");

	tmp = listHead;
	while (tmp->next && tmp->next->value < toInsert->value)
		tmp = tmp->next;

	if (tmp->next && tmp->next->value == toInsert->value) {
		tmp->next->nDuplicates++;
		free(toInsert);
		return SUCCESS;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int FreeList(node *node)
{
	if (node == NULL) return SUCCESS;

	FreeList(node->next);
	free(node);

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
