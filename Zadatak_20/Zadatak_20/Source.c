/*
31. kolovoza 2017.


Napisati program koji generira 15 slučajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu listu,
po redoslijedu generiranja,a ne sortirano. U listi ne smije biti duplih vrijednosti.

a) Potrebno je pronaći minimalnu i maksimalnu vrijednost, te iz njih izračunati srednju vrijednost ((min+max)/2) i
nakon toga sve vrijednosti koje su veće od srednje prebaciti na kraj liste.
Ispisati minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu.

b) Pronaći vrijednost u listi koja je najbliža srednjoj vrijednosti i nju postaviti kao root element binarnog stabla za pretraživanje.
Nakon toga sve elemente iz liste prebaciti u stablo i gotovo stablo ispisati na level order način.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0
#define BUFFER_LENGTH 1024

#define N 15
#define LB 100
#define UB 120


#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _node {
	int value;

	struct _node *next;
} node;

typedef struct _treeNode {
	int value;

	struct _treeNode *left;
	struct _treeNode *right;
} TreeNode;

void PrintError(char *message);
int GetUniqueRand(int min, int max, int arr[], int arrSize);
int QShuffleCompare(const void *x, const void *y);
node *CreateNewNode(int value);
int InsertAt(node *position, node *toInsert);
node *FindTail(node *listHead);
int PrintList(node *head);
int FreeList(node *element);
int FindMinMax(node *listHead, int *min, int *max);
node *Unlink(node *previous, node **current);
int FindClosestToAverage(node *listHead);
TreeNode *CreateNewTreeNode(int value);
TreeNode *InsertToBinTree(TreeNode *current, TreeNode *toInsert);
int BuildTreeFromList(TreeNode **root, node *listHead);
int PrintLevelOrder(TreeNode *root);
int PrintGivenLevel(TreeNode *root, int level);
int GetBinTreeHeight(TreeNode *node);
int FreeBinTree(TreeNode *current);

int main()
{
	int uniqArr[N];
	int i = 0;
	int min = 0, max = 0;
	float avg = 0;
	node list = {0, NULL};
	node *curr = NULL, *prev = NULL;
	node *tail = NULL, *end = NULL;
	node *tmp = NULL;
	TreeNode *root = NULL;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//srand(time(NULL));
	GetUniqueRand(LB, UB, uniqArr, N);

	printf("Random numbers generated:\n");
	for (i = 0; i < N; i++) {
		printf("%d ", uniqArr[i]);
		InsertAt(&list, CreateNewNode(uniqArr[i]));
	}
	printf("\n\nNumbers inserted at head of the list in generated order:\n");
	PrintList(&list);

	FindMinMax(&list, &min, &max);
	avg = (float)(min + max) / 2;

	prev = &list;
	curr = prev->next;
	end = tail = FindTail(&list);
	while (curr != end) {
		if (curr->value > avg) {
			InsertAt(tail, Unlink(prev, &curr));
			tail = tail->next;
		} else {
			prev = curr;
			curr = curr->next;
		}	
	}

	printf("\nMinimum: \t\t%d\nMaximum: \t\t%d\nAverage: \t\t%.3f\nClosest to average: \t%d\n", min, max, avg, FindClosestToAverage(&list));
	printf("\nList after reordering: \n");
	PrintList(&list);

	BuildTreeFromList(&root, &list);
	printf("\n\nlevel order print:");
	PrintLevelOrder(root);

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

int GetUniqueRand(int min, int max, int arr[], int arrSize)
{
	int *tmpArr = NULL;
	int i = 0;
	int span = abs(max - min);

	if (min > max || span < arrSize) RETURN_FAILURE("Invalid bounds for random numbers");

	tmpArr = (int *)malloc(span * sizeof(int));
	if (!tmpArr) RETURN_FAILURE("Error");

	for (i = 0; i < span; i++)
		tmpArr[i] = min + i;

	qsort(tmpArr, span, sizeof(int), QShuffleCompare);
	for (i = 0; i < arrSize; i++)
		arr[i] = tmpArr[i];

	free(tmpArr);
	return SUCCESS;
}

int QShuffleCompare(const void *x, const void *y)
{
	return rand() % 2 ? 1 : -1;
}

node *CreateNewNode(int value)
{
	node *tmp = NULL;

	tmp = (node *)malloc(sizeof(node));
	if (!tmp) RETURN_NULL("Error");

	tmp->value = value;
	tmp->next = NULL;

	return tmp;
}

int InsertAt(node *position, node *toInsert)
{
	toInsert->next = position->next;
	position->next = toInsert;

	return SUCCESS;
}

node *FindTail(node *listHead)
{
	node *tmp = NULL;

	if (!listHead) RETURN_NULL("FindTail: Invalid arguments!");

	tmp = listHead;
	while (tmp->next)
		tmp = tmp->next;

	return tmp;
}

int PrintList(node *head)
{
	node *tmp = head->next;

	if (!head) RETURN_FAILURE("PrintList: Invalid function arguments!");
	if (!tmp) {
		printf("List is empty!\n");
		return FAILURE;
	}

	while (tmp) {
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}
	puts("");

	return SUCCESS;
}

int FreeList(node *element)
{
	if (element == NULL) return SUCCESS;

	FreeList(element->next);
	free(element);

	return SUCCESS;
}

int FindMinMax(node *listHead, int *min, int *max)
{
	node *tmp = NULL;

	if (!listHead || !min || !max) RETURN_FAILURE("FindMinMax: Invalid arguments!");

	tmp = listHead->next;
	*min = tmp->value;
	*max = tmp->value;
	while (tmp) {
		if (tmp->value < *min)
			*min = tmp->value;
		if (tmp->value > *max)
			*max = tmp->value;
		tmp = tmp->next;	
	}

	return SUCCESS;
}

node *Unlink(node *previous, node **current)
{
	node *tmp = *current;

	previous->next = (*current)->next;
	(*current) = (*current)->next;

	tmp->next = NULL;
	return tmp;
}

int FindClosestToAverage(node *listHead)
{
	node* tmp = NULL;
	int lower = 0, upper = 0;
	float closestTo = 0;

	FindMinMax(listHead, &lower, &upper);
	closestTo = (float)(lower + upper) / 2;
	tmp = listHead->next;
	while (tmp) {
		if (tmp->value <= closestTo && tmp->value >= lower) {
			lower = tmp->value;
		}
		if (tmp->value >= closestTo && tmp->value <= upper) {
			upper = tmp->value;
		}

		tmp = tmp->next;
	}

	return (closestTo - lower <= upper - closestTo) ? lower : upper;
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

int BuildTreeFromList(TreeNode **root, node *listHead)
{
	node *tmp = NULL;

	if (!listHead) RETURN_FAILURE("BuildTreeFromList: Invalid arguments!");

	*root = CreateNewTreeNode(FindClosestToAverage(listHead));
	tmp = listHead->next;
	while(tmp) {
		*root = InsertToBinTree(*root, CreateNewTreeNode(tmp->value));
		tmp = tmp->next;
	}

	return SUCCESS;
}

int PrintLevelOrder(TreeNode *root)
{
	int height = 0;
	int i = 0;

	height = GetBinTreeHeight(root);
	for (i = 1; i <= height; i++) {
		printf("\n");
		PrintGivenLevel(root, i);
	}

	return SUCCESS;
}

int PrintGivenLevel(TreeNode *root, int level)
{
	if (root == NULL) return SUCCESS;

	if (level == 1) {
		printf("%d ", root->value);

	} else if (level > 1) {
		PrintGivenLevel(root->left, level-1);
		PrintGivenLevel(root->right, level-1);

	}

	return SUCCESS;
}

int GetBinTreeHeight(TreeNode *node)
{
	int lHeight = 0;
	int rHeight = 0;

	if (node == NULL) return FAILURE;

	lHeight = GetBinTreeHeight(node->left);
	rHeight = GetBinTreeHeight(node->right);

	return (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
}

int FreeBinTree(TreeNode *current)
{
	if (current == NULL) return SUCCESS;

	FreeBinTree(current->left);
	FreeBinTree(current->right);
	free(current);

	return SUCCESS;
}
