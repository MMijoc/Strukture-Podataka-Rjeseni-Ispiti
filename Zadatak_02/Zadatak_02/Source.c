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
	total: 38
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

#define MAX_NAME 128
#define BUFFER_LENGTH 1024
#define TABLE_SIZE 23
#define CHARS_HASHIN 3

struct _student;
typedef struct _student *StudentPosition;
typedef struct _student{
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int total;
	int totalEcts;
	StudentPosition next;
} Student;

typedef Student HashTable;

HashTable *CreateHashTable(int tableSize);
int InitHashTable(HashTable *table, int tableSize);
int FreeHashTable(HashTable *table, int tableSize);
int Hash(char *key1, char *key2, int tableSize);
int HashTableInsert(HashTable *table, int tableSize, Student *toInsert);
//Student *HashTableLookup(HashTable *table, int tableSize, char *firstName, char *lastName);
Student *CreateNewStudent(char *firstName, char *lastName, int mark, int ects);
int InsertToList(Student *listHead, Student *toInsert);
int FreeList(Student *listHead);
int BuildHashTableFromFile(char *fileName, HashTable *table, int tableSize);
int PrintHashTableToFile(HashTable *table, int tableSize);

int main()
{
	char fileName[BUFFER_LENGTH]= { '\0' };
	HashTable *hTable = NULL;


	hTable = CreateHashTable(TABLE_SIZE);

	strcpy(fileName, "Zad_2");
	//BuildHashTableFromFile(fileName, hTable, TABLE_SIZE);
	//PrintHashTableToFile(hTable, TABLE_SIZE);





	//FreeHashTable(hTable, TABLE_SIZE);
	return SUCCESS;
}

HashTable *CreateHashTable(int tableSize)
{

	return NULL;//uhu hu
}

int InitHashTable(HashTable *table, int tableSize)
{
	return SUCCESS;
}

int FreeHashTable(HashTable *table, int tableSize)
{


	return SUCCESS;
}
int HashTableInsert(HashTable *table, int tableSize, Student *toInsert)
{

	return SUCCESS;
}

Student *CreateNewStudent(char *firstName, char *lastName, int mark, int ects)
{
	Student *newStudent = NULL;

	if (firstName == NULL || lastName == NULL ||strlen(firstName) == 0 ||strlen(lastName) == 0) {
		fprintf(stderr, "\n%s", "Invalid functions paramaters");
		return NULL;
	}


	newStudent = (Student *)malloc(sizeof(Student));
	if (!newStudent)  {
		perror("ERROR");
		return NULL;
	}

	strncpy(newStudent->firstName, firstName, MAX_NAME);
	strncpy(newStudent->lastName, lastName, MAX_NAME);
	newStudent->total = mark * ects;
	newStudent->totalEcts = ects;
	newStudent->next = NULL;

	return newStudent;
}

int Hash(char *key1, char *key2, int tableSize)
{
	int hashValue = 0;
	int i = 0;

	if (key1 == NULL ||key2 == NULL || strlen(key1) == 0 || strlen(key2) == 0) {
		fprintf(stderr, "\n%s", "Invalid functions paramaters");
		return FAILURE;
	}

	for (i = 0; i < CHARS_HASHIN && key1[i] != '\0'; i++) {
		hashValue += key1[i];
	}

	for (i = 0; i < CHARS_HASHIN && key2[i] != '\0'; i++) {
		hashValue += key2[i];
	}

	return hashValue;
}

int InsertToList(Student *listHead, Student *toInsert)
{
	return SUCCESS;
}

int FreeList(Student *listHead)
{
	return SUCCESS;
}

int BuildHashTableFromFile(char *fileName, HashTable *table, int tableSize)
{
	return SUCCESS;
}

int PrintHashTableToFile(HashTable *table, int tableSize)
{

	return SUCCESS;
}