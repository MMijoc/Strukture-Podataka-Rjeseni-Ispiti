/*
15.02.2018. Grupa 2


Napisati program koji iz datoteke „text.txt“ čita zadani tekst. Od pročitanih riječi se gradi binarno stablo pretraživanja,
s tim da ukoliko se pronađe riječ koja se već nalazi u stablu potrebno ju je dodati u vezanu listu istih riječi za određeni čvor.
Ispisati stablo. Za odabranu riječ ispitat koliko se puta ponavlja.

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
#define MAX_WORD_LENGTH 128
#define BUFFER_LENGTH 1024

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _word {
	char word[MAX_WORD_LENGTH];

	struct _word *next;
} Word;

typedef struct _treeNode {
	char word[MAX_WORD_LENGTH];

	Word duplicatesListHead;
	struct _treeNode *left;
	struct _treeNode *right;
} TreeNode;


void PrintError(char *message);
char *GetFileContent(char *fileName);
int ReplaceChars(char *source, char *charsToRemove, char replaceBy);
TreeNode *CreateNewTreeNode(char *word);
TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert);
int BuildTreeFromString(TreeNode **root, char *source);
TreeNode *FindWord(TreeNode *current, char *wordToFind);
int PrintInOrder(TreeNode *current);
int FreeBinTree(TreeNode *current);
Word *CreateNewWord(char *word);
int InsertAtHead(Word *listHead, Word *toInsert);
int PrintList(Word *listHead);
int FreeList(Word *element);
int CountDuplicates(TreeNode *node);


int main()
{
	char fileName[BUFFER_LENGTH] = {"Zad_18"};
	char *fileContent = NULL;
	TreeNode *root = NULL;
	char buffer[BUFFER_LENGTH] = {'\0'};
	char wordToSearch[MAX_WORD_LENGTH] = {'\0'};
	TreeNode *tmp = NULL;
	int argTaken = 0;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;
	ReplaceChars(fileContent, ".?!,;:\"-_", ' ');

	BuildTreeFromString(&root, fileContent);
	PrintInOrder(root);

	printf("\n\nEnter word to count duplicates or \"Enter\" to exit");
	while (TRUE) {
		printf("\nEnter word: ");
		fgets(buffer, BUFFER_LENGTH, stdin);
		argTaken = sscanf(buffer, "%s", wordToSearch);
		if (argTaken != 1)
			break;

		tmp = FindWord(root, wordToSearch);
		if (tmp)
			printf("Word \"%s\" is repeated %d times", tmp->word, CountDuplicates(tmp));
		else
			printf("Word \"%s\" was not found in the text!", wordToSearch);

	}

	FreeBinTree(root);
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

int ReplaceChars(char *source, char *charsToRemove, char replaceBy)
{
	int i = 0, j = 0;
	int length = 0, nChars = 0;

	if (!source || !charsToRemove) RETURN_FAILURE("Invalid parameters");

	length = strlen(source);
	nChars = strlen(charsToRemove);

	for (i = 0; i < length; i++)
		for (j = 0; j < nChars; j++)
			if (source[i] == charsToRemove[j])
				source[i] = replaceBy;

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
	newNode->duplicatesListHead.next = NULL;

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
		InsertAtHead(&(current->duplicatesListHead), CreateNewWord(toInsert->word));
		free(toInsert);
	}

	return current;
}

int BuildTreeFromString(TreeNode **root, char *source)
{
	int argTaken = 1, offset = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!source) RETURN_FAILURE("Invalid arguments");

	while (argTaken > 0) {
		argTaken = sscanf(source, " %s%n", buffer, &offset);
		if (argTaken == 1)
			*root = InsertToBinTree(*root, CreateNewTreeNode(buffer));

		source += offset;
	}

	return SUCCESS;
}

TreeNode *FindWord(TreeNode *current, char *wordToFind)
{
	if (current) {
		if (_strnicmp(current->word, wordToFind, MAX_WORD_LENGTH) == 0) {
			return current;

		} else if (_strnicmp(current->word, wordToFind, MAX_WORD_LENGTH) < 0) {
			return FindWord(current->right, wordToFind);

		} else /*if (_strnicmp(current->word, wordToFind, MAX_WORD_LENGTH) > 0)*/ {
			return FindWord(current->left, wordToFind);

		}
	}

	return NULL;
}

int PrintInOrder(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	PrintInOrder(current->left);
	printf("\n%s", current->word);
	PrintList(&(current->duplicatesListHead));
	PrintInOrder(current->right);

	return SUCCESS;
}

int FreeBinTree(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	FreeList(current->duplicatesListHead.next);
	free(current);

	return SUCCESS;
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

int InsertAtHead(Word *listHead, Word *toInsert)
{
	if (!listHead || !toInsert) RETURN_FAILURE("Invalid function arguments");

	toInsert->next = listHead->next;
	listHead->next = toInsert;

	return SUCCESS;
}

int PrintList(Word *listHead)
{
	Word *tmp = NULL;

	tmp = listHead->next;
	while (tmp) {
		printf(" -> %s", tmp->word);
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

int CountDuplicates(TreeNode *node)
{
	int count = 1;
	Word *tmp = NULL;

	if (!node) return FAILURE;

	tmp = node->duplicatesListHead.next;
	while (tmp) {
		count++;
		tmp = tmp->next;
	}

	return count;
}
