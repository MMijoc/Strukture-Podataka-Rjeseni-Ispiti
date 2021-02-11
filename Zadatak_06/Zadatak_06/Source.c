/*
Zadatak_06


Napisati program koji iz datoteke čita šifru artikla (string za koji je potrebno prostor alocirati dinamički) i količinu tog artikla i sprema ih u vezanu listu složenu po šifri.
U programu postoji pet (5) takvih datoteka i za svaku je potrebno kreirati odvojenu vezanu listu. Nadalje u programu treba

a) Kreirati binarno stablo koje se formira prema šiframa artikla s tim da se za šifre koje vec postoje u stablu samo uvećava ukupna količina artikala iz svih vezanih listi - za 2
b) Iz dodatne datoteke u kojoj je uz šifru pohranjen i naziv artikla, pročitati podatke i spremiti ih u odvojenu vezanu listu.
Ponovno ispisati podatke iz binarnog stabla poda a) s tim da se za svaki artikl uz šifru ispiše i njegov naziv - za 3
c) Proširiti binarno stablo na način da svaki čvor ima i pokazivač na vezanu listu osoba koje su taj artikl kupile.
Ime prezime osobe se može izvući iz naziva datoteke. Ispisati binarno stablo sa svim pripadajućim podacima. - za 4 i 5

NAPOMENA: Zatvoriti sve otvorene datoteke, pobrisati svu dinamički alociranu memoriju i mirnim putem prekinuti rad programa. Programski kod napisati kozistentno, uredno te odvojeno u funkcije
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FAILURE (-1)
#define BUFFER_LENGTH 1024

int main()
{


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	puts("Hello world");

	return SUCCESS;
}