/*
Napisati program koji:
a) Iz datoteke „drzave.txt“ čita popis država i njihov ID od pročitanih država izgraditi vezanu listu država na sortirani način od početka prema kraju abecede
(treba raditi sortirani unos, a ne naknadno sortirati).
Uz pokazivač na sljedeću državu struktura od koje se gradi vezana lista mora sadržavati i pokazivač na stablo gradova koji su u toj državi (trenutno NULL) - za 2

b) Iz datoteke „gradovi.txt“ pročitati ime grada i ID države u kojoj se nalazi. Pronaći odgovarajuću državu u gornjoj listi,
te dodati pročitani grad u stablo gradova te države. Za zadanu državu ispisati sve njene gradove po abecedi. – za 5

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