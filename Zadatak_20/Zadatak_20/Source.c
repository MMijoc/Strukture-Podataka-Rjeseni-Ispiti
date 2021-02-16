/*
31. kolovoza 2017.


Napisati program koji generira 15 slučajnih brojeva u opsegu od 100 - 120 i sprema ih u vezanu listu, po redoslijedu generiranja,a ne sortirano. U listi ne smije biti duplih vrijednosti.
a) Potrebno je pronaći minimalnu i maksimalnu vrijednost, te iz njih izračunati srednju vrijednost ((min+max)/2) i
nakon toga sve vrijednosti koje su veće od srednje prebaciti na kraj liste. Ispisati minimalnu, maksimalnu i srednju vrijednost kao i rezultantnu listu.
b) Pronaći vrijednost u listi koja je najbliža srednjoj vrijednosti i nju postaviti kao root element binarnog stabla za pretraživanje.
Nakon toga sve elemente iz liste prebaciti u stablo i gotovo stablo ispisati na level order način.

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

#define N 15

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);


void PrintError(char *message);
int GetUniqueRand(int min, int max, int arr[], int arrSize);
int QShuffleCompare(const void *x, const void *y);

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	puts("Hello world");

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