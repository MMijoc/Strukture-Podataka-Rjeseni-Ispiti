/*
Zadatak_10
2 ispitni rok 27.2.2014.


Napisati program koji iz datoteke čita dio teksta, riječ po riječi unosi u binarno stablo pretraživanja (maksimalna duljina riječi 1024 znaka).
Ispisati binarno stablo na „inorder" način.

Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve riječi koje počinju samoglasnikom, a u drugoj sve riječi koje počinju suglasnikom.
Riječi zapisane u datotekama moraju biti sortirane po abecedi.

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

typedef struct _binNode {
	char word[BUFFER_LENGTH];

	struct _binNode *left;
	struct _binNode *right;

} BinNode;

typedef struct _node {
	char word[BUFFER_LENGTH];

	struct _node *next;
} Node;


#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE; } while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL; } while(0);

void PrintError(char *message);
BinNode *CreateBinNode(char *word);
BinNode *InsertToBinTree(BinNode *current, BinNode *toInsert);
int IsVowel(char c);
int FreeBinTree(BinNode *current);
int PrintInOrder(BinNode *current, FILE *out);
char *GetFileContent(char *fileName);
int BuildTreeFromString(BinNode *root, char *source);
int PrintTreeToFiles(BinNode *root);
int ReplaceChars(char *source, char *charsToRemove, char replaceBy);

int main()
{
	BinNode Root = {"", NULL, NULL};
	char *content = NULL;
	char fileName[BUFFER_LENGTH] = {"Zad_10"};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	content = GetFileContent(fileName);

	printf("%s\n\n", content);

	BuildTreeFromString(&Root, content);
	PrintInOrder(Root.left, stdout);
	PrintInOrder(Root.right, stdout);

	PrintTreeToFiles(&Root);

	FreeBinTree(Root.left);
	FreeBinTree(Root.right);
	free(content);
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

BinNode *CreateBinNode(char *word)
{
	BinNode *newNode = NULL;

	if (!word || strlen(word) <= 0) RETURN_NULL("Invalid paramaters");

	newNode = (BinNode *)malloc(sizeof(BinNode));
	if (!newNode) RETURN_NULL("Error");

	strncpy(newNode->word, word, BUFFER_LENGTH);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

BinNode *InsertToBinTree(BinNode *current, BinNode *toInsert)
{
	if (current == NULL) {
		return toInsert;
	
	} else if (_stricmp(current->word, toInsert->word) < 0) {
		current->right = InsertToBinTree(current->right, toInsert);
	
	} else if (_stricmp(current->word, toInsert->word) > 0) {
		current->left = InsertToBinTree(current->left, toInsert);
	
	} else {
		free(toInsert);
		return current;
	}

	return current;
}

int IsVowel(char c)
{
	switch(c) {
	case 'A':
	case 'a':
	case 'e':
	case 'E':
	case 'i':
	case 'I':
	case 'o':
	case 'O':
	case 'u':
	case 'U':
		return TRUE;
	}

	if ((c > 'A' && c <= 'Z') || (c > 'a' && c <= 'z'))
		return FALSE;

	return FAILURE;
}

int FreeBinTree(BinNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current);

	return SUCCESS;
}

int PrintInOrder(BinNode *current,  FILE *out)
{
	if (current == NULL) return SUCCESS;

	PrintInOrder(current->left, out);
	fprintf(out, "%s\n", current->word);
	PrintInOrder(current->right, out);

	return SUCCESS;
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

int BuildTreeFromString(BinNode *root, char *source)
{
	int argTaken = 1, offset = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!source) RETURN_FAILURE("Invalid arguments");
	ReplaceChars(source, ".?!,;:\"-_", ' ');

	while (argTaken > 0) {
	
		argTaken = sscanf(source, " %s%n", buffer, &offset);
		if (argTaken == 1) {
			if (IsVowel(buffer[0]) == TRUE)
				root->left = InsertToBinTree(root->left, CreateBinNode(buffer));
			else
				root->right = InsertToBinTree(root->right, CreateBinNode(buffer));

		}
		source += offset;

	}

	return SUCCESS;
}

int PrintTreeToFiles(BinNode *root)
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	fp1 = fopen("vowel.txt", "w");
	fp2 = fopen("consonant.txt", "w");
	if (!fp1 || !fp2) RETURN_FAILURE("Error");


	PrintInOrder(root->left, fp1);
	PrintInOrder(root->right, fp2);

	fclose(fp1);
	fclose(fp2);
	return SUCCESS;
}

int ReplaceChars(char *source, char *charsToRemove, char replaceBy)
{
	int i = 0, j = 0;
	int length = 0, nChars = 0;

	if (!source || !charsToRemove) RETURN_FAILURE("Invalid paramters");

	length = strlen(source);
	nChars = strlen(charsToRemove);

	for (i = 0; i < length; i++)
		for (j = 0; j < nChars; j++)
			if (source[i] == charsToRemove[j])
				source[i] = replaceBy;
	
	return SUCCESS;
}
