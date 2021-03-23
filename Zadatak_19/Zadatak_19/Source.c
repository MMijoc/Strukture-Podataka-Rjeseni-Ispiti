/*
Zadatak_19
izvanredni ispitni rok 26.9.2017.


Kreirati dvije datoteke i u njih upisati 10 slučajno generiranih brojeva iz opsega od 20-35. Svaku od datoteka pročitati i spremiti u vezanu listu
(kreiraju se dvije vezane liste, npr. L1 i L2). Ispisati ih.
Iz ove dvije vezane liste se kreiraju dvije nove vezane liste koje sadrže:
a) presjek parnih članova listi L1 i L2;
b) uniju neparnih članova listi L1 i L2.

Kod kreiranja listi pod a) i b) se ne smije koristiti malloc, već uzeti postojeće elemente iz listi L1 i L2 i preusmjeriti pokazivače. Ispisati sve četiri liste.
U listama pod a) i b) ne smije biti duplih vrijednosti i vrijednosti moraju bit složene uzlaznim redoslijedom.

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


typedef struct _node {
	int value;

	struct _node *next;
} node;


void PrintError(char *message);
char *GetFileContent(char *fileName);
node *CreateNewNode(int value);
int SortedInsert(node *listHead, node *toInsert);
int InputFromString(node *head, char *source);
int PrintList(node *head);
int FreeList(node *element);
int OddListUnion(node *L1, node *L2, node *result);
int EvenListIntersection(node *L1, node *L2, node *result);
node *Unlink(node *previous, node **current);
int InsertAt(node *position, node *toInsert);


int main()
{
	node list1 = {0, NULL}, list2 = {0, NULL};
	node evenIntersection = {0, NULL};
	node oddUnion = {0, NULL};
	char fileName[BUFFER_LENGTH] = {'\0'};
	char *fileContent = NULL;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	strncpy(fileName, "Zad_19_list1", BUFFER_LENGTH);
	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;
	InputFromString(&list1, fileContent);
	free(fileContent);
	fileContent = NULL;

	strncpy(fileName, "Zad_19_list2", BUFFER_LENGTH);
	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;
	InputFromString(&list2, fileContent);
	free(fileContent);
	fileContent = NULL;

	printf("List 1: ");
	PrintList(&list1);
	printf("List 2: ");
	PrintList(&list2);

	EvenListIntersection(&list1, &list2, &evenIntersection);
	printf("\n\nLists intersection only with even numbers: ");
	PrintList(&evenIntersection);
	printf("\nList 1: ");
	PrintList(&list1);
	printf("List 2: ");
	PrintList(&list2);

	printf("\n\nLists union only with odd numbers: ");
	OddListUnion(&list1, &list2, &oddUnion);
	PrintList(&oddUnion);
	printf("\nList 1: ");
	PrintList(&list1);
	printf("List 2: ");
	PrintList(&list2);

	FreeList(list1.next);
	FreeList(list2.next);
	FreeList(evenIntersection.next);
	FreeList(oddUnion.next);

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

node *CreateNewNode(int value)
{
	node *tmp = NULL;

	tmp = (node *)malloc(sizeof(node));
	if (!tmp) RETURN_NULL("Error");

	tmp->value = value;
	tmp->next = NULL;

	return tmp;
}

int SortedInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE("Invalid function arguments");

	tmp = listHead;
	while (tmp->next && tmp->next->value < toInsert->value)
		tmp = tmp->next;

	if (tmp->next && tmp->next->value == toInsert->value)
		return FAILURE;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int InputFromString(node *head, char *source)
{
	int argTaken = 0, n = 0;
	int value = 0;
	int err = 0;
	node *newNode = NULL;

	while (TRUE) {
		argTaken = sscanf(source, "%d%n", &value, &n);
		if (argTaken != 1)
			break;
		source += n;
		newNode = CreateNewNode(value);
		err = SortedInsert(head, newNode);
		if (err == FAILURE)
			free(newNode);
	}

	return SUCCESS;
}

int PrintList(node *head)
{
	node *tmp = head->next;

	if (!head) RETURN_FAILURE("PrintList: Invalid function arguments!");
	if (!tmp) {
		printf("List is empty!\n");
		return FAILURE;
	}

	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	puts("");

	return SUCCESS;
}

int FreeList(node *element)
{
	if (element == NULL) return SUCCESS;

	FreeList(element->next);
	free(element);

	return SUCCESS;
}

int OddListUnion(node *L1, node *L2, node *result)
{
	node *tmp = NULL;
	node *curr1 = NULL;
	node *curr2 = NULL;
	node *prev1 = L1;
	node *prev2 = L2;
	node *resultTail = result;
	int proceed = FALSE;

	if (!L1 || !L2 || !result) RETURN_FAILURE("OddListUnion: Invalid arguments!");

	curr1 = prev1->next;
	curr2 = prev2->next;
	while (curr1 && curr2) {
		proceed = FALSE;
		if (curr1->value % 2 == 0) {
			prev1 = curr1;
			curr1 = curr1->next;
			proceed = TRUE;
		}
		if (curr2->value % 2 == 0) {
			prev2 = curr2;
			curr2 = curr2->next;
			proceed = TRUE;
		}
		if (proceed == TRUE)
			continue;

		if (curr1->value == curr2->value) {
			InsertAt(resultTail, Unlink(prev1, &curr1));
			resultTail = resultTail->next;
			free(Unlink(prev2, &curr2));

		} else if (curr1->value < curr2->value) {
			InsertAt(resultTail, Unlink(prev1, &curr1));
			resultTail = resultTail->next;

		} else /*if (curr1->value > curr2->value)*/ {
			InsertAt(resultTail, Unlink(prev2, &curr2));
			resultTail = resultTail->next;
		}
	}


	if (curr1) {
		curr2 = curr1;
		prev2 = prev1;
	}

	while (curr2) {
		if (curr1->value % 2 == 1) {
			InsertAt(resultTail, Unlink(prev1, &curr2));
			resultTail = resultTail->next;
		} else {
			curr2 = curr2->next;
		}
	}

	return SUCCESS;
}

int EvenListIntersection(node *L1, node *L2, node *result)
{
	node *curr1 = NULL;
	node *curr2 = NULL;
	node *prev1 = L1;
	node *prev2 = L2;
	node *resultTail = result;
	int proceed = FALSE;

	if (!L1 || !L2 || !result) RETURN_FAILURE("EvenListIntersection: Invalid arguments!");

	curr1 = prev1->next;
	curr2 = prev2->next;
	while (curr1 && curr2) {
		proceed = FALSE;
		if (curr1->value % 2 != 0) {
			prev1 = curr1;
			curr1 = curr1->next;
			proceed = TRUE;
		}
		if (curr2->value % 2 != 0) {
			prev2 = curr2;
			curr2 = curr2->next;
			proceed = TRUE;
		}
		if (proceed == TRUE)
			continue;

		if (curr1->value > curr2->value) {
			prev2 = curr2;
			curr2 = curr2->next;

		} else if (curr1->value < curr2->value) {
			prev1 = curr1;
			curr1 = curr1->next;

		} else {
			InsertAt(resultTail, Unlink(prev1, &curr1));
			resultTail = resultTail->next;
			free(Unlink(prev2, &curr2));
		}
	}

	return SUCCESS;
}

node *Unlink(node *previous, node **current)
{
	node *tmp = *current;

	previous->next = (*current)->next;
	(*current) = (*current)->next;

	tmp->next = NULL;
	return tmp;
}

int InsertAt(node *position, node *toInsert)
{
	toInsert->next = position->next;
	position->next = toInsert;

	return SUCCESS;
}
