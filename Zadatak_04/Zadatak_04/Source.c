﻿/*
Zadatak_04


Napisati program koji iz datoteke cita popis studenata i sprema ih u vezanu listu.

struct _student;
typedef struct _student *StudentNode;
typedef struct _student {
	int brojIndeksa;
	char *ime;
	char *prezime;
	int orderNum;

	StudentNode next;
} Student;

a) Prilikom spremanja studenta u vezanu listu potrebno je studentu dodijeliti orderNum, kao slučajno generirani cijeli broj u rasponu od 1 do 1000.
Ispisati listu.

b) Iz tako kreirane liste potrebno je kreirati novu vezanu listuu kojoj ce studenti biti sortirani po orderNum. Ispisati listu.
NAPOMENA: Nije dozvoljena nova alokacija elementato pri nose u novu vezanu listu vec je potrebno prebaciti cvorove iz postojece liste.

c) Iz sortirane liste kreirati hash tablicu sa zasebnim redovima od 8 (osam) mjesta.
Funkcija preslikavanja ključ računa kao ostatak cjelobrojnog dijeljenja orderNum ukupnim brojem elemenata tablice Studenti s izračunatim ključem se spremaju u binarno stablo po broju indexa.

NAPOMENA: Zatvoriti sve otvorene datoteke, pobrisati svu dinamički alociranu memoriju i mirnim putem prekinuti rad programa.
Programski kod napisati koristentno, uredno te odvojeno u funkcije

*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//for debugging
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024


struct student;
typedef struct _student *StudentNode;
typedef struct _student {
	int brojIndeksa;
	char *ime;
	char *prezime;
	int orderNum;

	StudentNode next;
} Student;

typedef Student HashTable;

Student *CreateNewNode(int index, char *firstName, char *lastName);
int InsertAtHead(Student *listHead, Student *toInsert);
int SortedInsert(Student *listHead, Student *toInsert);
int SortListByOrderNum(Student *listHead);
int GetRandomNumber(int min, int max);
int InputFromFile(char *fileName, Student *listHead);
int FreeList(Student *head);
HashTable CreateHashTabel(size_t size);
int InitHashTable(HashTable *table, size_t size);
int FreeHashTable(HashTable *table, size_t size);
int PrintList(Student *listHead);

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	char fileName[BUFFER_LENGTH] = {'\0'};
	Student List;
	List.next = NULL;

	//for debugging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	strncpy(fileName, "Zad_4", BUFFER_LENGTH);
	InputFromFile(fileName, &List);

	PrintList(&List);
	puts("");

	SortListByOrderNum(&List);
	PrintList(&List);
	puts("");

	FreeList(List.next);
	return SUCCESS;
}

Student *CreateNewNode(int index, char *firstName, char *lastName)
{
	Student *newNode = NULL;

	if (!firstName || !lastName || strlen(firstName) <= 0 || strlen(lastName) <= 0) return (Student*)ExecutionFailureNull("Invalid function paramters");

	newNode = (Student *)malloc(sizeof(Student));
	if (!newNode) return (Student*)ExecutionFailureNull("Memory allocation failed");

	newNode->ime = (char *)calloc(strlen(firstName) + 1, sizeof(char));
	newNode->prezime = (char *)calloc(strlen(lastName) + 1, sizeof(char));
	if (!newNode->ime || !newNode->prezime) return (Student*)ExecutionFailureNull("Memory allocation failed");
	
	newNode->brojIndeksa = index;
	strcpy(newNode->ime, firstName);
	strcpy(newNode->prezime, lastName);
	newNode->orderNum = GetRandomNumber(1, 1000);
	newNode->next = NULL;

	return newNode;
}

int InsertAtHead(Student *listHead, Student *toInsert)
{
	if (!listHead || !toInsert) return ExecutionFailure("Invalid function parameters");

	toInsert->next = listHead->next;
	listHead->next = toInsert;

	return SUCCESS;
}

int SortedInsert(Student *listHead, Student *toInsert)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid function parameters");

	tmp = listHead;
	while (tmp->next && tmp->next->orderNum < toInsert->orderNum)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}

int SortListByOrderNum(Student *listHead)
{
	Student *tmp = NULL;
	Student *nextOne = NULL;

	tmp = listHead->next;
	listHead->next = NULL;

	while (tmp) {
		nextOne = tmp->next;
		SortedInsert(listHead, tmp);
		tmp = nextOne;
	}

	return SUCCESS;
}

int InputFromFile(char *fileName, Student *listHead)
{
	FILE *fp = NULL;
	int argTaken = 0;
	int index = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char firstName[BUFFER_LENGTH] = {'\0'};
	char lastName[BUFFER_LENGTH] = {'\0'};

	if (!fileName || strlen(fileName) <= 0) return ExecutionFailure("Invalid function paramater");

	if (strchr(fileName, 'c') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) return ExecutionFailure("Error");

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%d %s %s", &index, firstName, lastName);
		if (argTaken != 3) {
			printf("Following line was not read successfuly: %s", buffer);
			continue;
		}

		InsertAtHead(listHead, CreateNewNode(index, firstName, lastName));
	}

	fclose(fp);
	return SUCCESS;
}

int PrintList(Student *listHead)
{
	Student *tmp = NULL;

	tmp = listHead->next;
	while (tmp) {
		printf("\n%-5d %-32s %-32s %-10d",tmp->brojIndeksa, tmp->ime, tmp->prezime, tmp->orderNum);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeList(Student *node)
{
	Student *tmp = NULL;
	
	if (node == NULL) return SUCCESS;

	FreeList(node->next);
	free(node->ime);
	free(node->prezime);
	free(node);
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