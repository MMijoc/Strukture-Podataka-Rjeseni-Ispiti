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