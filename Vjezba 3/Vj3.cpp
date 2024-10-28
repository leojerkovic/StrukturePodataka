#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct osoba {
	char ime[15];
	char prezime[15];
	int godrod;
	struct osoba* next;
};


//2. Zad:

struct osoba* Create(char*, char*, int);
struct osoba* ReturnFirst(struct osoba*, char*, char*, int);
int ListOut(struct osoba*);
struct osoba* ReturnLast(struct osoba*);
int AddLast(struct osoba*, char*, char*, int);
struct osoba* ReturnSurname(struct osoba*, char*);
int DeletePerson(struct osoba*, char*);

//3. Zad:

struct osoba* AddAfter(struct osoba*, char*, char*, char*, int);
struct osoba* AddBefore(struct osoba*, char*, char*, char*, int);
int WriteIn(struct osoba*);
//int ReadOut(struct osoba*);



int main() {
	//testiranje funkcija s primjerima

	struct osoba head {};
	head.next = NULL;
	char ime1[15] = { "Walter" }, prezime1[15] = { "White" }; int godrod1 = 1958;
	char ime2[15] = { "Alan" }, prezime2[15] = { "Wake" }; int godrod2 = 1977;
	char ime3[15] = { "Dexter" }, prezime3[15] = { "Morgan" }; int godrod3 = 1970;
	char ime4[15] = { "Kazuma" }, prezime4[15] = { "Kiryu" }; int godrod4 = 1968;
	char ime5[15] = { "Isshin" }, prezime5[15] = { "Ashina" }; int godrod5 = 1938;
	char ime6[15] = { "Malenia" }, prezime6[15] = { "Marika" }; int godrod6 = 1900;
	char ime7[15] = { "Miquella" }, prezime7[15] = { "Radagon" }; int godrod7 = 1900;
	struct osoba* prva = ReturnFirst(&head, ime1, prezime1, godrod1); //Tri elementa dodana na prvo mjesto (s pridruzivanjem)
	struct osoba* druga = ReturnFirst(&head, ime2, prezime2, godrod2);
	struct osoba* cetvrta = ReturnFirst(&head, ime4, prezime4, godrod4);

	ListOut(&head); //Ispis elemenata

	if (!AddLast(&head, ime3, prezime3, godrod3)) //Dodavanje elementa na zadnje mjesto (bez pridruzivanja)
		printf("\nAdded person to the end of list: %s %s, born: %d.\n", ime3, prezime3, godrod3);

	ListOut(&head); //Ispis elemenata

	struct osoba* temp = NULL;
	temp = ReturnSurname(&head, prezime2); //Pronalazak po prezimenu i pridruzivanje
	if (temp != NULL)
		printf("\nReturned with surname '%s': %s %s, born: %d.\n", prezime2, temp->ime, temp->prezime, temp->godrod);

	if (!DeletePerson(&head, prezime1)) //Brisanje elementa po prezimenu
		printf("\nDeleted from list: %s %s, born: %d.\n", ime1, prezime1, godrod1);

	ListOut(&head); //Ispis elemenata

	AddAfter(&head, prezime3, ime6, prezime6, godrod6);
	AddBefore(&head, prezime4, ime7, prezime7, godrod7);

	ListOut(&head);

	return 0;
}



struct osoba* Create(char* ime, char* prezime, int godrod) {
	struct osoba* Novi = NULL;
	Novi = (struct osoba*)malloc(sizeof(struct osoba));
	if (Novi == NULL) {
		printf("\nError allocating memory\n");
		return NULL;
	}
	strcpy(Novi->ime, ime);
	strcpy(Novi->prezime, prezime);
	Novi->godrod = godrod;
	return Novi;
}

struct osoba* ReturnFirst(struct osoba* head, char* ime, char* prezime, int godrod) {
	struct osoba* Novi = NULL;
	Novi = Create(ime, prezime, godrod);
	if (Novi == NULL) {
		printf("\nError allocating memory\n");
		return NULL;
	}
	Novi->next = head->next;
	head->next = Novi;
	return Novi;

}

int ListOut(struct osoba* head) {
	struct osoba* temp = head->next;
	if (temp == NULL) {
		printf("\nNo elements to print\n");
		return EXIT_FAILURE;
	}
	printf("\nList:\n");
	while (1) {
		printf("%s %s %d.\n", temp->ime, temp->prezime, temp->godrod);
		if (temp->next == NULL) break;
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

struct osoba* ReturnLast(struct osoba* head) {
	struct osoba* temp = head->next;
	if (temp == NULL) {
		printf("\nHead is the only element\n");
		return temp;
	}
	while (1) {
		if (temp->next == NULL) return temp;
		temp = temp->next;
	}
}

int AddLast(struct osoba* head, char* ime, char* prezime, int godrod) {
	struct osoba* beforelast = ReturnLast(head);
	struct osoba* last = Create(ime, prezime, godrod);
	if (last == NULL) {
		printf("\nError allocating memory\n");
		return EXIT_FAILURE;
	}
	last->next = NULL;
	if (beforelast == NULL) {
		head->next = last;
	}
	else {
		beforelast->next = last;
	}
	return EXIT_SUCCESS;
}

struct osoba* ReturnSurname(struct osoba* head, char* prezime) {
	struct osoba* temp = head->next;
	if (temp == NULL) {
		printf("\nNo elements to return\n");
		return NULL;
	}
	while (1) {
		if (!strcmp(temp->prezime, prezime)) {
			return temp;
		}
		else if (temp->next == NULL) {
			printf("\nPerson not found\n");
			return NULL;
		}
		temp = temp->next;
	}

}

int DeletePerson(struct osoba* head, char* prezime) {
	struct osoba* temp = head->next;
	if (temp == NULL) {
		printf("\nNo elements to delete\n");
		return EXIT_FAILURE;
	}
	struct osoba* toDelete = NULL;
	toDelete = ReturnSurname(head, prezime);
	if (toDelete == NULL) {
		printf("\nError deleting person\n");
		return EXIT_FAILURE;
	}
	if (toDelete == head->next) {
		free(toDelete);
		head->next = NULL;
		return EXIT_SUCCESS;
	}
	while (1) {
		if (temp->next == toDelete) {
			temp->next = toDelete->next;
			free(toDelete);
			return EXIT_SUCCESS;
		}
		temp = temp->next;
		if (temp->next == NULL) {
			printf("\nPerson with surname not found\n");
			return EXIT_FAILURE;
		}
	}

}

struct osoba* AddAfter(struct osoba* head, char* nakon, char* ime, char* prezime, int godrod) {
	struct osoba* novi = Create(ime, prezime, godrod);
	if (novi == NULL) {
		return NULL;
	}
	struct osoba* vrati = ReturnSurname(head, nakon);
	if (vrati == NULL) {
		return NULL;
	}
	struct osoba* temp = vrati->next;
	vrati->next = novi;
	novi->next = temp;
	return novi;
}

struct osoba* AddBefore(struct osoba* head, char* nakon, char* ime, char* prezime, int godrod) {
	struct osoba* novi = Create(ime, prezime, godrod);
	if (novi == NULL) {
		return NULL;
	}
	struct osoba* temp = head;
	while (1) {
		if (!strcmp(temp->next->prezime, nakon)) {
			break;
		}
		temp = temp->next;
	}
	novi->next = temp->next;
	temp->next = novi;
	return novi;
}

int WriteIn(struct osoba* head, const char* ime) {
	FILE* dat;
	dat = fopen(ime, "w");
	struct osoba* temp;
	temp = head->next;
	if (temp == NULL) {
		fprintf(dat, "NO ELEMENTS...");
		return EXIT_FAILURE;
	}
	while (1) {
		fprintf(dat, "%s %s %d\n", temp->ime, temp->prezime, temp->godrod);
		if (temp->next == NULL) {
			break;
		}
		else {
			temp = temp->next;
		}

	}
	return EXIT_SUCCESS;

}
