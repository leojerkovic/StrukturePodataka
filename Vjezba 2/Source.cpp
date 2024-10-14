#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.H>

struct osoba{
	char ime[15];
	char prezime[15];
	int godrod;
	struct osoba* next;
};

struct osoba* unos(char *,char *, int);
int PrependList(struct osoba**, char*, char*, int);

int main() {
	struct osoba* head = NULL;

	return 0;
}

struct osoba* unos(char *ime,char *prezime,int godrod) {
	struct osoba* N = NULL;
	N = (struct osoba*)malloc(sizeof(osoba));
	if (N == NULL) {
		printf("Error allocating memory");
		return NULL;
	}
	strcpy(N->ime, ime);
	strcpy(N->ime, prezime);
	N->godrod = godrod;
	return N;
}

int PrependList(struct osoba** head, char* ime, char* prezime, int godrod) {
	struct osoba* N = NULL;
	N = unos(ime, prezime, godrod);
	if (N==NULL) {
		printf("Error allocating memory");
		return NULL;
	}

}