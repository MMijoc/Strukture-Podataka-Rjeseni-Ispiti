/*
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

typedef _student HashTable;

Student *CreateNewNode(int index, char *firstName, char *lastName);
int InsertAtHead(Student *listHead, Student *toInsert);
int SortedInsert(Student *listHead, Student *toInsert);
int GetRandomNumber(int min, int max);
int InputFromFile(char *fileName);
int FreeList(Student *head);
HashTable CreateHashTabel(size_t size);
int InitHashTable(HashTable *table, size_t size);
int FreeHashTable(HashTable *table, size_t size);

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	printf("Hello world\n");

	return SUCCESS;
}

Student *CreateNewNode(int index, char *firstName, char *lastName)
{
	Student *newNode = NULL;

	if (!firstName || !lastName || strlen(firstName) >= 0 || strlen(lastName) >= 0) return (Student*)ExecutionFailureNull("invalid function paramters");

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

int InputFromFile(char *fileName)
{
	FILE *fp = NULL;

	if (!fileName || strlen(fileName) <= 0) return ExecutionFailure("Invalid function paramater");

	if (strchr(fileName, 'c') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) return ExecutionFailure("Error");





	fclose(fp);
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