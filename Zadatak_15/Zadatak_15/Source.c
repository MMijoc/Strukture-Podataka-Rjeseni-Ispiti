/*
3 ispitni rok 11.9.2014.


Napisati program koji generira slučajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran sprema se u vezanu listu parnih brojeva i to u padajućem redoslijedu
(od najvećeg prema najmanjem), Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, takoder u padajućem redoslijedu.
Niti jedna vezana lista ne smije sadržavati dva ista elementa.
Unos traje sve dok obje liste ne sadrže 10 clemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste.

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
#define MAX 10

typedef struct _node {
	int value;

	struct _node *next;
} node;

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"


void PrintError(char *message);
int GetRandomNumber(int min, int max);
node *CreateNewNode(int value);
int SotredInsert(node *listHead, node *toInsert);
int PrintList(node *listHead);
int FreeList(node *node);

int main()
{
	node even = {0, NULL};
	node odd = {0, NULL};
	int x = 0;
	int evenCount = 0;
	int oddCount = 0;


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while ((evenCount < MAX) || (oddCount < MAX)) {
		x = GetRandomNumber(50, 80);
		if (x % 2 == 0) {
			if (evenCount < MAX)
				if (SotredInsert(&even, CreateNewNode(x)) == SUCCESS)
					evenCount++;
		} else {
			if (oddCount < MAX)
				if (SotredInsert(&odd, CreateNewNode(x)) == SUCCESS)
					oddCount++; 
		}
	}

	printf("Even list:\t ");
	PrintList(&even);
	printf("\nOdd list:\t ");
	PrintList(&odd);
	puts("");

	FreeList(even.next);
	FreeList(odd.next);
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

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}

node *CreateNewNode(int value)
{
	node *newNode = NULL;

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) RETURN_NULL("Error");

	newNode->value = value;
	newNode->next = NULL;

	return newNode;	
}

int SotredInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && tmp->next->value > toInsert->value)
		tmp = tmp->next;

	if (tmp->next && tmp->next->value == toInsert->value) {
		free(toInsert);
		return FAILURE;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintList(node *listHead)
{
	node *tmp = listHead->next;

	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeList(node *node)
{
	if (node == NULL) return SUCCESS;

	FreeList(node->next);
	free(node);

	return SUCCESS;
}
