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

#define N 20

typedef struct _node {
	int value;

	struct _node *next;
} node;

int GetRandomNumber(int min, int max);
node *CreateNewNode(int value);
int EvenOddInsert(node *listHead, node *toInsert);
int FreeList(node *listHead);
int PrintList(node *head);
int SortOddEven(node *head);
int SortedInsert(node *head, node *toInsert);
int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	int numbers[N];
	node List = {0, NULL};
	int i;

	printf("Random numbers generated:\n\t\t");
	for (i = 0; i < N; i++) {
		numbers[i] = GetRandomNumber(100, 200);
		printf("%d ", numbers[i]);
	}

	for (i = 0; i < N; i++)
		EvenOddInsert(&List, CreateNewNode(numbers[i]));

	printf("\n\nEven numbers descending - odd numbers ascending:\n\t\t");
	PrintList(&List);


	SortOddEven(&List);
	printf("\n\nAll numbers sorted descending:\n\t\t");
	PrintList(&List);
	printf("\n\n");

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
		while (tmp->next && tmp->next->value % 2 == 0 && tmp->next->value > toInsert->value)
			tmp = tmp->next;
	
	} else {
		while (tmp->next && tmp->next->value % 2 == 0)
			tmp = tmp->next;
		while (tmp->next && tmp->next->value < toInsert->value)
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

int FreeList(node *firstToFree)
{
	if (firstToFree == NULL) return SUCCESS;

	FreeList(firstToFree->next);
	free(firstToFree);

	return SUCCESS;
}

int SortOddEven(node *head)
{
	node *tmp = NULL;
	node *nextOne = NULL;
	node oddList = {0, NULL};

	if (!head) return ExecutionFailure("Invalid function paramaters");

	tmp = head;
	while (tmp->next && tmp->next->value % 2 == 0)
		tmp = tmp->next;

	oddList.next = tmp->next;
	tmp->next = NULL;

	tmp = oddList.next;
	while (tmp) {
		nextOne = tmp->next;
		SortedInsert(head, tmp);
		tmp = nextOne;
	}

	return SUCCESS;
}

int SortedInsert(node *head, node *toInsert)
{
	node *tmp = NULL;

	if (!head || !toInsert) return ExecutionFailure("Invalid function paramaters");

	tmp = head;
	while (tmp->next && tmp->next->value > toInsert->value)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

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