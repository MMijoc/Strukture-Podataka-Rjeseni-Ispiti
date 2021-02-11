/*
Zadatak_06


Napisati program koji iz datoteke čita šifru artikla (string za koji je potrebno prostor alocirati dinamički) i količinu tog artikla i sprema ih u vezanu listu složenu po šifri.
U programu postoji pet (5) takvih datoteka i za svaku je potrebno kreirati odvojenu vezanu listu. Nadalje u programu treba

a) Kreirati binarno stablo koje se formira prema šiframa artikla s tim da se za šifre koje vec postoje u stablu samo uvećava ukupna količina artikala iz svih vezanih listi - za 2
b) Iz dodatne datoteke u kojoj je uz šifru pohranjen i naziv artikla, pročitati podatke i spremiti ih u odvojenu vezanu listu.
Ponovno ispisati podatke iz binarnog stabla poda a) s tim da se za svaki artikl uz šifru ispiše i njegov naziv - za 3
c) Proširiti binarno stablo na način da svaki čvor ima i pokazivač na vezanu listu osoba koje su taj artikl kupile.
Ime prezime osobe se može izvući iz naziva datoteke. Ispisati binarno stablo sa svim pripadajućim podacima. - za 4 i 5

NAPOMENA: Zatvoriti sve otvorene datoteke, pobrisati svu dinamički alociranu memoriju i mirnim putem prekinuti rad programa. Programski kod napisati kozistentno, uredno te odvojeno u funkcije
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

typedef struct _node {
	char *articeCode;
	int quantity;

	struct _node *next;
} node;

typedef struct _binTreeNode {
	node *article;

	struct _binTreeNode *left;
	struct _binTreeNode *right;
} BinTreeNode;


node *CreateNewNode(char *articleCode, int qunatity);
int SortedInsert(node *listHead, node *toInsert);
int InputFromFile(char *fileName, node *listHead);
int PrintList(node *listHead);
int FreeList(node *node);

BinTreeNode *CreateNewBinTreeNode(node *article);
BinTreeNode *InsertToBinTree(BinTreeNode *current, node *toInsert);
int FreeBinTree(BinTreeNode *root);

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	node lists[5];
	node *tmp = NULL;
	BinTreeNode *root = NULL;
	char fileName[BUFFER_LENGTH] = {'\0'};
	int i;

	//for debugging
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for (i = 0; i < 5; i++)
		lists[i].next = NULL;

	strcpy(fileName, "Zad_6_1");
	InputFromFile(fileName, &lists[0]);
	strcpy(fileName, "Zad_6_2");
	InputFromFile(fileName, &lists[1]);
	strcpy(fileName, "Zad_6_3");
	InputFromFile(fileName, &lists[2]);
	strcpy(fileName, "Zad_6_4");
	InputFromFile(fileName, &lists[3]);
	strcpy(fileName, "Zad_6_5");
	InputFromFile(fileName, &lists[4]);

	for (i = 0; i < 5; i++) {
		PrintList(&lists[i]);
		puts("");
	}

	for (i = 0; i < 5; i++) {
		tmp = lists[i].next;
		while (tmp) {
			root = InsertToBinTree(root, CreateNewNode(tmp->articeCode, tmp->quantity));
			tmp = tmp->next;
		}
	} 

	for (i = 0; i < 5; i++)
		FreeList(lists[i].next);

	FreeBinTree(root);

	return SUCCESS;
}

node *CreateNewNode(char *articleCode, int qunatity)
{
	node *newNode = NULL;

	if (!articleCode || strlen(articleCode) <= 0) return (node *)ExecutionFailureNull("Invalid function paramters");

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) return (node *)ExecutionFailureNull("Error");

	
	newNode->articeCode = (char *)calloc(strlen(articleCode) + 1, sizeof(char));
	if (!newNode->articeCode) return (node *)ExecutionFailureNull("Error");

	strcpy(newNode->articeCode, articleCode);
	newNode->quantity = qunatity;
	newNode->next = NULL;

	return newNode;
}

int SortedInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid arguments");

	tmp = listHead;
	while (tmp->next && strcmp(tmp->next->articeCode, toInsert->articeCode) < 0)
		tmp = tmp->next;

	if (tmp->next && strcmp(tmp->next->articeCode, toInsert->articeCode) == 0) {
		tmp->next->quantity += toInsert->quantity;
		free(toInsert);
	}


	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int InputFromFile(char *fileName, node *listHead)
{
	FILE *fp = NULL;
	int argTaken = 0;
	int quantity = 0;
	char articleCode[BUFFER_LENGTH] = {'\0'};
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!fileName || strlen(fileName) <= 0) return ExecutionFailure("Invalid functions paramters");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");
	fp = fopen(fileName, "r");
	if (!fp) return ExecutionFailure("Error");

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s %d", articleCode, &quantity);
		if (argTaken != 2) {
			printf("Unable to read folowing line: \"%s\"", buffer);
			continue;
		}
		SortedInsert(listHead, CreateNewNode(articleCode, quantity));
	}

	fclose(fp);
	return SUCCESS;
}

int PrintList(node *listHead)
{
	node *tmp = listHead->next;
	while (tmp) {
		printf("\n%s (%d) ",tmp->articeCode, tmp->quantity);
		tmp = tmp->next;
	}
	
	return SUCCESS;
}

int FreeList(node *node)
{
	if (node == NULL) return SUCCESS;

	FreeList(node->next);
	free(node->articeCode);
	free(node);

	return SUCCESS;
}

BinTreeNode *CreateNewBinTreeNode(node *article)
{
	BinTreeNode *newNode = NULL;

	if (!article) return (BinTreeNode *)ExecutionFailureNull("Invalid function paramters");

	newNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	if (!newNode) return (BinTreeNode *)ExecutionFailureNull("Error");

	newNode->article = article;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

BinTreeNode *InsertToBinTree(BinTreeNode *current, node *valuetoInsert)
{
	BinTreeNode *nodeToInsert = NULL;

	if (current == NULL) {
		nodeToInsert = CreateNewBinTreeNode(valuetoInsert);
		if (!nodeToInsert) return NULL;

		return nodeToInsert;

	} else if (strcmp(current->article->articeCode, valuetoInsert->articeCode) > 0) {
		current->left = InsertToBinTree(current->left, valuetoInsert);

	} else if (strcmp(current->article->articeCode, valuetoInsert->articeCode) < 0) {
		current->right = InsertToBinTree(current->right, valuetoInsert);


	} else {
		current->article->quantity += valuetoInsert->quantity;
		free(valuetoInsert->articeCode);
		free(valuetoInsert);
	}

	return current;
}

int FreeBinTree(BinTreeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current->article->articeCode);
	free(current->article);
	free(current);

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
