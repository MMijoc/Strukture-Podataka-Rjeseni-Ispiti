/*
Zadatak_24
27.02.2013.  Grupa 2


Napisati program kojim se
a) Iz datoteke čitaju riječi i spremaju u vezanu listu na način da se riječi slažu po abecednom redu obrnutom od abecednog reda. Zatim ispisati tu vezanu listu.
b) Iz generirane liste ispisati samo one riječi koje se nalaze zapisane u drugoj proizvoljnoj datoteci.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define SUCCESS 0
#define FAILURE (-1)
#define TRUE 1
#define FALSE 0
#define BUFFER_LENGTH 1024
#define MAX_WORD_LENGTH 128

#define RETURN_FAILURE(message) do {PrintError(message); return FAILURE;} while(0);
#define RETURN_NULL(message) do {PrintError(message); return NULL;} while(0);

typedef struct _word {
	char word[MAX_WORD_LENGTH];

	struct _word *next;
} Word;

void PrintError(char *message);
char *GetFileContent(char *fileName);
Word *CreateNewWord(char *word);
int SortedInsert(Word *listHead, Word *toInsert);
int BuildListFromString(Word *listHead, char *source);
int PrintList(Word *listHead);
int FreeList(Word *element);
int PrintListAndFileDuplicates(Word *listHead, char *fileName);
char *FindWord(Word *listHead, char *word);

int main()
{
	char fileName[2][BUFFER_LENGTH] = {"Zad_24_1", "Zad_24_2"};
	char *fileContent = NULL;
	Word list = {"", NULL};

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	fileContent = GetFileContent(fileName[0]);
	if (!fileContent) return FAILURE;

	printf("List:\n");
	BuildListFromString(&list, fileContent);
	free(fileContent);
	PrintList(&list);

	printf("\n\nWords found in both files:\n");
	PrintListAndFileDuplicates(&list, fileName[1]);

	FreeList(list.next);
	return SUCCESS;

}

void PrintError(char *message)
{
	if (errno != 0)
		perror(message);
	else
		fprintf(stderr, "\n%s", message);

	return;
}

char *GetFileContent(char *fileName)
{
	FILE *fp = NULL;
	size_t length = 0;
	char *content = NULL;

	if (!fileName || strlen(fileName) <= 0) RETURN_NULL("Invalid arguments");

	if (strchr(fileName, '.') == NULL)
		strcat(fileName, ".txt");

	fp = fopen(fileName, "r");
	if (!fp) RETURN_NULL("Error");


	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	content = (char *)calloc(length + 1, sizeof(char));
	if (!content) RETURN_NULL("Error");

	fread(content, sizeof(char), length, fp);

	fclose(fp);
	return content;
}

Word *CreateNewWord(char *word)
{
	Word *newWord = NULL;

	if (!word || strlen(word) <= 0) RETURN_NULL("CreateNewWord: Invalid function arguments");

	newWord = (Word *)malloc(sizeof(Word));
	if (!newWord) RETURN_NULL("Error");

	strncpy(newWord->word, word, MAX_WORD_LENGTH);
	newWord->next = NULL;

	return newWord;
}

int SortedInsert(Word *listHead, Word *toInsert)
{
	Word *tmp = NULL;

	if (!listHead || !toInsert) RETURN_FAILURE("SortedInsert: Invalid arguments!");

	tmp = listHead;
	while (tmp->next && _strnicmp(tmp->next->word, toInsert->word, MAX_WORD_LENGTH) > 0)
		tmp = tmp->next;

	toInsert->next = tmp->next;
	tmp->next = toInsert;

	return SUCCESS;
}

int BuildListFromString(Word *listHead, char *source)
{
	int argTaken = 1, offset = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};

	if (!source) RETURN_FAILURE("BuildListFromString: Invalid arguments!");

	while (argTaken > 0) {
		argTaken = sscanf(source, " %s%n", buffer, &offset);
		if (argTaken == 1)
			SortedInsert(listHead, CreateNewWord(buffer));

		source += offset;
	}

	return SUCCESS;
}

int PrintList(Word *listHead)
{
	Word *tmp = NULL;

	tmp = listHead->next;
	while (tmp) {
		printf("\t%s\n", tmp->word);
		tmp = tmp->next;
	}

	return SUCCESS;
}

int FreeList(Word *element)
{
	if (element == NULL) return SUCCESS;

	FreeList(element->next);
	free(element);

	return SUCCESS;
}

int PrintListAndFileDuplicates(Word *listHead, char *fileName)
{
	char *fileContent = NULL, *source = NULL;
	int argTaken = 1, offset = 0;
	char buffer[BUFFER_LENGTH] = {'\0'};

	source = fileContent = GetFileContent(fileName);
	if (!fileContent) return FAILURE;

	while (argTaken > 0) {
		argTaken = sscanf(source, " %s%n", buffer, &offset);
		if (argTaken == 1)
			if (FindWord(listHead, buffer))
				printf("\t%s\n", buffer);

		source += offset;
	}

	free(fileContent);
	return SUCCESS;
}

char *FindWord(Word *listHead, char *word)
{
	Word *tmp = NULL;
	if (!listHead || !word || strlen(word) <= 0) RETURN_NULL("FindWord: Invalid arguments!");

	tmp = listHead->next;
	while (tmp) {
		if (_strnicmp(tmp->word, word, MAX_WORD_LENGTH) == 0)
			return tmp->word;
		tmp = tmp->next;
	}

	return NULL;
}
