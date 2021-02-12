/*
Zadatak_09
1 ispitni rok 13.2.2014.


Napisati program koji iz datoteke čita dio teksta, riječ po riječi unosi ih u red s prioritetom
(maksimalna duljina riječi 1024 znaka, prioritet=1 => riječ počinje samoglasnikom, prioritet=2 => riječ počinje suglasnikom;).
Riječi u redu moraju biti sortirane po prioritetu.

Iz tako kreiranog reda kreirati dvije datoteke, u prvoj će se nalaziti riječi sa prioritetom=1, a u drugoj riječi s prioritetom=2; 
s tim da su te riječi u datoteci zapisane sortirane po abecedi.

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


typedef struct _node {
	char word[BUFFER_LENGTH];
	int priority;

	struct _node *next;
} node;

#define RETURN_FAILURE(message) do { PrintError(message); return FAILURE; } while(0);
#define RETURN_NULL(message) do { PrintError(message); return NULL; } while(0);

void PrintError(char *message);
node *CreateNewNode(char *word);
int GetPriority(char c);
char *GetFileContent(char *fileName);
int BuildQueueFromString(node *qHead, char *source);
int Enqueue(node *qHead, node *toEnqueue);
int Dequeue(node *qHead, node *toDequeue);
int PrintList(node *qHead);
int PrintToFile(char *fileName, node *qHead);
int PrintListToFile(char *fileName, node *qHead);
int SortedInput(node *listHead, node *toInsert);
int FreeList(node *current);
int PrintToFileByPrority(node *qHead);
int RemoveInterpunction(char *source, char *charsToRemove);

int main()
{
	int a = 0;
	node Queue = {"", 0, NULL};
	node tmp = {"", 0, NULL};
	char fileName[BUFFER_LENGTH] = {"Zad_9"};
	char *fileContent = NULL;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;


	BuildQueueFromString(&Queue, fileContent);
	PrintToFileByPrority(&Queue);
	
	free(fileContent);
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

node *CreateNewNode(char *word)
{
	node *newNode = NULL;

	if (!word || strlen(word) <= 0) RETURN_NULL("Invalid arguments");

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) RETURN_NULL("Error");

	strcpy(newNode->word, word);
	newNode->priority = GetPriority(*word);
	newNode->next = NULL;

	return newNode;
}

int GetPriority(char c)
{
	switch (c) {
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
		return 1;
	default:
		return 2;
	}
}

char *GetFileContent(char *fileName)
{
	FILE *fp = NULL;
	size_t length = 0;
	char *content = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!fileName || strlen(fileName) <= 0) RETURN_NULL("Error");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_NULL("Error");

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	content = (char *)calloc(length + 1, sizeof(char));
	if (!content) RETURN_NULL("Error");

	fread(content, sizeof(char), length, fp);

	fclose(fp);
	return content;
}

int BuildQueueFromString(node *qHead, char *source)
{
	int argTaken = 0, offset = 0;
	char buffer[BUFFER_LENGTH];

	RemoveInterpunction(source, ".,;:*?!()\"");

	while(TRUE) {
		argTaken = sscanf(source, "%s%n", buffer, &offset);
		if (argTaken != 1) return FAILURE;
		Enqueue(qHead, CreateNewNode(buffer));
		source += offset;

	}

	return SUCCESS;
}

int Enqueue(node *qHead, node *toEnqueue)
{
	node *tmp = NULL;

	if (!qHead || !toEnqueue) RETURN_FAILURE("Invalid arguments");

	tmp = qHead;
	while (tmp->next && tmp->next->priority < toEnqueue->priority)
		tmp = tmp->next;

	toEnqueue->next = tmp->next;
	tmp->next = toEnqueue;

	return SUCCESS;
}

int Dequeue(node *qHead, node *toDequeue)
{
	node *toFree = qHead->next;

	if (!qHead) RETURN_FAILURE("Invalid arguments");
	if (qHead->next == NULL) return FAILURE;

	qHead->next = toFree->next;
	toDequeue->priority = toFree->priority;
	strcpy(toDequeue->word, toFree->word);

	free(toFree);

	return SUCCESS;
}

int PrintList(node *qHead)
{
	node *tmp = qHead->next;

	while (tmp) {
		printf("\n%s %d", tmp->word, tmp->priority);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintListToFile(char *fileName, node *qHead)
{
	FILE *fp = NULL;
	node *tmp = qHead->next;
	

	fp = fopen(fileName, "w");
	if (!fp) RETURN_FAILURE("error");

	while (tmp) {
		fprintf(fp, "%s %d\n", tmp->word, tmp->priority);
		tmp = tmp->next;
	}

	fclose(fp);
	return SUCCESS;
}

int PrintToFileByPrority(node *qHead)
{
	node tmpList1 = {"", 0, NULL};
	node tmpList2 = {"", 0, NULL};
	node tmp = {"", 0, NULL};

	while (Dequeue(qHead, &tmp) != FAILURE) {
		if (tmp.priority == 1)
			SortedInput(&tmpList1, CreateNewNode(tmp.word));
		else
			SortedInput(&tmpList2, CreateNewNode(tmp.word));
	}

	PrintListToFile("Priority_1.txt", &tmpList1);
	PrintListToFile("Priority_2.txt", &tmpList2);

	FreeList(tmpList1.next);
	FreeList(tmpList2.next);

	return SUCCESS;
}

int SortedInput(node *listHead, node *toInsert)
{
	node *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE("Invalid arguments");

	tmp = listHead;
	while (tmp->next && _stricmp(tmp->next->word, toInsert->word) < 0)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int FreeList(node *current)
{
	if (current == NULL) return SUCCESS;

	FreeList(current->next);
	free(current);

	return SUCCESS;
}

int RemoveInterpunction(char *source, char *charsToRemove)
{
	int i = 0, j = 0;
	int length = 0, nChars = 0;

	length = strlen(source);
	nChars = strlen(charsToRemove);
	for (i = 0; i < length; i++)
		for (j = 0; j <nChars; j++)
			if (source[i] == charsToRemove[j])
				source[i] = ' ';

	return SUCCESS;
}
