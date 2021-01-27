/*
Zadatak_01:
1. ispitni rok 13. 2. 2020


Napisati program koji iz datoteke (ime se unosi u programu) Čita podatke u binarno stablo za pretaživanje u kojeme se sortiraju po prezimenu, 
pa zatim po imenu osobe. Binarno stablo za pretaživanje je definirano strukturom:

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPosition left;
	PersonPosition right;
} Person;

Pri tome Word word je član strukture Person koja predstavlja glavu vezane liste, te je definirana kao:

struct _word;
typedef struct _word *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Word;

Podaci u datoteci su organizirani na način da prve dvije riječi u retku predstavljaju ime i prezime, dok ostatak rijči u retku predstavljaju rečenicu te osobe.
Rečenicu je potrebno za svaku osobu upisati u vezanu listu Word i to:
•vezana lista se formira u proizvoljnom rasporedu - za ocjenu 2;
•lista se formira tako da rečenica ima smisla - za ocjenu 5.
Program ispisuje osobe i njihove rečenice in order.

Na kraju programa potrebno je osloboditi svu dinamički rezerviranu memoriju.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0

#define MAX_NAME 128
#define BUFFER_LENGTH 1024

struct _word;
typedef struct _word *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Word;

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPosition left;
	PersonPosition right;
} Person;

Word *CreateWord(char *word);
int InsertWordAtHead(Word *head, char *word);
int PrintList(Word *head);
Person *CreatePerson(char *firstName, char *lastName);
Person *BuildTree(char *fileName);
Person *InsertPerson(Person *currentNode, Person *nodeToInsert);
int Insert(Person **root, char *buffer);
int PrintTreeInOrder(Person *current);
int DeleteBinTree(Person *node);
int DeleteWordList(Word *head);

int main()
{
	char fileName[BUFFER_LENGTH] = {'\0'};
	char buffer[BUFFER_LENGTH] = {'\0'};
	Person *root = NULL;
	int argTaken = 0;

	while (argTaken != 1) {
		printf("Please enter the name of the file you want to read: ");
		fgets(buffer, BUFFER_LENGTH, stdin);
		argTaken = sscanf(buffer, "%s", fileName);
	}

	root = BuildTree(fileName);
	PrintTreeInOrder(root);
	puts("");

	DeleteBinTree(root);
	return SUCCESS;
}

Word *CreateWord(char *word)
{
	Word *newWord = NULL;

	if (word == NULL || strlen(word) == 0) {
		perror("Invalid function argument");
		return NULL;
	}

	newWord = (Word *)malloc(sizeof(Word));
	if (newWord == NULL) {
		perror("");
		return NULL;
	}

	strncpy(newWord->word, word, MAX_NAME - 1);
	newWord->next = NULL;

	return newWord;
}

int InsertWordAtHead(Word *head, char *word)
{
	Word *newWord = NULL;

	newWord = CreateWord(word);
	if (!newWord) return FAILURE;

	newWord->next = head->next;
	head->next = newWord;

	return SUCCESS;
}

int PrintList(Word *head)
{
	Word *tmp = head->next;
	while (tmp) {
		printf(" %s", tmp->word);
		tmp = tmp->next;
	}

	return SUCCESS;
}

Person *CreatePerson(char *firstName, char *lastName)
{
	Person *newPerson = NULL;

	if ( firstName == NULL || lastName == NULL || strlen(firstName) == 0 || strlen(lastName) == 0 ) {
		printf("Invalid function argument");
		return NULL;
	}

	newPerson = (Person *)malloc(sizeof(Person));
	if (NULL == newPerson) {
		perror("");
		return NULL;
	}
	
	strncpy(newPerson->firstName, firstName, MAX_NAME);
	strncpy(newPerson->lastName, lastName, MAX_NAME);
	strncpy(newPerson->word.word, "HEAD", MAX_NAME);
	newPerson->word.next = NULL;

	newPerson->left = NULL;
	newPerson->right = NULL;

	return newPerson;
}

Person *BuildTree(char *fileName)
{
	Person *root = NULL;
	FILE *fp = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (fileName == NULL || strlen(fileName) == 0) {
		perror("Invalid function argument");
		return NULL;
	}

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "rb");
	if (!fp) {
		perror("ERROR");
		return NULL;
	}
	
	while (fgets(buffer, BUFFER_LENGTH, fp)) {
		Insert(&root, buffer);
		memset(buffer, '\0', BUFFER_LENGTH);
	}

	fclose(fp);
	return root;
}

int Insert(Person **root, char *buffer)
{
	int n = 0;
	int argTaken = 0;
	char firstName[MAX_NAME] = {'\0'};
	char lastName[MAX_NAME] = {'\0'};
	char word[BUFFER_LENGTH] = {'\0'};
	Person *newPerson = NULL;

	argTaken = sscanf(buffer, "%s %s %n", firstName, lastName, &n);
	if (argTaken != 2) return FAILURE;
	buffer += n;

	newPerson = CreatePerson(firstName, lastName);
	if (!newPerson) return FAILURE;

	while (argTaken > 0) {
		argTaken = sscanf(buffer, "%s %n", word, &n);
		if (argTaken == 1) {
			InsertWordAtHead(&newPerson->word, word);
			buffer += n;
		}
	}

	*root = InsertPerson(*root, newPerson);
	return SUCCESS;
}

Person *InsertPerson(Person *currentNode, Person *nodeToInsert)
{
	if (NULL == currentNode) {
		return nodeToInsert;

	} else if (_stricmp(currentNode->lastName, nodeToInsert->lastName) > 0) {
		currentNode->left = InsertPerson(currentNode->left, nodeToInsert);

	} else if (_stricmp(currentNode->lastName, nodeToInsert->lastName) < 0) {
		currentNode->right = InsertPerson(currentNode->right, nodeToInsert);
	
	} else {
	
		if (_stricmp(currentNode->firstName, nodeToInsert->firstName) > 0) {
			currentNode->left = InsertPerson(currentNode->left, nodeToInsert);

		} else if (_stricmp(currentNode->firstName, nodeToInsert->firstName) < 0) {
			currentNode->right = InsertPerson(currentNode->right, nodeToInsert);

		} else {
			printf("Person with the sam name and last name already exits");
			free(nodeToInsert);
		}

	}

	return currentNode;
}

int PrintTreeInOrder(Person *current)
{
	if (current == NULL) return SUCCESS;
	
	PrintTreeInOrder(current->left);
	printf("\n%-16s %-16s", current->firstName, current->lastName);
	PrintList(&current->word);
	PrintTreeInOrder(current->right);
	return SUCCESS;
}

int DeleteBinTree(Person *node)
{
	if (NULL == node) return SUCCESS;

	DeleteBinTree(node->left);
	DeleteBinTree(node->right);
	DeleteWordList(&node->word);
	free(node);

	return SUCCESS;
}

int DeleteWordList(Word *head)
{
	Word *toFree = NULL;
	Word *tmp = head->next;

	while(tmp) {
		toFree = tmp;
		tmp = tmp->next;
		free(toFree);
	}

	head->next = NULL;
	return SUCCESS;
}
