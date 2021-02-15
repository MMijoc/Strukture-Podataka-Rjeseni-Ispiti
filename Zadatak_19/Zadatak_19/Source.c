/*
Zadatak_19
izvanredni ispitni rok 26.9.2017.


Kreirati dvije datoteke i u njih upisati 10 slučajno generiranih brojeva iz opsega od 20-35. Svaku od datoteka pročitati i spremiti u vezanu listu
(kreiraju se dvije vezane liste, npr. L1 i L2). Ispisati ih.
Iz ove dvije vezane liste se kreiraju dvije nove vezane liste koje sadrže:
a) presjek parnih članova listi L1 i L2;
b) uniju neparnih članova listi L1 i L2.

Kod kreiranja listi pod a) i b) se ne smije koristiti malloc, već uzeti postojeće elemente iz listi L1 i L2 i preusmjeriti pokazivače. Ispisati sve četiri liste.
U listama pod a) i b) ne smije biti duplih vrijednosti i vrijednosti moraju bit složene uzlaznim redoslijedom.

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