/*
Napisati program koji:
a) Iz datoteke „drzave.txt“ čita popis država i njihov ID od pročitanih država izgraditi vezanu listu država na sortirani način od početka prema kraju abecede
(treba raditi sortirani unos, a ne naknadno sortirati).
Uz pokazivač na sljedeću državu struktura od koje se gradi vezana lista mora sadržavati i pokazivač na stablo gradova koji su u toj državi (trenutno NULL) - za 2

b) Iz datoteke „gradovi.txt“ pročitati ime grada i ID države u kojoj se nalazi. Pronaći odgovarajuću državu u gornjoj listi,
te dodati pročitani grad u stablo gradova te države. Za zadanu državu ispisati sve njene gradove po abecedi. – za 5

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

typedef struct _treeNode {
	char cityName[BUFFER_LENGTH];
	int id;

	struct _treeNode *left;
	struct _treeNode *right;
} treeNode;


typedef struct _node {
	char countryName[BUFFER_LENGTH];
	int id;
	treeNode *root;

	struct _node *next;
} node;

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
node *CreateNewNode(char *name, int id);
int SortedInsert(node *listHead, node *toInsert);
int FreeList(node *element);
int PrintList(node *listHead);
int InputCountriesFromFile(node *listHead, char *fileName);

treeNode *CreateNewTreeNode(char *cityName, int id);
treeNode *InsertToBinTree(treeNode *current, treeNode *toInsert);
int FreeBinTree(treeNode *current);
int PrintTreeInOrder(treeNode *root);


node *GetConutry(node *listHead, int id);
int InputCitiesFromFile(node *listHead, char *fileName);

int main()
{
	char drzave[BUFFER_LENGTH] = {"Zad_17_drzave"};
	char gradovi[BUFFER_LENGTH] = {"Zad_17_gradovi"};

	node countries = {"", 0, NULL, NULL};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InputCountriesFromFile(&countries, drzave);
	//PrintList(&countries);

	InputCitiesFromFile(&countries, gradovi);
	PrintList(&countries);

	FreeList(countries.next);
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

node *CreateNewNode(char *name, int id)
{
	node *newNode = NULL;

	if (!name || strlen(name) <= 0) RETURN_NULL(ERR_0);

	newNode = (node *)malloc(sizeof(node));
	if(!newNode) RETURN_NULL("Error");

	strncpy(newNode->countryName, name, BUFFER_LENGTH);
	newNode->id = id;
	newNode->root = NULL;
	newNode->next = NULL;

	return newNode;
}

int SortedInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->countryName, toInsert->countryName) < 0)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int FreeList(node *element)
{
	if (element == NULL) return SUCCESS;

	FreeList(element->next);
	FreeBinTree(element->root);
	free(element);

	return SUCCESS;
}

int PrintList(node *listHead)
{
	node *tmp = NULL;

	if (!listHead) RETURN_FAILURE(ERR_0);

	tmp = listHead->next;
	while (tmp) {
		printf("\n%-32s %-4d", tmp->countryName, tmp->id);
		PrintTreeInOrder(tmp->root);
		printf("\n");
		tmp = tmp->next;
	}

	return SUCCESS;
}

int InputCountriesFromFile(node *listHead, char *fileName)
{
	FILE *fp = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char name[BUFFER_LENGTH] = {'\0'};
	int id = 0;
	int argTaken = 0;

	if (!fileName || strlen(fileName) <= 0) RETURN_FAILURE(ERR_0);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%d", name, &id);
		if (argTaken != 2) {
			printf("\nFollowing line was not read successfully: \"%s\"", buffer);
			continue;
		}
		SortedInsert(listHead, CreateNewNode(name, id));
	}

	fclose(fp);
	return SUCCESS;
}

treeNode *CreateNewTreeNode(char *cityName, int id)
{
	treeNode *newNode = NULL;

	if (!cityName || strlen(cityName) <= 0) RETURN_NULL(ERR_0);

	newNode = (treeNode *)malloc(sizeof(treeNode));
	if(!newNode) RETURN_NULL("Error");

	strncpy(newNode->cityName, cityName, BUFFER_LENGTH);
	newNode->id = id;

	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

treeNode *InsertToBinTree(treeNode *current, treeNode *toInsert)
{
	if (current == NULL) {
		return toInsert;
	
	} else if (_stricmp(current->cityName, toInsert->cityName) > 0) {
		current->left = InsertToBinTree(current->left, toInsert);

	} else if (_stricmp(current->cityName, toInsert->cityName) < 0) {
		current->right = InsertToBinTree(current->right, toInsert);
	
	} else {
		printf("City with the same name alread exists!");
		free(toInsert);
	}

	return current;
}

int FreeBinTree(treeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current);

	return SUCCESS;
}

int PrintTreeInOrder(treeNode *current)
{
	if (current == NULL) return SUCCESS;

	PrintTreeInOrder(current->left);
	printf("\n\t%s", current->cityName);
	PrintTreeInOrder(current->right);

	return SUCCESS;
}

node *GetConutry(node *listHead, int id)
{
	node *tmp = NULL;

	if (!listHead) RETURN_NULL(ERR_0);

	tmp = listHead->next;
	while (tmp) {
		if (tmp->id == id)
			return tmp;
		tmp = tmp->next;
	}
	
	return NULL;
}

int InputCitiesFromFile(node *listHead, char *fileName)
{
	FILE *fp = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char name[BUFFER_LENGTH] = {'\0'};
	int id = 0;
	int argTaken = 0;
	node *tmp = NULL;

	if (!fileName || strlen(fileName) <= 0) RETURN_FAILURE(ERR_0);

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_FAILURE("Error");

	while (!feof(fp)) {
		memset(buffer, '\0', BUFFER_LENGTH);
		memset(name, '\0', BUFFER_LENGTH);
		id = -1;
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s%d", name, &id);
		if (argTaken != 2) {
			printf("\nFollowing line was not read successfully: \"%s\"", buffer);
			continue;
		}
		tmp = GetConutry(listHead, id);
		if (tmp) {
			tmp->root = InsertToBinTree(tmp->root, CreateNewTreeNode(name, id));
		
		} else {
			printf("Unxpected error");
		}
	}

	fclose(fp);
	return SUCCESS;
}
