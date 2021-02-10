#define _CRT_SECURE_NO_WARNING
/*
Zadatak_05
3 ispitni rok - dodatni 10.9.2020


Napisati program koji generira 30 slučajnih brojeve u opsegu od 120-150.
Sve brojeve spremiti u vezanu listu tako da redoslijed brojeva u listi odgovara redoslijedu generiranja brojeva.
Ispisati listu i nakon toga izbrisati iz liste sve vrijednosti koje se ponavljaju uz uvjet da u čvoru koji ostane u listi se zapiše koliko je ukupno bilo tih vrijednosti.
Ispisati novu vezanu listu kao i broj ponavljanja svakog čvora.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//for debuging memory leaks
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024

int main()
{
	//for debuging memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	printf("Hello World\n");

	return SUCCESS;
}