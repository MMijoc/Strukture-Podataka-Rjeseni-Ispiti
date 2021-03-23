/*
12.02.2013. Grupa 1


Napisati program koji
a) Iz datoteke čita stringove (mogu biti imena i mora ih biti min. 10) i stvara vezanu listu elemenata sortiranih po abecedi.
b) Elemente iz datoteke ubaciti u binarno stablo i ispisati ga na inorder način.
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
#define MAX_WORD_LENGTH 128

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _word {
	char word[MAX_WORD_LENGTH];

	struct _word *next;
} Word;

typedef struct _treeNode {
	char word[MAX_WORD_LENGTH];

	struct _treeNode *left;
	struct _treeNode *right;
} TreeNode;


void PrintError(char *message);
char *GetFileContent(char *fileName);
Word *CreateNewWord(char *word);
int SortedInsert(Word *listHead, Word *toInsert);
int BuildListFromString(Word *listHead, char *source);
int PrintList(Word *listHead);
int FreeList(Word *element);
TreeNode *CreateNewTreeNode(char *word);
TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert);
int BuildTreeFromList(TreeNode **root, Word *listHead);
int PrintInOrder(TreeNode *current);
int FreeBinTree(TreeNode *current);


int main()
{
	char fileName[BUFFER_LENGTH] = {"Zad_21"};
	char *fileContent = NULL;
	Word list = {"", NULL};
	TreeNode *root = NULL;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;
	
	printf("List:\n");
	BuildListFromString(&list, fileContent);
	PrintList(&list);

	printf("\n\nBinary tree printed in order:\n");
	BuildTreeFromList(&root, &list);
	PrintInOrder(root);

	free(fileContent);
	FreeList(list.next);
	FreeBinTree(root);

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

char *GetFileContent(char *fileName)
{
	FILE *fp = NULL;
	size_t length = 0;
	char *content = NULL;

	if (!fileName || strlen(fileName) <= 0) RETURN_NULL("Invalid arguments");

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

Word *CreateNewWord(char *word)
{
	Word *newWord = NULL;

	if (!word || strlen(word) <= 0) RETURN_NULL("Invalid function arguments");

	newWord = (Word *)malloc(sizeof(Word));
	if (!newWord) RETURN_NULL("Error");

	strncpy(newWord->word, word, MAX_WORD_LENGTH);
	newWord->next = NULL;

	return newWord;
}

int SortedInsert(Word *listHead, Word *toInsert)
{
	Word *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE("SortedInsert: Invalid arguments!");

	tmp = listHead;
	while (tmp->next && _strnicmp(tmp->next->word, toInsert->word, MAX_WORD_LENGTH) < 0)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int BuildListFromString(Word *listHead, char *source)
{
	int argTaken = 1, offset = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!source) RETURN_FAILURE("BuildListFromString: Invalid arguments!");

	while (argTaken > 0) {
		argTaken = sscanf(source, " %s%n", buffer, &offset);
		if (argTaken == 1)
			SortedInsert(listHead, CreateNewWord(buffer));

		source += offset;
	}

	return SUCCESS;
}

int PrintList(Word *listHead)
{
	Word *tmp = NULL;

	tmp = listHead->next;
	while (tmp) {
		printf("\t%s\n", tmp->word);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeList(Word *element)
{
	if (element == NULL) return SUCCESS;

	FreeList(element->next);
	free(element);

	return SUCCESS;
}

TreeNode *CreateNewTreeNode(char *word)
{
	TreeNode *newNode = NULL;

	if (!word || strlen(word) <= 0) RETURN_NULL("Invalid parameters");

	newNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (!newNode) RETURN_NULL("Error");

	strncpy(newNode->word, word, MAX_WORD_LENGTH);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert)
{
	if (current == NULL) {
		return toInsert;

	} else if (_strnicmp(current->word, toInsert->word, MAX_WORD_LENGTH) < 0) {
		current->right = InsertToBinTree(current->right, toInsert);

	} else if (_strnicmp(current->word, toInsert->word, MAX_WORD_LENGTH) > 0) {
		current->left = InsertToBinTree(current->left, toInsert);

	} else {
		free(toInsert);
	}

	return current;
}

int BuildTreeFromList(TreeNode **root, Word *listHead)
{
	Word *tmp = NULL;

	if (!listHead) RETURN_FAILURE("BuildTreeFromList: Invalid arguments!");

	tmp = listHead->next;
	while(tmp) {
		*root = InsertToBinTree(*root, CreateNewTreeNode(tmp->word));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintInOrder(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	PrintInOrder(current->left);
	printf("\n%s", current->word);
	PrintInOrder(current->right);

	return SUCCESS;
}

int FreeBinTree(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current);

	return SUCCESS;
}
