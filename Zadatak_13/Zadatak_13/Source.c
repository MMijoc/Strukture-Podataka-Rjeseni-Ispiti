/*
Zadatak_13
3 ispitni rok 28.8.2014


Napisati program koji za tri različita predmeta čita ime i prezime studenta te njegovu ocjenu.
Podaci o svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i ispisati je.

a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri predmeta

b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena studenata, sadrži i njihovu prosječnu ocjenu iz ta tri predmeta.

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
#define N 3

typedef struct _student {
	char firstName[BUFFER_LENGTH];
	char lastName[BUFFER_LENGTH];
	int mark[N];
	int markCount;

	struct _student *next;
} Student;

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
Student *CreateNewStudent(char *firstName, char *lastName, int mark);
int SortedInsertStudent(Student *listHead, Student *toInsert);
int PrintStudentList(Student *listHead);
int PrintMarks(Student *s);
int FreeStudentList(Student *node);
int InputStudentsFromFile(Student *listHead, char *fileName);
int BuildAllStudentsAndMarks(Student listHead[], Student *result);
int _internal_SortedInsert(Student *listHead, Student *toInsert);
int AddMark(Student *s, int mark);
int RemoveStudentsWithLessThanNMarks(Student *listHead);
float GetAverage(Student *s);

int main()
{
	char courses[N][BUFFER_LENGTH] = {"Zad_12_1", "Zad_12_2", "Zad_12_3"};

	Student sLists[N];
	Student tmpList;
	Student result;
	Student *tmp = NULL;
	int i = 0;
	for (i = 0; i < N; i++)
		sLists[i].next = NULL;
	result.next = NULL;

	//for debugging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |_CRTDBG_LEAK_CHECK_DF);

	for (i = 0; i < N; i++)
		InputStudentsFromFile(&sLists[i], courses[i]);

	for (i = 0; i < N; i++) {
		printf("\n\t\tStudents from file: %s\n", courses[i]);
		PrintStudentList(&sLists[0]);	
	}

	BuildAllStudentsAndMarks(sLists, &result);
	RemoveStudentsWithLessThanNMarks(&result);
	printf("\nAll students who have passed all %d courses and their average grade:\n", N);
	PrintStudentList(&result);

	for (i = 0; i < 3; i++) {
		FreeStudentList(sLists[i].next);
	}
	FreeStudentList(result.next);

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

Student *CreateNewStudent(char *firstName, char *lastName, int mark)
{
	Student *newNode = NULL;

	if (!firstName || !lastName) RETURN_NULL(ERR_0);
	
	newNode = (Student *)malloc(sizeof(Student));
	if(!newNode) RETURN_NULL("Error");

	strncpy(newNode->firstName, firstName, BUFFER_LENGTH);
	strncpy(newNode->lastName, lastName, BUFFER_LENGTH);
	newNode->markCount = 1;
	newNode->mark[newNode->markCount - 1] = mark;
	newNode->next = NULL;

	return newNode;
}

int SortedInsertStudent(Student *listHead, Student *toInsert)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) < 0)
		tmp = tmp->next;

	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) < 0)
		tmp = tmp->next;


	if (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) == 0) {
		printf("Student %s %s already exits\n", toInsert->firstName, toInsert->lastName);
		free(toInsert);
		return FAILURE;	
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintStudentList(Student *listHead)
{
	Student *tmp = listHead->next;
	while (tmp) {
		printf("%-32s %-32s", tmp->firstName, tmp->lastName);
		PrintMarks(tmp);
		printf("\t\t%.2f\n", GetAverage(tmp));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintMarks(Student *s)
{
	int i = 0;
	if (!s) return FAILURE;

	for (i = 0; i < s->markCount; i++){
		printf("%d ", s->mark[i]);
	}

	return SUCCESS;
}

int FreeStudentList(Student *node)
{
	if (node == NULL) return SUCCESS;

	FreeStudentList(node->next);
	free(node);

	return SUCCESS;
}

int InputStudentsFromFile(Student *listHead, char *fileName)
{
	FILE *fp = NULL;
	int argTaken = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char fName[BUFFER_LENGTH] = {'\0'};
	char lName[BUFFER_LENGTH] = {'\0'};
	int mark = 0;

	if (!listHead || !fileName) RETURN_FAILURE(ERR_0);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%s%d", fName, lName, &mark);
		if (argTaken != 3) {
			//printf("Following line was not read successfully: %s", buffer);
			continue;
		}
		SortedInsertStudent(listHead, CreateNewStudent(fName, lName, mark));
	
	}

	fclose(fp);
	return SUCCESS;
}

int AddMark(Student *s, int mark)
{
	s->mark[s->markCount] = mark;
	s->markCount++;
	return SUCCESS;
}

int BuildAllStudentsAndMarks(Student sLists[], Student *result)
{
	Student *tmp = NULL;
	int i = 0;

	for (i = 0; i < N; i++) {
		tmp = sLists[i].next;
		while (tmp) {
			if (tmp->mark[0] >= 2)
				_internal_SortedInsert(result, CreateNewStudent(tmp->firstName, tmp->lastName, tmp->mark[0]));
			tmp = tmp->next;
		}
	}

	return SUCCESS;
}

int _internal_SortedInsert(Student *listHead, Student *toInsert)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) < 0)
		tmp = tmp->next;

	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) < 0)
		tmp = tmp->next;

	if (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) == 0) {
		AddMark(tmp->next, toInsert->mark[0]);
		free(toInsert);
		return SUCCESS;	
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int RemoveStudentsWithLessThanNMarks(Student *listHead)
{
	Student *tmp = listHead->next;
	Student *prev = listHead;

	while (tmp) {
		if (tmp->markCount < N) {
			prev->next = tmp->next;
			free(tmp);
			tmp = prev->next;
			continue;
		}
		prev = tmp;
		tmp = tmp->next;
	}

	return SUCCESS;
}

float GetAverage(Student *s)
{
	int total = 0;
	int i = 0;

	for (i = 0; i < s->markCount; i++)
		total += s->mark[i];

	return (float)total / s->markCount;
}
