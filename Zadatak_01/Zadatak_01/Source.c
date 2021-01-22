/*
Zadatak_01:
1. ispitni rok 13. 2. 2020


Napisati program koji iz datoteke (ime se unosi u programu) Čita podatke u binarno stablo za pretaživanje u kojeme se sortiraju po prezimenu, 
pa zatim po imenu osobe. Binarno stablo za pretaživanje je definirano strukturom:

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPosition left;
	PersonPosition right;
} Person;

Pri tome Word word je član strukture Person koja predstavlja glavu vezane liste, te je definirana kao:

struct _word;
typedef struct _word *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Word;

Podaci u datoteci su organizirani na način da prve dvije riječi u retku predstavljaju ime i prezime, dok ostatak rijči u retku predstavljaju rečenicu te osobe.
Rečenicu je potrebno za svaku osobu upisati u vezanu listu Word i to:
•vezana lista se formira u proizvoljnom rasporedu - za ocjenu 2;
•lista se formira tako da rečenica ima smisla - za ocjenu S.
Program ispisuje osobe i njihove rečenice in order.

Na kraju programa potrebno je osloboditi svu dinamički rezerviranu memoriju.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0

#define MAX_NAME 128
#define BUFFER_LENGTH 1024

struct _word;
typedef struct _word *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Word;

struct _person;
typedef struct _person *PersonPosition;
typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPosition left;
	PersonPosition right;
} Person;

char *GetFileContent(char *fileName);
Word *CreateWord(char *word);
Person *CreatePerson(char *firstName, char *lastName);


int main()
{
	char tmpBuffer[BUFFER_LENGTH] = {'\0'};
	char fileName[BUFFER_LENGTH] = {'\0'};
	char *fileContent = NULL;
	FILE *fp = NULL;
	
	char *tmp = NULL;

	//unos imena datoteke sa konzole
	strcpy(fileName, "Zad_1.txt");
	fileContent = GetFileContent(fileName);

	if (fileContent)
		printf("%s\n", fileContent);

	free(fileContent);
	return SUCCESS;
}

char *GetFileContent(char *fileName)
{
	FILE *fp = NULL;
	char *fileContent = NULL;
	size_t length = 0;
	size_t bytesRead = 0;

	if (fileName == NULL || strlen(fileName) == 0) {
		perror("Invalid function argument");
		return NULL;
	}

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "rb");
	if (!fp) {
		perror("ERROR");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);

	fileContent = (char *)calloc(length + 1, sizeof(char));
	if (!fileContent) {
		perror("ERROR");
		return NULL;
	}

	fseek(fp, 0, SEEK_SET);
	bytesRead = fread(fileContent, 1, length, fp);
	fclose(fp);
	
	if (bytesRead != length) {
		perror("An error occured while reading the file!");
		free(fileContent);
		return NULL;
	}

	return fileContent;
}

Word *CreateWord(char *word)
{
	Word *newWord = NULL;

	if (word == NULL || strlen(word) == 0) {
		perror("Invalid function argument");
		return NULL;
	}

	newWord = (Word *)malloc(sizeof(Word));
	if (newWord == NULL) {
		perror("");
		return NULL;
	}

	strncpy(newWord->word, word, MAX_NAME - 1);
	newWord->next = NULL;

	return newWord;
}

Person *CreatePerson(char *firstName, char *lastName)
{
	Person *newPerson = NULL;

	if ( firstName == NULL || lastName == NULL || strlen(firstName) == 0 || strlen(lastName) == 0 ) {
		printf("Invalid function argument");
		return NULL;
	}

	newPerson = (Person *)malloc(sizeof(Person));
	if (NULL == newPerson) {
		perror("");
		return NULL;
	}
	
	strncpy(newPerson->firstName, firstName, MAX_NAME);
	strncpy(newPerson->lastName, lastName, MAX_NAME);
	strncpy(newPerson->word.word, "HEAD", MAX_NAME);
	newPerson->word.next = NULL;

	return newPerson;
}