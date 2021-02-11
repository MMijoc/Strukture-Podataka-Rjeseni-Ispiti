/*
Zadatak_07
izvanredni ispitni rok 22. rujna 2020.


Napisati program koji generira 30 puta dva slučajna broja. Prvi broj je vrijednost i ona je u opsegu od 100 do 200, a drugi je prioritet u opsegu od 1 do 5.
Te podatke se sprema u strukturu od koje se gradi red s prioritetom. Što je veći prioritet to je podatak bliže vrhu (početku) reda. Ispisati red.

Izmijeniti unos na način da podaci unutar istog prioriteta moraju biti sortirani po veličini od najmanjeg prema najvećem (koristiti sortirani unos, a ne sortiranje). 
Ispisati red.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)

int ExecutionFailure(char *message);
void *ExecutionFailureNull(char *message);


int main()
{
	puts("Hello World");

	return SUCCESS;
}

int ExecutionFailure(char *message)
{
	if (errno != 1)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return FAILURE;
}

void *ExecutionFailureNull(char *message)
{
	if (errno != 1)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return NULL;
}
