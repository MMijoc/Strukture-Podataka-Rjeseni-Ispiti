/*
Zadatak_12
2 ispitni rok 27.2.2014.


Napisati program koji čita iz datoteka podatke o studentima i ispitima, te kreira dvije vezane liste

struct _Student{
	char *sifra_studenta;
	char *ime;
	char *prezime;
	char *sifra_ispita;
	struct _Student *Next;
};

struct _ispit {
	char *sifra_ispita;
	char *naziv;
	struct Ispit *Next;
};

Potrebno je ispisati koliko je studenata položilo svaki pojedini ispit (po nazivu ispita), te nabrojati koji su to studenti
//valjda se podrazumjeva da su svi studenti u datoteci polozili ispit
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


struct _student{
	char *sifra_studenta;
	char *ime;
	char *prezime;
	char *sifra_ispita;
	struct _student *next;
};

struct _ispit {
	char *sifra_ispita;
	char *naziv;
	struct _ispit *next;
};

typedef struct _student Student;
typedef struct _ispit Exam;


#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
Student *CreateNewStudent(char *firstName, char *lastName, char *studCode, char *examCode);
int StudentSortedInsert(Student *listHead, Student *toInsert);
int PrintStudentAndExamsList(Student *sListm, Exam *eList);
int FreeStudent(Student *toFree);
int FreeStudentList(Student *head);

Exam *CreateNewExam(char *name, char *examCode);
int ExamSortedInsert(Exam *listHead, Exam *toInsert);
int PrintExamList(Exam *listHead);
int FreeExam(Exam *toFree);
int FreeExamList(Exam *head);
int InputStudentsFromFile(Student *listHead, char *fileName);
int InputExamsFromFile(Exam *listHead, char *fileName);
char *GetExamName(Exam *eList, char *eCode);

int main()
{
	Student sList = {NULL, NULL, NULL, NULL, NULL};
	Exam eList = {NULL, NULL, NULL};
	char examsFile[BUFFER_LENGTH] = {"Zad_12_predmeti"};
	char studentsFile[BUFFER_LENGTH] = {"Zad_12_studenti"};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	InputStudentsFromFile(&sList, studentsFile);
	InputExamsFromFile(&eList, examsFile);

	PrintStudentAndExamsList(&sList, &eList);
	printf("\n\n");
	//PrintExamList(&eList);

	FreeExamList(eList.next);
	FreeStudentList(sList.next);
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

Student *CreateNewStudent(char *firstName, char *lastName, char *studCode, char *examCode)
{
	Student *newNode = NULL;

	if (!firstName || !lastName || !studCode || !examCode) RETURN_NULL(ERR_0);

	newNode = (Student *)malloc(sizeof(Student));
	if (!newNode) RETURN_NULL("Error");

	newNode->ime = (char *)calloc(strlen(firstName) + 1, sizeof(char));
	newNode->prezime = (char *)calloc(strlen(lastName) + 1, sizeof(char));
	newNode->sifra_studenta = (char *)calloc(strlen(studCode) + 1, sizeof(char));
	newNode->sifra_ispita = (char *)calloc(strlen(examCode) + 1, sizeof(char));

	if (!newNode->ime || !newNode->prezime || !newNode->sifra_studenta || !newNode->sifra_ispita) RETURN_NULL("Error");

	strcpy(newNode->ime, firstName);
	strcpy(newNode->prezime, lastName);
	strcpy(newNode->sifra_studenta, studCode);
	strcpy(newNode->sifra_ispita, examCode);

	newNode->next = NULL;
	
	return newNode;
}

int StudentSortedInsert(Student *listHead, Student *toInsert)
{
	Student *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->prezime, toInsert->prezime) < 0)
		tmp = tmp->next;

	while (tmp->next && _stricmp(tmp->next->prezime, toInsert->prezime) == 0 && _stricmp(tmp->next->ime, toInsert->ime) < 0)
		tmp = tmp->next;

	if (tmp->next && _stricmp(tmp->next->prezime, toInsert->prezime) == 0 && _stricmp(tmp->next->ime, toInsert->ime) == 0) {
		FreeStudent(toInsert);
		return FAILURE;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintStudentAndExamsList(Student *sList, Exam *eList)
{
	Student *tmp = sList->next;

	while (tmp) {
		printf("%-32s %-32s %-32s\n", tmp->ime, tmp->prezime, GetExamName(eList, tmp->sifra_ispita));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeStudent(Student *toFree)
{
	if (!toFree) RETURN_FAILURE(ERR_0);

	free(toFree->ime);
	free(toFree->prezime);
	free(toFree->sifra_studenta);
	free(toFree->sifra_ispita);
	free(toFree);

	return SUCCESS;
}

int FreeStudentList(Student *node)
{
	if (node == NULL) return SUCCESS;

	FreeStudentList(node->next);
	FreeStudent(node);

	return SUCCESS;
}

Exam *CreateNewExam(char *name, char *examCode)
{
	Exam *newNode = NULL;

	if (!name || !examCode) RETURN_NULL(ERR_0);

	newNode = (Exam *)malloc(sizeof(Exam));
	if (!newNode) RETURN_NULL("Error");

	newNode->naziv = (char *)calloc(strlen(name) + 1, sizeof(char));
	newNode->sifra_ispita = (char *)calloc(strlen(examCode) + 1, sizeof(char));

	if (!newNode->naziv || !newNode->sifra_ispita) RETURN_NULL("Error");

	strcpy(newNode->naziv, name);
	strcpy(newNode->sifra_ispita, examCode);

	newNode->next = NULL;
	
	return newNode;
}

int ExamSortedInsert(Exam *listHead, Exam *toInsert)
{
	Exam *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->sifra_ispita, toInsert->sifra_ispita) < 0)
		tmp = tmp->next;

	if (tmp->next && _stricmp(tmp->next->sifra_ispita, toInsert->sifra_ispita) == 0) {
		FreeExam(toInsert);
		return FAILURE;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintExamList(Exam *listHead)
{
	Exam *tmp = listHead->next;

	while (tmp) {
		printf("%-32s %-32s\n", tmp->naziv, tmp->sifra_ispita);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeExam(Exam *toFree)
{
	if (!toFree) RETURN_FAILURE(ERR_0);

	free(toFree->naziv);
	free(toFree->sifra_ispita);
	free(toFree);

	return SUCCESS;
}

int FreeExamList(Exam *node)
{
	if (node == NULL) return SUCCESS;

	FreeExamList(node->next);
	FreeExam(node);

	return SUCCESS;
}

int InputStudentsFromFile(Student *listHead, char *fileName)
{
	FILE *fp = NULL;
	int argTaken = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char fName[BUFFER_LENGTH] = {'\0'};
	char lName[BUFFER_LENGTH] = {'\0'};
	char sCode[BUFFER_LENGTH] = {'\0'};
	char eCode[BUFFER_LENGTH] = {'\0'};

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");
	
	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%s%s%s", sCode, fName, lName, eCode);
		if (argTaken != 4) {
			printf("\nFollowing line could not be read: %s", buffer);
			continue;
		}
		StudentSortedInsert(listHead, CreateNewStudent(fName, lName, sCode, eCode));
	}

	fclose(fp);
	return SUCCESS;
}

int InputExamsFromFile(Exam *listHead, char *fileName)
{
	FILE *fp = NULL;
	int argTaken = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char eName[BUFFER_LENGTH] = {'\0'};
	char eCode[BUFFER_LENGTH] = {'\0'};

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");
	
	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s %s", eCode, eName);
		if (argTaken != 2) {
			printf("\nFollowing line could not be read: %s", buffer);
			continue;
		}
		ExamSortedInsert(listHead, CreateNewExam(eName, eCode));
	}

	fclose(fp);
	return SUCCESS;
}

char *GetExamName(Exam *eList, char *eCode)
{
	Exam *tmp = eList->next;

	while (tmp) {
		if (strcmp(tmp->sifra_ispita, eCode) == 0)
			return tmp->naziv;
		tmp = tmp->next;
	}

	return NULL;
}