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

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);


void PrintError(char *message);


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