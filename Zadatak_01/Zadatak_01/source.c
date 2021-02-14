/*
Zadatak_01:
1. ispitni rok 13. 2. 2020

Napisati program koji iz datoteke (ime se unosi u programu) Èita podatke u binarno stablo za pretaživanje u kojeme se sortiraju po prezimenu, 
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

Pri tome Word word je èlan strukture Person koja predstavlja glavu vezane liste, te je definirana kao:

struct _word;
typedef struct _word *WordPosition;
typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
} Word;

Podaci u datoteci su organizirani na naèin da prve dvije rijeèi u retku predstavljaju ime i prezime, dok ostatak rijèi u retku predstavljaju reèenicu te osobe.
Reèenicu je potrebno za svaku osobu upisati u vezanu listu Word i to:
•vezana lista se formira u proizvoljnom rasporedu- za ocjenu 2;
•lista se formira tako da reèenica ima smisla - za ocjenu S.
Program ispisuje osobe i njihove reèenice in order.
Na kraju programa potrebno je osloboditi svu dinamièki rezerviranu memoriju.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_STRING 1024
#define ERR (-1)
#define OKAY 0
#define LOOP 1

struct _word;
typedef struct _word *WordPosition;

 typedef struct _word {
	char word[MAX_NAME];
	WordPosition next;
}Word;

struct _person;
typedef struct _person *PersonPosition;

typedef struct _person {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	Word word;
	PersonPosition left;
	PersonPosition right;
}Person;

PersonPosition GetFromFile(char* FileName);
PersonPosition MakeNewRoot(char* firstName, char* lastName, char* buffer);
PersonPosition AddPerson(PersonPosition r, char* firstName, char* lastName, char* buffer); 
PersonPosition DeleteTree(PersonPosition r);
int AddWord(WordPosition h, char* word);
int DeleteWordList(WordPosition h);
void PrintInOrder(PersonPosition r);
void PrintWordList(WordPosition h);

int main()
{
	int succ = 0;
	char fileName[MAX_NAME] = "Zad_1.txt";
	PersonPosition root = NULL;

	root = GetFromFile(fileName);
	if(NULL == root){
		puts("Stablo nije unešeno!");
		return ERR;
	}

	PrintInOrder(root);
	root = DeleteTree(root);
	
	return succ;

}

PersonPosition GetFromFile(char* fileName)
{
	FILE* fp;

	int retVal = 0; 
	int n = 0;
	
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];

	char* buffer;

	PersonPosition r = NULL;

	buffer = (char*)malloc(sizeof(MAX_STRING + 1));
	if(NULL == buffer){
		puts("Neuspješna alokacija!(buffer)");
		return NULL;
	}

	if(strstr(fileName, ".txt") == 0)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if(NULL == fp){
		perror("Datoteka!");
		return NULL;
	}

	while(!feof(fp)){
		
		memset(buffer, '\0', MAX_STRING);
		memset(firstName, '\0', sizeof(buffer));
		memset(lastName, '\0', MAX_NAME);

		fgets(buffer, sizeof(buffer), fp);
		retVal = sscanf(buffer, "%s%s%n", firstName, lastName, &n);
		buffer += n;

		r = AddPerson(r, firstName, lastName, buffer);
	}

	fclose(fp);
	free(buffer);

	return r;
}
PersonPosition MakeNewRoot(char* firstName, char* lastName, char* buffer)
{
	int n = 0;
	int succ = 0;
	int retVal;

	PersonPosition p;
	Word q;

	char word[MAX_NAME];

	p = (PersonPosition)malloc(sizeof(Person));
	p->left = NULL;
	p->right = NULL;

	q.next = NULL;
	p->word = q;

	strcpy(p->firstName, firstName);
	strcpy(p->lastName, lastName);

	while(LOOP){
		
		memset(word, '\0', MAX_NAME);

		retVal = sscanf(buffer, "%s %n", word, &n);
		if(retVal == 0)
			break;

		succ = AddWord(&p->word, word);

		buffer += n;
	}

	return p;
}
PersonPosition AddPerson(PersonPosition r, char* firstName, char* lastName, char* buffer)
{
	if(r == NULL){

		r = MakeNewRoot(firstName, lastName, buffer);
	}
	else if(r->lastName[0] > lastName[0]) {

		AddPerson(r->left, firstName, lastName, buffer);
	}
	else if(r->lastName[0] < lastName[0]) {

		AddPerson(r->right, firstName, lastName, buffer);
	}
	else /*if(r->lastName[0] == lastName[0])*/{
	
		if(r->firstName[0] > firstName[0]) {

			AddPerson(r->left, firstName, lastName, buffer);
		}
		else if(r->firstName[0] < firstName[0]) {

			AddPerson(r->right, firstName, lastName, buffer);
		}
		else {

			AddPerson(r->right, firstName, lastName, buffer);
		}
	}
	return r;
}
PersonPosition DeleteTree(PersonPosition r)
{
	if(r != NULL){
		DeleteTree(r->left);
		DeleteTree(r->right);
		DeleteWordList(&r->word);
		free(r);
	}

	return NULL;
}
int AddWord(WordPosition h, char* word)
{
	WordPosition q = NULL;

	q->next = h->next;
	strcpy(q->word, word);

	h->next = q;

	return OKAY;
}
int DeleteWordList(WordPosition h)
{
	WordPosition temp;

	while(h->next != NULL){
		temp = h->next;
		h->next = temp->next;
		free(temp);
	}

	return OKAY;
}
void PrintInOrder(PersonPosition r)
{
	if(NULL == r)
		return;
	PrintInOrder(r->left);
	printf("%s %s, ", r->firstName, r->lastName);
	PrintWordList(&r->word);
	printf("\n");
	PrintInOrder(r->right);

}
void PrintWordList(WordPosition h)
{

	h = h->next;

	while(h != NULL){
		printf("%s ", h->word);

		h = h->next;
	}

	return;
}
