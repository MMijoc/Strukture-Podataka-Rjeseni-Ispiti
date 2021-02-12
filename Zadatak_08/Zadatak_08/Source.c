/*
Zadatak_08
1 ispitni rok 13.2.2014.


Napisati program koji čita iz datoteke dio teksta, te kreira binarno stablo pretraživanja.
Binarno stablo se kreira na način da se u njega upisuju sve različite riječi iz teksta koji je zapisan u datoteci s pripadajućim duljinama unesene riječi.

struct _Cvor {
	char *rijec;
	int length;
	struct _Cvor *Left;
	struct _Cvor *Right;
};

Potrebno je izračunati prosječnu duljinu svake riječi zapisane u binarnom stablu,

Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one riječi koje su dulje od prosječne duljine svih riječi, te ispisati tu vezanu listu.

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
#define FALIURE (-1)
#define BUFFER_LENGTH 1024

struct _Cvor {
	char *rijec;
	int length;
	struct _Cvor *Left;
	struct _Cvor *Right;
};
typedef struct _Cvor Cvor;

typedef struct _word {
	char *rijec;

	struct _word *next;
} Word;


int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);
Cvor *CreateNewTreeNode(char *word);
Cvor *InsertToTree(Cvor *root, Cvor *toInsert);
int FreeBinaryTree(Cvor *current);
int FreeBinNode(Cvor *toFree);
int InputFromFile(Cvor **root, char *fileName);
int CountNodesInTree(Cvor *current);
int GetTotalLength(Cvor *current);
float GetAverageWordLength(Cvor *current);
Word *CreateNewWord(char *word);
int InsertToList(Word *listHead, Word *toInsert);
int GetLongerThanAverageWords(Word *listHead, Cvor *root, float avg);
int PrintList(Word *listHead);
int FreeList(Word *listHead);

int main()
{
	Cvor *root = NULL;
	Word wordList = {'\0', NULL};
	char fileName[BUFFER_LENGTH] = {"Zad_8"};
	float avg = 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InputFromFile(&root, fileName);

	avg = GetAverageWordLength(root);
	printf("Average word length is: %f\n", avg);

	printf("\nFolowing words are longer than an average word:");
	GetLongerThanAverageWords(&wordList, root, avg);
	PrintList(&wordList);
	
	puts("");
	FreeBinaryTree(root);
	FreeList(wordList.next);
	return SUCCESS;
}

int ExecutionFailure(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return FALIURE;
}

void *ExecutionFailureNull(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return NULL;
}

Cvor *CreateNewTreeNode(char *word)
{
	Cvor *newNode = NULL;

	if (!word || strlen(word) <= 0) return (Cvor *)ExecutionFailureNull("Invalid function arguments");

	newNode = (Cvor *)malloc(sizeof(Cvor));
	if (!newNode) return (Cvor *)ExecutionFailureNull("Error");

	newNode->rijec = (char *)calloc(strlen(word) + 1, sizeof(char));
	if (!newNode->rijec) return (Cvor *)ExecutionFailureNull("Error");

	strcpy(newNode->rijec, word);
	newNode->length = strlen(word);
	newNode->Left = NULL;
	newNode->Right = NULL;

	return newNode;
}

Cvor *InsertToTree(Cvor *current, Cvor *toInsert)
{
	if (current == NULL) {
		return toInsert;
	
	} else if (_stricmp(current->rijec, toInsert->rijec) < 0) {
		current->Left = InsertToTree(current->Left, toInsert);

	} else if(_stricmp(current->rijec, toInsert->rijec) > 0) {
		current->Right = InsertToTree(current->Right, toInsert);
	
	} else {
		free(toInsert->rijec);
		free(toInsert);
	}

	return current;
}

int FreeBinaryTree(Cvor *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinaryTree(current->Left);
	FreeBinaryTree(current->Right);
	FreeBinNode(current);
	
	return SUCCESS;
}

int FreeBinNode(Cvor *toFree)
{
	free(toFree->rijec);
	free(toFree);
	return SUCCESS;
}

int InputFromFile(Cvor **root, char *fileName)
{
	FILE *fp = NULL;
	size_t length = 0;
	char *content = NULL;
	char *source = NULL;
	int argTaken = 0, n = 0;
	char buffer[BUFFER_LENGTH];

	if (!fileName || strlen(fileName) <= 0) return ExecutionFailure("Invalid parameters");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "rb");
	if (!fp) return ExecutionFailure("Error");

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	content = (char *)calloc(length + 1, sizeof(char));
	if (!content) return ExecutionFailure("Error");

	fread(content, sizeof(char), length,  fp);
	fclose(fp);
	source = content;
	while (TRUE) {
		argTaken = sscanf(source, " %s%n", buffer, &n);
		if (argTaken != 1) break;
		strtok(buffer, ",.!?*';");
		*root = InsertToTree(*root, CreateNewTreeNode(buffer));
		source += n;
	}

	free(content);
	return SUCCESS;
}

int CountNodesInTree(Cvor *current)
{
	int n = 1;

	if (current == NULL) return 0;

	n += CountNodesInTree(current->Left);
	n += CountNodesInTree(current->Right);

	return n;
}

int GetTotalLength(Cvor *current)
{
	int n = 0;
	if (current == NULL) return 0;

	n = current->length;
	n += GetTotalLength(current->Left);
	n += GetTotalLength(current->Right);

	return n;
}

float GetAverageWordLength(Cvor *current)
{
	int nodeCount = 0;
	int totalLnegth = 0;

	nodeCount = CountNodesInTree(current);
	totalLnegth = GetTotalLength(current);

	if (nodeCount == 0) return 0;

	return (float)totalLnegth / nodeCount;
}

Word *CreateNewWord(char *word)
{
	Word *newWord = NULL;

	if (!word ||strlen(word) <= 0) return (Word *)ExecutionFailureNull("Invalid function arguments");

	newWord = (Word *)malloc(sizeof(Word));
	if (!newWord) return (Word *)ExecutionFailureNull("Error");

	newWord->rijec = (char *)calloc(strlen(word) + 1, sizeof(char));
	if (!newWord->rijec) return (Word *)ExecutionFailureNull("Error");
	
	strcpy(newWord->rijec, word);
	newWord->next = NULL;

	return newWord;
}

int InsertToList(Word *listHead, Word *toInsert)
{
	Word *tmp = NULL;

	if (!listHead || !toInsert) return ExecutionFailure("Invalid function arguments");

	tmp = listHead;

	while (tmp->next && strlen(tmp->next->rijec) < strlen(toInsert->rijec))
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int GetLongerThanAverageWords(Word *listHead, Cvor *root, float avg)
{
	if (root == NULL) return SUCCESS;

	GetLongerThanAverageWords(listHead, root->Left, avg);
	GetLongerThanAverageWords(listHead, root->Right, avg);
	if (strlen(root->rijec) > avg)
		InsertToList(listHead, CreateNewWord(root->rijec));
	
	return SUCCESS;
}

int PrintList(Word *listHead)
{
	Word *tmp = listHead->next;

	while (tmp) {
		printf("\n\t%s", tmp->rijec);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeList(Word *word)
{
	if (word == NULL) return SUCCESS;

	FreeList(word->next);
	free(word->rijec);
	free(word);

	return SUCCESS;
}