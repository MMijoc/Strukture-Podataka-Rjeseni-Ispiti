/*Zadatak_10
2 ispitni rok 27.2.2014.


Napisati program koji iz datoteke èita dio teksta, rijeè po rijeèi unosi u binarno stablo pretraživanja (maksimalna duljina rijeèi 1024 znaka).
Ispisati binarno stablo na „inorder" naèin.

Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve rijeèi koje poèinju samoglasnikom, a u drugoj sve rijeèi koje poèinju suglasnikom.
Rijeèi zapisane u datotekama moraju biti sortirane po abecedi.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OKAY 0 
#define LOOP 1
#define ERR -1

#define MAX_RIJEC 1024
#define MAX_NAME 50

struct _stablo;
typedef struct _stablo* Pozicija;

typedef struct _stablo { 
	char word[MAX_RIJEC];
	Pozicija L;
	Pozicija D;
}Stablo;

Pozicija DodajEl(char* word, Pozicija s);
Pozicija StvoriCvor(char* word);
void IspisInOrder(Pozicija s);
Pozicija UvozDat(char* fileName);
Pozicija UnosString(char* buffer, Pozicija s);
Pozicija BrisiSve(Pozicija s);

int main() 
{
	int succ = 0;
	char fileName[MAX_NAME] = "Zad_10.txt";
	Pozicija root = NULL;
	
	root = UvozDat(fileName);
	IspisInOrder(root);

	BrisiSve(root);

	return OKAY;
}

Pozicija DodajEl(char* word, Pozicija s) 
{
	if (NULL == s) {
		s = StvoriCvor(word);
	}
	else if(strcmp(s->word, word) > 0){
		s->L = DodajEl(word, s->L);
	}
	else if(strcmp(s->word, word) < 0){
		s->D = DodajEl(word, s->D);
	}
	return s;
}

Pozicija StvoriCvor(char* word)
{
	Pozicija s = NULL;

	s = (Pozicija)malloc(sizeof(Stablo));

	strcpy(s->word, word);
	s->L = NULL;
	s->D = NULL;

	return s;
}

void IspisInOrder(Pozicija s)
{
	if (s != NULL) {
		IspisInOrder(s->L);
		printf("%s \n", s->word);
		IspisInOrder(s->D);
	}
	return;
}

Pozicija UvozDat(char* fileName)
{
	Pozicija s = NULL;
	FILE* fp = NULL;

	char buffer[MAX_RIJEC];

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror("Nece alokacija.");
		return NULL;
	}

	while (!feof(fp)) {
		memset(buffer, '\0', MAX_RIJEC);
		fgets(buffer, MAX_RIJEC, fp);
		if (buffer[0] == '\n')
			continue;
		s = UnosString(buffer, s);
	}

	fclose(fp);
	return s;
}

Pozicija UnosString(char* buffer, Pozicija s) {

	int n = 0;
	int retVal = 0;
	char word[MAX_NAME];

	while (LOOP) {

		memset(word, '\0', MAX_NAME);
		retVal = sscanf(buffer, " %s %n", word, &n);
		

		if (retVal != 1) {
			break;
		}

		s = DodajEl(word, s);

		buffer += n;
	}
	return s;
}

Pozicija BrisiSve(Pozicija s) {
	if (s != NULL) {
		BrisiSve(s->L);
		BrisiSve(s->D);
		free(s);
	}
	return NULL;
}