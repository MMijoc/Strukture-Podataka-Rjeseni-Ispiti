/*Napisati program koji generira 20 sluèajnih brojeva u opsegu od 20 - 50. Pri tome parne brojeve spremiti na poèetak vezane liste od najveæeg prema najmanjem,
a neparne spremati na kraj vezane najmanjeg prema najveæem.
U vezanoj listi ne smije biti ponavljanja elemenata i ne smiju se koristiti nizovi. Ispisati listu.

Složiti elemente vezane liste od najveæeg prema najmanjem, ali se pri tome ne smije koristiti funkcija za sortiranje,
veæ se treba iskoristiti raspored elemenata u vezanoj listi i samo prebacivati neparne elemente na odgovarajuæe mjesto (od na veæeg prema najmanjem). Ispisati listu.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OKAY 0
#define ERR -1
#define LOOP 1
#define DG 20
#define GG 50

struct _broj;
typedef struct _broj* Pozicija;

typedef struct _broj{
	int br;
	Pozicija next;
}Broj;

int Unos(Pozicija h);
int UnosParni(Pozicija h, int br);
int UnosNeparni(Pozicija h, int br);
int ProvjeriPonavljanje(Pozicija h, int br);
int RandomBroj();
int Ispis(Pozicija h);
int BrisiListu(Pozicija h);

int Sortiraj(Pozicija h);


int main() {

	srand(time(NULL));
	int succ;

	Pozicija head = NULL;
	head = (Pozicija)malloc(sizeof(Broj));
	head->next = NULL;

	succ = Unos(head);
	succ = Ispis(head);

	succ = Sortiraj(head);
	succ = Ispis(head);
	
	succ = BrisiListu(head);

	return OKAY;
}

int Unos(Pozicija h)
{
	int succ;
	int r_br;
	int i = 0;

	while (i != 20) {
		r_br = RandomBroj();
		succ = ProvjeriPonavljanje(h, r_br);
		if (OKAY == succ) {
			i++;
		}
		else {
			continue;
		}
		if (r_br % 2 == 0) {
			UnosParni(h, r_br);
		}
		else {
			UnosNeparni(h, r_br);
		}


	}
}

int UnosParni(Pozicija h, int br) {

	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(Broj));
	
	while (h->next != NULL && h->next->br > br && h->next->br % 2 == 0) {
		h = h->next;
	}

	p->br = br;
	p->next = h->next;
	h->next = p;

	return OKAY;
}

int UnosNeparni(Pozicija h, int br)
{
	Pozicija p = NULL;
	p = (Pozicija)malloc(sizeof(Broj));

	while (h->next != NULL && h->next->br % 2 == 0) {
		h = h->next;
	}
	while (h->next != NULL && h->next->br < br) {
		h = h->next;
	}

	p->br = br;
	p->next = h->next;
	h->next = p;

	return OKAY;
}

int ProvjeriPonavljanje(Pozicija h, int br)
{

	if (h->next == NULL) {
		return OKAY;
	}
	else {
		while (h->next != NULL && h->br != br) {
			h = h->next;
		}

		if (h->br == br)
			return ERR;
		else
			return OKAY;
	}
}

int RandomBroj()
{
	return rand() % (GG - DG + 1) + DG;
}

int Ispis(Pozicija h)
{
	h = h->next;

	while (h != NULL)
	{
		printf("%d ", h->br);
		h = h->next;
	}

	printf("\n");

	return OKAY;
}

int BrisiListu(Pozicija h)
{
	Pozicija temp = NULL;

	while (h->next != NULL) {
		temp = h->next;
		h->next = temp->next;
		free(temp);
	}

	return OKAY;
}

int Sortiraj(Pozicija h) {

	Broj neparniBr = { 0, NULL };
	Pozicija temp = NULL;
	Pozicija nextCvor = NULL;

	temp = h;

	while (temp->next != NULL && temp->next->br % 2 == 0) {
		temp = temp->next;
	}

	neparniBr.next = temp->next;
	temp->next = NULL;

	temp = neparniBr.next;

	while (temp != NULL) {
		nextCvor = temp->next;
		NapraviCvor(h, temp);
		temp = nextCvor;
	}

	return OKAY;
}

int NapraviCvor(Pozicija h, Pozicija temp)
{

	while (h->next && h->next->br > temp->br)
		h = h->next;

	temp->next = h->next;
	h->next = temp;

	return OKAY;
}
