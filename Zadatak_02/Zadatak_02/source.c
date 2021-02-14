/*Zadatak_02
2. ispitni rok 27.2.2020.


Zadana je datoteka sa popisom studenata, njihovim ocjenama i pripadaju�im  ECTS-ovima.
Svaki redak datoteke sadr�i ime, prezime, ocjenu
Napisati program koji u�itava podatke u hash tablicu du�ine 23 i pri tome:
	* Svaki element hash tablice ozna�ava glavu vezane liste.
	* Ulazni podaci iz datoteke se raspr�uju na na�in da se zbroje ASCII vrijednosti prva tri slova
	  imena i prezimena.
	* Svaka vezana lista je sortirana po prezimenu, zatim po imenu studenata
	* Ukoliko se pojavi student s ve� postoje�im imenom i prezimenom ne unosi se ponovo
	* �vor vezane liste je definiran sljede�im poljima:

				struct _student;
				typedef struct _student *StudentPosition;
				typedef struct _student{
					char firstName[MAX_NAME];
					char lastName[MAX_NAME];
					int total;
					int totalEcts;
					StudentPosition next;
				} Student;

Varijabla total je suma umno�aka ocjena s pripadaju�im ECTS-om, a totalEcts je suma svih ECTS-ova.

Npr. ukoliko su ulazni podaci za studenta Ivu Mati�a:
(ime)   (prezime)   (ocjena)    (ECTS)
---------------------------------------------------------
---------------------------------------------------------
Ivo	Mati�a          4         7
Ivo     Mati�a          5         2
...
Tada �vor vezane liste treba sadr�avati podatke:
{
	firstName: Ivo
	lastName: Mati�
	totalEcts: 38
	totalEcts: 9
	next: ...
}

Za ocjenu 2:
	* Iz hash tablice upisati sve studente u datoteku zajedno s njihovim relevantnim prosjekom,
	* Pobrisati svu dinami�ki rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 3:
	* Iz hash tablice upisati u datoteku samo one studente (zajedno s njihovim relevantnim prosjekom)
	  koji ispunjavaju dva uvjeta za stipendiju:
		* Relativni prosjek ve�i ili jednak 3.5
		* Broj polo�enih ECTS-ova ve�i ili jednak 55
	* Pobrisati svu dinami�ki rezerviranu memoriju i zatvoriti datoteke
Za ocjenu 5:
	* Studente iz koji zadovoljavaju uvjete za stipendiju u datoteku upisati od najve�eg prema
	  najmanjem relativnom prosjeku.*/