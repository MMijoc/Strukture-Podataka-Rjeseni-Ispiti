/*
3 ispitni rok 28.8.2014.


Napisati program koji generira 20 slučajnih brojeva iz opsega 100 - 150 i njih spremiti u vezanu listu i svakom od njih dodijeliti redni broj od 0-19.

a) Nakon toga treba generirati pet slučajnih brojeva iz opsega 0-19 (voditi računa da se ne pojavi isti broj više puta) i
elemente gornje liste s tim rednim brojem postaviti na početak liste. Ispisati te brojeve te novu listu s rednim brojevima.

Npr. za listu:
broj:			0	1	2	3	4	5	6	7	8
Element:		125	134	145	121	103	111	106	149	...
Ako se izgeneriraju redni brojevi 4, 2, 6, 0, 5 prvo se na početak dodaje element s rednim brojem 4, pa s rednim brojem 2, pa s 6... Nova lista na kraju izgleda:
Npr. za listu:
broj:			5	0	6	2	4	1	3	7	8
Element:		111	125	106	145	103	134	121	149	...

b) Izmijeniti gornji zadatak tako da iz postojeće liste nova formira na način da se elementi iz postojeće liste prebace po redoslijedu generiranja rednih brojeva,
tj. za gornji primjer nova bi lista izgledala:
Npr. za listu:
broj:			4	2	6	0	5	1	3	7	8
Element:		103	145	106	125	111	134	121	149	...
Ispisati te brojeve te novu listu s rednim brojevima.
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

#define N 19
#define M 5

typedef struct _node {
	int value;
	int orderNum;

	struct _node *next;
} node;


#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);
#define ERR_0 "Invalid function arguments"

void PrintError(char *message);
int GetRandomNumber(int min, int max);
node *CreateNewNode(int value, int orderNum);
int InsertAtHead(node *listHead, node *toInsert);
int InsertAtTail(node *listHead, node *toInsert);
node *FindTail(node *listHead);
int GetUniqueRand(int min, int max, int arr[], int arrSize);
int QShuffleComp(const void *dummy1, const void *dummy2);
int PrintList(node *listHead);
int FindNumber(node *listHead, int orderNum);

int main()
{
	int i = 0, j = 0;
	node list = {0, 0, NULL};
	node list1 = {0, 0, NULL};
	node *tmp = NULL;
	int randArray[10];
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	for(i = N; i >= 0; i--)
		InsertAtHead(&list, CreateNewNode(GetRandomNumber(100, 150), i));
	
	printf("Initial list:\n");
	PrintList(&list);

	printf("\nUnique random numbers generated: ");
	GetUniqueRand(0, 20, randArray, M);
	for(i = 0; i < M; i++)
		printf("%d ", randArray[i]);


	tmp = list.next;
	while (tmp) {
		for (i = 0; i < M; i++) {
			if (randArray[i] == tmp->orderNum) {
				tmp = tmp->next;
				continue;
			}
		}

		InsertAtTail(&list1, CreateNewNode(tmp->value, tmp->orderNum));
		tmp = tmp->next;
	}

	for (i = 0; i < M; i++) {
		InsertAtHead(&list1, CreateNewNode(FindNumber(&list, randArray[i]), randArray[i]));
	}
	printf("\nChanged list:\n");
	PrintList(&list1);


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

int GetRandomNumber(int min, int max)
{
	return min + rand() % (max - min);
}

node *CreateNewNode(int value, int orderNum)
{
	node *newNode = NULL;

	newNode = (node *)malloc(sizeof(node));
	if (!newNode) RETURN_NULL("Error");

	newNode->value = value;
	newNode->orderNum = orderNum;
	newNode->next = NULL;

	return newNode;	
}

int InsertAtHead(node *listHead, node *toInsert)
{
	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);

	toInsert->next = listHead->next;
	listHead->next = toInsert;

	return SUCCESS;
}

int InsertAtTail(node *listHead, node *toInsert)
{
	node *tail = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE(ERR_0);
	tail = FindTail(listHead);
	tail->next = toInsert;

	return SUCCESS;
}

node *FindTail(node *listHead)
{
	node *tmp = listHead;

	while (tmp->next)
		tmp = tmp->next;

	return tmp;
}

int FindNumber(node *listHead, int orderNum)
{
	node *tmp = listHead->next;

	while (tmp) {
		if (tmp->orderNum == orderNum)
			return tmp->value;
		tmp = tmp->next;
	}

	return INT_MIN;
}

int GetUniqueRand(int min, int max, int arr[], int arrSize)
{

	int *tmpArr = NULL;
	int i = 0;

	if (min > max || abs(max - min) < arrSize) RETURN_FAILURE("Invalid bunds for random numbers");

	tmpArr = (int *)malloc((max - min) * sizeof(int));
	if (!tmpArr) RETURN_FAILURE("Error");

	for (i = 0; i < arrSize; i++)
		tmpArr[i] = min + i;

	qsort(tmpArr, arrSize, sizeof(int), QShuffleComp);
	for (i = 0; i < arrSize; i++) {
		arr[i] = tmpArr[i];
	}

	free(tmpArr);
	return SUCCESS;
}

int QShuffleComp(const void *dummy1, const void *dummy2)
{
	return rand() % 2 ? 1 : -1;
}

int PrintList(node *listHead)
{
	node *tmp = NULL;

	tmp = listHead->next;
	while (tmp) {
		printf("%d   %d\n", tmp->value, tmp->orderNum);
		tmp = tmp->next;
	}

	return SUCCESS;
}