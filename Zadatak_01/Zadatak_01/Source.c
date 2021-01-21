/*
Zad_01:
1. ispitni rok 13. 2. 2020


Napisati program koji iz datoteke (ime se unosi u programu) Cita podatke u binarno stablo za pretazivanje u kojeme se sortiraju po prezimenu, 
pa zatim po imenu osobe. Binarno stablo za pretazivanje je definirano strukturom:


struct person;
typedef struct _person *Person Position;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPostion left;
	PersonPosition right;
} Person;

Pri tome Word word je clan strukture Person koja predstavlja glavu vezane liste, te je definirana kao:

struct _word;
typedef struct *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Person;

Podaci u datoteci su organizirani na nacin da prve dvije rijeci u retku predstavljaju ime prezime, dok ostatak rijci u retku predstavljaju recenicu te osobe.
Recenicu je potrebno za svaku osobu upisati u vezanu listu Word i to:
•vezana lista se formira u proizvoljnom rasporedu- za ocjenu 2;
•lista se formira tako da rečenica ima smisla - za ocjenu S.
Program ispisuje osobe i njihove recenice in order.

Na kraju programa potrebno je osloboditi svu dinamički rezerviranu memoriju.
*/
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE (-1)

#define TRUE 1
#define FALSE 0

int main()
{
	printf("Hello World\n");

	system("pause");
	return SUCCESS;
}