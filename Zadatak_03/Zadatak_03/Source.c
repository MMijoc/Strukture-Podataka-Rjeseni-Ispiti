/*
Zadatak_03
29. kolovoza 2019.

Napisati program koji generira 20 slučajnih brojeva u opsegu od 20 - 50.
Pri tome parne brojeve spremiti na početak vezane liste od najvećeg prema najmanjem,
a neparne spremati na kraj vezane najmanjeg prema najvećem.
U vezanoj listi ne smije biti ponavljanja elemenata i ne smiju se koristiti nizovi.
Ispisati listu.

Složiti elemente vezane liste od najvećeg prema najmanjem, ali se pri tome ne smije koristiti funkcija za sortiranje,
već se treba iskoristiti raspored elemenata u vezanoj listi i samo prebacivati neparne elemente na odgovarajuće mjesto
(od na većeg prema najmanjem).
Ispisati listu.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)

typedef struct _node {
	int value;

	struct _node *next;
} node;

int GetRandomNumber(int min, int max);
node *CreateNewNode(int value);
int EvenOddInsert(node *listHead, node *toInsert);
int FreeList(node *listHead);
int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);
int PrintList(node *head);


int main()
{
	int number = 0;

	node List = {0, NULL};
	int i = 0;
	for (i = 0; i < 20; i++) {
		number = GetRandomNumber(100, 200);
		printf("%d ", number);
		EvenOddInsert(&List, CreateNewNode(number));
	}

	puts("");
	PrintList(&List);
	puts("");

	FreeList(List.next);
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
	newNode->next = NULL;

	return newNode;	
}

int EvenOddInsert(node *listHead, node *toInsert)
{
	node *tmp = listHead;
	
	if (!listHead || !toInsert) return ExecutionFailure("Invalid functions paramaters");

	tmp = listHead;
	if (toInsert->value % 2 == 0) {
		while (tmp->next && tmp->next->value % 2 == 0 && tmp->next->value < toInsert->value)
			tmp = tmp->next;
	
	} else {
		while (tmp->next && tmp->next->value % 2 == 0)
			tmp = tmp->next;
		while (tmp->next && tmp->next->value > toInsert->value)
			tmp = tmp->next;
	}
	
	if (tmp->next && tmp->next->value == toInsert->value) {
		free(toInsert);
		return SUCCESS;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintList(node *head)
{
	node *tmp = head->next;

	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int ExecutionFailure(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr,"%s", message);

	return FAILURE;
}

void *ExecutionFailureNull(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr,"%s", message);

	return NULL;
}

int FreeList(node *firstToFree)
{
	if (firstToFree == NULL) return SUCCESS;

	FreeList(firstToFree->next);
	free(firstToFree);

	return SUCCESS;
}