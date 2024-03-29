﻿/*
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
	char *articleCode;
	int quantity;

	struct _node *next;
} node;

typedef struct _article {
	char *code;
	char *name;

	struct _article *next;
} Article;

typedef struct _person {
	char fullName[BUFFER_LENGTH];

	struct _person *next;
} Person;

typedef struct _binTreeNode {
	node *article;
	Person person;

	struct _binTreeNode *left;
	struct _binTreeNode *right;
} BinTreeNode;


node *CreateNewNode(char *articleCode, int quantity);
int SortedInsert(node *listHead, node *toInsert);
int InputFromFile(char *fileName, node *listHead);
int PrintList(node *listHead);
int FreeList(node *node);
BinTreeNode *CreateNewBinTreeNode(node *article, Person *person);
BinTreeNode *InsertToBinTree(BinTreeNode *current, node *valueToInsert, Person *personToInsert);
int FreeBinTree(BinTreeNode *root);
int PrintArticlesInOrder(BinTreeNode *current, Article *listHead);
int InputArticleNamesFromFile(char *fileName, Article *listHead);
int ArticleSortedInsert(Article *listHead, Article *toInsert);
int FreeArticleList(Article *node);
char *FindArticleName(Article *listHead, char *code);
Person *CreateNewPerson(char *fullName);
int InsertPerson(Person *listHead, Person *toInsert);
int PrintPersonList(Person *listHead);
int FreePersonsList(Person *person);
int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	int i = 0;
	node lists[5];
	node *tmp = NULL;
	BinTreeNode *root = NULL;
	Article articleList = {'\0', '\0', NULL};
	char articleNamesFile[BUFFER_LENGTH] = {"Zad_6_names"};
	char fileNames[5][BUFFER_LENGTH] = {"Zad_6_1", "Zad_6_2", "Zad_6_3", "Zad_6_4" ,"Zad_6_5"};


	//for debugging memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	for (i = 0; i < 5; i++)
		lists[i].next = NULL;
	for (i = 0; i < 5; i++)
		InputFromFile(fileNames[i], &lists[i]);

	for (i = 0; i < 5; i++) {
		printf("\nList from file: \"%s\"", fileNames[i]);
		PrintList(&lists[i]);
		puts("");
	}

	for (i = 0; i < 5; i++) {
		tmp = lists[i].next;
		while (tmp) {
			root = InsertToBinTree(root, CreateNewNode(tmp->articleCode, tmp->quantity), CreateNewPerson(fileNames[i]));
			tmp = tmp->next;
		}
	}
	InputArticleNamesFromFile(articleNamesFile, &articleList);

	printf("\n\nBinary tree printed In Order in format {article code} {article name} {(quantity)}"
		"\n\t->{list of persons who have that article -> name of the file in which that article code was found}");
	PrintArticlesInOrder(root, &articleList);
	puts("");


	for (i = 0; i < 5; i++)
		FreeList(lists[i].next);
	FreeArticleList(articleList.next);
	FreeBinTree(root);

	return SUCCESS;
}

node *CreateNewNode(char *articleCode, int quantity)
{
	node *newNode = NULL;

	if (!articleCode || strlen(articleCode) <= 0) return (node *)ExecutionFailureNull("Invalid function paramters");

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) return (node *)ExecutionFailureNull("Error");

	
	newNode->articleCode = (char *)calloc(strlen(articleCode) + 1, sizeof(char));
	if (!newNode->articleCode) return (node *)ExecutionFailureNull("Error");

	strcpy(newNode->articleCode, articleCode);
	newNode->quantity = quantity;
	newNode->next = NULL;

	return newNode;
}

int SortedInsert(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid arguments");

	tmp = listHead;
	while (tmp->next && strcmp(tmp->next->articleCode, toInsert->articleCode) < 0)
		tmp = tmp->next;

	if (tmp->next && strcmp(tmp->next->articleCode, toInsert->articleCode) == 0) {
		tmp->next->quantity += toInsert->quantity;
		free(toInsert);
		return SUCCESS;
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
		printf("\n%s (%d) ",tmp->articleCode, tmp->quantity);
		tmp = tmp->next;
	}
	
	return SUCCESS;
}

int FreeList(node *node)
{
	if (node == NULL) return SUCCESS;

	FreeList(node->next);
	free(node->articleCode);
	free(node);

	return SUCCESS;
}

BinTreeNode *CreateNewBinTreeNode(node *article, Person *person)
{
	BinTreeNode *newNode = NULL;

	if (!article) return (BinTreeNode *)ExecutionFailureNull("Invalid function paramters");

	newNode = (BinTreeNode *)malloc(sizeof(BinTreeNode));
	if (!newNode) return (BinTreeNode *)ExecutionFailureNull("Error");

	newNode->article = article;
	newNode->person.next = NULL;
	InsertPerson(&(newNode->person), person);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

BinTreeNode *InsertToBinTree(BinTreeNode *current, node *valueToInsert, Person *personToInsert)
{
	BinTreeNode *nodeToInsert = NULL;

	if (current == NULL) {
		nodeToInsert = CreateNewBinTreeNode(valueToInsert, personToInsert);
		if (!nodeToInsert) return NULL;

		return nodeToInsert;

	} else if (strcmp(current->article->articleCode, valueToInsert->articleCode) > 0) {
		current->left = InsertToBinTree(current->left, valueToInsert, personToInsert);

	} else if (strcmp(current->article->articleCode, valueToInsert->articleCode) < 0) {
		current->right = InsertToBinTree(current->right, valueToInsert, personToInsert);


	} else {
		current->article->quantity += valueToInsert->quantity;
		InsertPerson(&current->person, personToInsert);
		free(valueToInsert->articleCode);
		free(valueToInsert);
	}

	return current;
}

int FreeBinTree(BinTreeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current->article->articleCode);
	FreePersonsList(current->person.next);
	free(current->article);
	free(current);

	return SUCCESS;
}

int PrintArticlesInOrder(BinTreeNode *current, Article *listHead)
{
	char *tmp = NULL;

	if (current == NULL) return SUCCESS;

	PrintArticlesInOrder(current->left, listHead);
	tmp = FindArticleName(listHead, current->article->articleCode);
	if (tmp) {
		printf("\n%s %s (%d)\n\t", current->article->articleCode, tmp, current->article->quantity);
		PrintPersonList(&(current->person));
	}
	PrintArticlesInOrder(current->right, listHead);

	return SUCCESS;
}

Article *CreateNewArticle(char *code, char *name)
{
	Article *newArticle = NULL;

	if (!code || !name || strlen(code) <= 0 || strlen(name) <= 0 ) return (Article *)ExecutionFailureNull("Invalid function paramters");

	newArticle = (Article *)malloc(sizeof(Article));
	if (!newArticle) return (Article *)ExecutionFailureNull("Error");

	
	newArticle->code = (char *)calloc(strlen(code) + 1, sizeof(char));
	newArticle->name = (char *)calloc(strlen(name) + 1, sizeof(char));
	if (!newArticle->code || !newArticle->name) return (Article *)ExecutionFailureNull("Error");

	strcpy(newArticle->code, code);
	strcpy(newArticle->name, name);
	newArticle->next = NULL;

	return newArticle;
}

int InputArticleNamesFromFile(char *fileName, Article *listHead)
{
	FILE *fp = NULL;
	int argTaken = 0;
	char articleCode[BUFFER_LENGTH] = {'\0'};
	char articleName[BUFFER_LENGTH] = {'\0'};
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!fileName || strlen(fileName) <= 0) return ExecutionFailure("Invalid functions paramters");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");
	fp = fopen(fileName, "r");
	if (!fp) return ExecutionFailure("Error");

	while (!feof(fp)) {
		fgets(buffer, BUFFER_LENGTH, fp);
		argTaken = sscanf(buffer, "%s %s", articleCode, articleName);
		if (argTaken != 2) {
			printf("Unable to read folowing line: \"%s\"", buffer);
			continue;
		}
		ArticleSortedInsert(listHead, CreateNewArticle(articleCode, articleName));
	}

	fclose(fp);
	return SUCCESS;
}

int ArticleSortedInsert(Article *listHead, Article *toInsert)
{
	Article *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid arguments");

	tmp = listHead;
	while (tmp->next && strcmp(tmp->next->name, toInsert->name) < 0)
		tmp = tmp->next;

	if (tmp->next && strcmp(tmp->next->name, toInsert->name) == 0) {
		free(toInsert);
		return SUCCESS;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

char *FindArticleName(Article *listHead, char *code)
{
	Article *tmp = listHead->next;

	while (tmp) {
		if (strcmp(tmp->code, code) == 0)
			return tmp->name;
		tmp = tmp->next;
	}

	return NULL;
}

int FreeArticleList(Article *node)
{
	if (node == NULL) return SUCCESS;

	FreeArticleList(node->next);
	free(node->code);
	free(node->name);
	free(node);

	return SUCCESS;
}

Person *CreateNewPerson(char *fullName)
{
	Person *newPerson = NULL;

	if (!fullName || strlen(fullName) <= 0) return (Person *)ExecutionFailureNull("Invalid function paramters");

	newPerson = (Person *)malloc(sizeof(Person));
	if (!newPerson) return (Person *)ExecutionFailureNull("Error");

	strcpy(newPerson->fullName, fullName);
	newPerson->next = NULL;

	return newPerson;
}

int InsertPerson(Person *listHead, Person *toInsert)
{
	Person *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid arguments");

	tmp = listHead;
	while (tmp->next && strcmp(tmp->next->fullName, toInsert->fullName) < 0)
		tmp = tmp->next;

	if (tmp->next && strcmp(tmp->next->fullName, toInsert->fullName) == 0) {
		free(toInsert);
		return SUCCESS;
	}

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int PrintPersonList(Person *listHead)
{
	Person *tmp = listHead->next;
	while (tmp) {
		printf("-> %s ",tmp->fullName);
		tmp = tmp->next;
	}
	
	return SUCCESS;
}

int FreePersonsList(Person *person)
{
	if (person == NULL) return SUCCESS;

	FreePersonsList(person->next);
	free(person);

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
