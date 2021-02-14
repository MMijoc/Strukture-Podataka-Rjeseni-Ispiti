/*Zadatak_02
2. ispitni rok 27.2.2020.


Zadana je datoteka sa popisom studenata, njihovim ocjenama i pripadajuæim  ECTS-ovima.
Svaki redak datoteke sadrži ime, prezime, ocjenu
Napisati program koji uèitava podatke u hash tablicu dužine 23 i pri tome:
	* Svaki element hash tablice oznaèava glavu vezane liste.
	* Ulazni podaci iz datoteke se raspršuju na naèin da se zbroje ASCII vrijednosti prva tri slova
	  imena i prezimena.
	* Svaka vezana lista je sortirana po prezimenu, zatim po imenu studenata
	* Ukoliko se pojavi student s veæ postojeæim imenom i prezimenom ne unosi se ponovo
	* Èvor vezane liste je definiran sljedeæim poljima:

				struct _student;
				typedef struct _student *StudentPosition;
				typedef struct _student{
					char firstName[MAX_NAME];
					char lastName[MAX_NAME];
					int total;
					int totalEcts;
					StudentPosition next;
				} Student;

Varijabla total je suma umnožaka ocjena s pripadajuæim ECTS-om, a totalEcts je suma svih ECTS-ova.

Npr. ukoliko su ulazni podaci za studenta Ivu Matiæa:
(ime)   (prezime)   (ocjena)    (ECTS)
---------------------------------------------------------
---------------------------------------------------------
Ivo	Matiæa          4         7
Ivo     Matiæa          5         2
...
Tada èvor vezane liste treba sadržavati podatke:
{
	firstName: Ivo
	lastName: Matiæ
	totalEcts: 38
	totalEcts: 9
	next: ...
}

Za ocjenu 2:
	* Iz hash tablice upisati sve studente u datoteku zajedno s njihovim relevantnim prosjekom,
	* Pobrisati svu dinamièki rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 3:
	* Iz hash tablice upisati u datoteku samo one studente (zajedno s njihovim relevantnim prosjekom)
	  koji ispunjavaju dva uvjeta za stipendiju:
		* Relativni prosjek veæi ili jednak 3.5
		* Broj položenih ECTS-ova veæi ili jednak 55
	* Pobrisati svu dinamièki rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 5:
	* Studente iz koji zadovoljavaju uvjete za stipendiju u datoteku upisati od najveæeg prema
	  najmanjem relativnom prosjeku.*/