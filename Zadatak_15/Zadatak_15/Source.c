/*
3 ispitni rok 11.9.2014.


Napisati program koji generira slučajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran sprema se u vezanu listu parnih brojeva i to u padajućem redoslijedu
(od najvećeg prema najmanjem), Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, takoder u padajućem redoslijedu.
Niti jedna vezana lista ne smije sadržavati dva ista elementa.
Unos traje sve dok obje liste ne sadrže 10 clemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste.

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
