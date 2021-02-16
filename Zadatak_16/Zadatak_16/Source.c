/*
Zadatak_16
dekanski rok 23.9.2014.


Napisati program koji iz dvije datoteke (jedna sadrži ocjenu 1. kolokvija,a druga ocjenu 2. kolokvija) kreira vezanu listu studenata koji su položili ispit
i ta se nova vezana lista slaže po ocjenama. Način pretvorbe bodova u ocjenu je dan u tablici.

Bodovi			Ocjena
50 - 59.99%		2

60- 73.99%		3

74 - 86.99%		4

87 - 100		5


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
#define N 2

typedef struct _student {
	char firstName[BUFFER_LENGTH];
	char lastName[BUFFER_LENGTH];
	int points;

	struct _student *next;
} Student;

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
Student *CreateNewStudent(char *firstName, char *lastName, int mark);
int SortedInsertStudent(Student *listHead, Student *toInsert,  int addPointsForDuplicates);
int AddPoints(Student *s, int points);
int PrintStudentList(Student *listHead);
int PrintStudentAndMarks(Student *listHead);
int GetMark(Student *s);
int FreeStudentList(Student *node);
int InputStudentsFromFile(Student *listHead, char *fileName);
int BuildAllStudentsAndMarks(Student sLists[], Student *result);
int _internal_SortedInsert(Student *listHead, Student *toInsert);
int OrderByPassingMark(Student *listHead);

int main()
{
	char fileName[N][BUFFER_LENGTH] = {"Zad_16_1kolokvij", "Zad_16_2kolokvij"};
	Student kolokvij[N] = {"", "", 0, NULL};
	Student result = {"", "", 0, NULL};
	int i = 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for (i = 0; i < N; i++) {
		InputStudentsFromFile(&kolokvij[i], fileName[i]);
	}

	
	for (i = 0; i < N; i++)	{
		printf("\n\tAll students form file: %s\n", fileName[i]);
		PrintStudentList(&kolokvij[i]);
	}

	BuildAllStudentsAndMarks(kolokvij, &result);
	printf("\n\n\nAll students nad their marks and average:\n");
	PrintStudentAndMarks(&result);

	printf("\n\n\nAll students who have pased:\n");
	OrderByPassingMark(&result);
	PrintStudentAndMarks(&result);

	for (i = 0; i < N; i++) {
		FreeStudentList(kolokvij[i].next);
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

Student *CreateNewStudent(char *firstName, char *lastName, int points)
{
	Student *newNode = NULL;

	if (!firstName || !lastName) RETURN_NULL(ERR_0);
	
	newNode = (Student *)malloc(sizeof(Student));
	if(!newNode) RETURN_NULL("Error");

	strncpy(newNode->firstName, firstName, BUFFER_LENGTH);
	strncpy(newNode->lastName, lastName, BUFFER_LENGTH);
	newNode->points = points;
	newNode->next = NULL;

	return newNode;
}

int SortedInsertStudent(Student *listHead, Student *toInsert,  int addPointsForDuplicates)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) < 0)
		tmp = tmp->next;

	while (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) < 0)
		tmp = tmp->next;


	if (tmp->next && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) == 0) {
		if (addPointsForDuplicates == TRUE)
			AddPoints(tmp->next, toInsert->points);
		else
			printf("Student %s %s already exits\n", toInsert->firstName, toInsert->lastName);
		free(toInsert);
		return FAILURE;	
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int AddPoints(Student *s, int points)
{
	s->points += points;
	return SUCCESS;
}

int PrintStudentList(Student *listHead)
{
	Student *tmp = listHead->next;
	while (tmp) {
		printf("%-32s %-32s %-4d\n", tmp->firstName, tmp->lastName, tmp->points);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintStudentAndMarks(Student *listHead)
{
	Student *tmp = listHead->next;
	while (tmp) {
		printf("%-32s %-32s %-4d %-4d\n", tmp->firstName, tmp->lastName, tmp->points, GetMark(tmp));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int GetMark(Student *s)
{
	float percentage = 0;
	if (s->points == 0) return 1;

	percentage = (float)(s->points / 2);

	if (percentage < 50) return 1;
	if (percentage >= 50 && percentage < 60) return 2;
	if (percentage >= 60 && percentage < 74) return 3;
	if (percentage >= 74 && percentage < 87) return 4;
	if (percentage >= 87 && percentage <= 100) return 5;

	return FAILURE;
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
	int points = 0;

	if (!listHead || !fileName) RETURN_FAILURE(ERR_0);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");

	while (!feof(fp)) {
		memset(buffer, '\0', BUFFER_LENGTH);
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%s%d", fName, lName, &points);
		if (argTaken != 3) {
			//printf("Following line was not read successfully: \"%s\"\n", buffer);
			continue;
		}
		SortedInsertStudent(listHead, CreateNewStudent(fName, lName, points), FALSE);

	
	}

	fclose(fp);
	return SUCCESS;
}

int BuildAllStudentsAndMarks(Student sLists[], Student *result)
{
	Student *tmp = NULL;
	int i = 0;

	for (i = 0; i < N; i++) {
		tmp = sLists[i].next;
		while (tmp) {
			SortedInsertStudent(result, CreateNewStudent(tmp->firstName, tmp->lastName, tmp->points), TRUE);
			tmp = tmp->next;
		}
	}

	return SUCCESS;
}

int OrderByPassingMark(Student *listHead)
{

	Student *tmp = NULL;
	Student *next = NULL;

	if (!listHead) RETURN_FAILURE(ERR_0);

	tmp = listHead->next;
	listHead->next = NULL;

	while(tmp) {
		next = tmp->next;
		tmp->next = NULL;
		_internal_SortedInsert(listHead, tmp);
		tmp = next;
	}

	return SUCCESS;
}

int _internal_SortedInsert(Student *listHead, Student *toInsert)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);
	if (GetMark(toInsert) < 2) {
		free(toInsert);
		return FAILURE;
	}

	tmp = listHead;
	while (tmp->next && tmp->next->points < toInsert->points)
		tmp = tmp->next;

	while (tmp->next && tmp->next->points == toInsert->points && _stricmp(tmp->next->lastName, toInsert->lastName) < 0)
			tmp = tmp->next;

	while (tmp->next && tmp->next->points == toInsert->points && _stricmp(tmp->next->lastName, toInsert->lastName) == 0 && _stricmp(tmp->next->firstName, toInsert->firstName) < 0)
			tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}
