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
broj:			5	0	6	2	4	1	3	7	5
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
