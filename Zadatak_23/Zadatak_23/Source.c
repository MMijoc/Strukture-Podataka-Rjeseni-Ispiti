/*
Zadatak_23
27.02.2013. Grupa 1


Napisati program kojim se
a) Slučajnim uzorkom generira 100 brojeva iz opsega od 300 do 700, te ih sprema u binarno stablo pretraživanja. Zatim ispišemo to stablo u preorder načinu ispisa.
b) Iz generiranog stabla pretraživanja izbrisati sve elemente koji su zapisani u proizvoljno definiranoj datoteci.

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
#define N 100

#define LB 300
#define UB 700

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _treeNode {
	int value;

	struct _treeNode *left;
	struct _treeNode *right;
} TreeNode;

void PrintError(char *message);
char *GetFileContent(char *fileName);
TreeNode *CreateNewTreeNode(int value);
TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert);
TreeNode *FindMinValue(TreeNode *node);
TreeNode *DeleteNode(TreeNode *node, int value);
int PrintPreorder(TreeNode *current);
int FreeBinTree(TreeNode *current);
int GetRandomNumber(int min, int max);


int main()
{
	int i = 0;
	int tmp = 0;
	TreeNode *root = NULL;
	char fileName[BUFFER_LENGTH] = {"Zad_23"};
	char *fileContent = NULL, *source = NULL;
	int argTaken = 1, offset = 0, value;


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	printf("Random numbers generated: ");
	for (i = 0; i < N; i++) {
		tmp = GetRandomNumber(LB, UB);
		printf("%d ", tmp);
		root = InsertToBinTree(root, CreateNewTreeNode(tmp));
	}

	printf("\n\nPreorder print:");
	PrintPreorder(root);

	source = fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;

	while (argTaken > 0) {
		argTaken = sscanf(source, " %d%n", &value, &offset);
		if (argTaken == 1)
			root = DeleteNode(root, value);

		source += offset;
	}
	free(fileContent);

	printf("\n\nPreorder print:");
	PrintPreorder(root);

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


TreeNode *CreateNewTreeNode(int value)
{
	TreeNode *newNode = NULL;

	newNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (!newNode) RETURN_NULL("Error");

	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert)
{
	if (current == NULL) {
		return toInsert;

	} else if (current->value < toInsert->value) {
		current->right = InsertToBinTree(current->right, toInsert);

	} else if (current->value > toInsert->value) {
		current->left = InsertToBinTree(current->left, toInsert);

	} else {
		free(toInsert);
	}

	return current;
}

TreeNode *FindMinValue(TreeNode *current)
{
	if (NULL == current) return NULL;
	while (current->left)
		current = current->left;

	return current;
}

TreeNode *DeleteNode(TreeNode *current, int value)
{
	if (current == NULL) {
		printf("\nElement with the value '%d' does not exist in this tree", value);
		return current;
	} else if (value > current->value) {
		current->right = DeleteNode(current->right, value);
	} else if (value < current->value) {
		current->left = DeleteNode(current->left, value);
	} else {
		TreeNode* tmp = NULL;

		if (current->left && current->right) {
			tmp = FindMinValue(current->right);
			current->value = tmp->value;
			current->right = DeleteNode(current->right, tmp->value);

		} else {
			tmp = current;
			if (current->right == NULL)
				current = current->left;
			else
				current = current->right;

			free(tmp);
		}

	}

	return current;
}

int PrintPreorder(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	printf("\n%d", current->value);
	PrintPreorder(current->left);
	PrintPreorder(current->right);

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

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}
