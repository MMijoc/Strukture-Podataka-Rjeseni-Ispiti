/*
Zadatak_11
2 ispitni rok 27.2.2014.


Napisati program koji iz datoteke čita podatke o broju bodova koje je jedan student dobio na ispitu i sprema ih u binarno stablo pretraživanja.

struct _student {
	char ime[128];
	char prezime[128];
	int broj_bodova;
	float relativni_broj_bodova;
	struct _student *left;
	struct _student *right;
}

(Napomena: 0 broj_bodova <= 100).
Ispisati binarno stablo na „inorder" način.

U tako kreiranom binarnom stablu potrebno je za svakog od studenata izračunati i relativan broj bodova po formuli:
relativan_broj_bodova = ( broj_bodova / MAX(broj_bodova) )
Ispisati binarno stablo na "preorder" način.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024
#define NAME_LENGTH 128
#define MAX_POINTS 100

struct _student {
	char ime[128];
	char prezime[128];
	int broj_bodova;
	float relativni_broj_bodova;
	struct _student *left;
	struct _student *right;
};
typedef struct _student Student;

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;}while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;}while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
float CalcRelativePoints(int points, int maxPoints);
Student *CreateNewStudent(char *firtName, char *lastName, int points, float relativePoints);
Student *InsertToTree(Student *current, Student *toInsert);
Student *BuildTreeFromFile(char *fileName);
int PrintTreePostOrder(Student *current);
int PrintTreeInOrder(Student *current);
int FreeTree(Student *current);

int main()
{
	Student *root = NULL;
	char fileName[BUFFER_LENGTH] = {"Zad_11"};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	root = BuildTreeFromFile(fileName);
	printf("Tree InOrder:\n");
	PrintTreeInOrder(root);
	printf("\n\n\nTree PostOrder:\n");
	PrintTreePostOrder(root);

	FreeTree(root);
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

float CalcRelativePoints(int points, int maxPoints)
{
	return (float)points / maxPoints;
}

Student *CreateNewStudent(char *firstName, char *lastName, int points, float relativePoints)
{
	Student *newNode = NULL;

	if (!firstName || !lastName || strlen(firstName) <= 0 || strlen(lastName) <= 0) RETURN_NULL(ERR_0);

	newNode = (Student *)malloc(sizeof(Student));
	if (!newNode) RETURN_NULL("Error");

	strncpy(newNode->ime, firstName, NAME_LENGTH);
	strncpy(newNode->prezime, lastName, NAME_LENGTH);
	newNode->broj_bodova = points;
	newNode->relativni_broj_bodova = relativePoints;

	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

Student *InsertToTree(Student *current, Student *toInsert)
{
	if (current == NULL) {
		return toInsert;

	} else if (_stricmp(current->prezime, toInsert->prezime) < 0 ) {
		current->right = InsertToTree(current->right, toInsert);

	} else if (_stricmp(current->prezime, toInsert->prezime) > 0) {
		current->left = InsertToTree(current->left, toInsert);

	} else {
		if (_stricmp(current->ime, toInsert->ime) < 0) {
			current->right = InsertToTree(current->right, toInsert);
		} else if (_stricmp(current->ime, toInsert->ime) > 0) {
			current->left = InsertToTree(current->left, toInsert);
		} else {
			printf("\nStudent with that name and last name alreadi exists");
			free(toInsert);
		}
	}	

	return current;
}

Student *BuildTreeFromFile(char *fileName)
{
	FILE *fp = NULL;
	Student *root = NULL;
	int argTaken = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char firstName[BUFFER_LENGTH] = {'\0'};
	char lastName[BUFFER_LENGTH] = {'\0'};
	int points = 0;

	if (!fileName || strlen(fileName) <= 0) RETURN_NULL(ERR_0);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");


	fp = fopen(fileName, "r");
	if (!fp) RETURN_NULL("Error");

	while(!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%s%d", firstName, lastName, &points);
		if (argTaken != 3) {
			printf("\nFolowing line was not read successfuly: \"%s\"", buffer);
			continue;
		}
		root = InsertToTree(root, CreateNewStudent(firstName, lastName, points, CalcRelativePoints(points, MAX_POINTS)) );
	}

	fclose(fp);
	return root;
}

int PrintTreePostOrder(Student *current)
{
	if (current == NULL) return SUCCESS;

	PrintTreePostOrder(current->left);
	PrintTreePostOrder(current->right);
	printf("%-32s %-32s %-4d %-4.2f\n", current->ime, current->prezime, current->broj_bodova, current->relativni_broj_bodova);

	return SUCCESS;
}

int PrintTreeInOrder(Student *current)
{
	if (current == NULL) return SUCCESS;

	PrintTreePostOrder(current->left);
	PrintTreePostOrder(current->right);
	printf("%-32s %-32s %-4d %-4.2f\n", current->ime, current->prezime, current->broj_bodova, current->relativni_broj_bodova);

	return SUCCESS;
}

int FreeTree(Student *current)
{
	if (current == NULL) return SUCCESS;
	FreeTree(current->left);
	FreeTree(current->right);
	free(current);

	return SUCCESS;
}
