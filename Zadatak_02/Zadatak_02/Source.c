/*
Zadatak_02
2. ispitni rok 27.2.2020.


Zadana je datoteka sa popisom studenata, njihovim ocjenama i pripadajućim  ECTS-ovima.
Svaki redak datoteke sadrži ime, prezime, ocjenu
Napisati program koji učitava podatke u hash tablicu dužine 23 i pri tome:
	* Svaki element hash tablice označava glavu vezane liste.
	* Ulazni podaci iz datoteke se raspršuju na način da se zbroje ASCII vrijednosti prva tri slova
	  imena i prezimena.
	* Svaka vezana lista je sortirana po prezimenu, zatim po imenu studenata
	* Ukoliko se pojavi student s već postojećim imenom i prezimenom ne unosi se ponovo
	* Čvor vezane liste je definiran sljedećim poljima:

				struct _student;
				typedef struct _student *StudentPosition;
				typedef struct _student{
					char firstName[MAX_NAME];
					char lastName[MAX_NAME];
					int total;
					int totalEcts;
					StudentPosition next;
				} Student;

Varijabla total je suma umnožaka ocjena s pripadajućim ECTS-om, a totalEcts je suma svih ECTS-ova.

Npr. ukoliko su ulazni podaci za studenta Ivu Matića:
(ime)   (prezime)   (ocjena)    (ECTS)
---------------------------------------------------------
---------------------------------------------------------
Ivo	Matića          4         7
Ivo     Matića          5         2
...
Tada čvor vezane liste treba sadržavati podatke:
{
	firstName: Ivo
	lastName: Matić
	totalEcts: 38
	totalEcts: 9
	next: ...
}

Za ocjenu 2:
	* Iz hash tablice upisati sve studente u datoteku zajedno s njihovim relevantnim prosjekom,
	* Pobrisati svu dinamički rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 3:
	* Iz hash tablice upisati u datoteku samo one studente (zajedno s njihovim relevantnim prosjekom)
	  koji ispunjavaju dva uvjeta za stipendiju:
		* Relativni prosjek veći ili jednak 3.5
		* Broj položenih ECTS-ova veći ili jednak 55
	* Pobrisati svu dinamički rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 5:
	* Studente iz koji zadovoljavaju uvjete za stipendiju u datoteku upisati od najvećeg prema
	  najmanjem relativnom prosjeku.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0

int main()
{
	printf("Hello world\n");


	return SUCCESS;
}