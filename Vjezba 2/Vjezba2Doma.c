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

struct osoba* Create(char*, char*, int);
struct osoba* ReturnFirst(struct osoba**, char*, char*, int);
int ListOut(struct osoba*);
struct osoba* ReturnLast(struct osoba*);
int AddLast(struct osoba*, char*, char*, int);
struct osoba* ReturnSurname(struct osoba*, char*);
int DeletePerson(struct osoba**, char*);



int main() {
	//testiranje funkcija s primjerima

	struct osoba* head = NULL;
	char ime1[15] = { "Joe" }, prezime1[15] = { "Anderson" }; int godrod1 = 1950;
	char ime2[15] = { "Alan" }, prezime2[15] = { "Wake" }; int godrod2 = 1977;
	char ime3[15] = { "Dexter" }, prezime3[15] = { "Morgan" }; int godrod3 = 1970;
	char ime4[15] = { "Kazuma" }, prezime4[15] = { "Kiryu" }; int godrod4 = 1968;
	struct osoba* prva = ReturnFirst(&head, ime1, prezime1, godrod1);
	struct osoba* druga = ReturnFirst(&head, ime2, prezime2, godrod2);
	struct osoba* cetvrta = ReturnFirst(&head, ime4, prezime4, godrod4);
	if (ListOut(head)) {
		printf("ERROR LISTING");
	}
	if (AddLast(head, ime3, prezime3, godrod3)) {
		printf("ERROR ADDING LAST");
	}
	else {
		printf("\nAdded person to the end of list: %s %s, born: %d.\n", ime3, prezime3,godrod3);
	}
	if (ListOut(head)) {
		printf("ERROR LISTING");
	}
	struct osoba* temp = NULL;
	temp = ReturnSurname(head, prezime2);
	printf("\nReturned with surname '%s': %s %s, born: %d.\n", prezime2, temp->ime, temp->prezime,temp->godrod);
	if (DeletePerson(&head, prezime1)) {
		printf("ERROR DELETING PERSON");
	}
	else {
		printf("\nDeleted from list: %s %s, born: %d.\n", ime1, prezime1, godrod1);
	}
	if (ListOut(head)) {
		printf("ERROR LISTING");
	}

	return 0;
}



struct osoba* Create(char* ime, char* prezime, int godrod) {
	struct osoba* Novi = NULL;
	Novi = (struct osoba*)malloc(sizeof(struct osoba));
	if (Novi == NULL) {
		printf("Error allocating memory");
		return NULL;
	}
	strcpy(Novi->ime, ime);
	strcpy(Novi->prezime, prezime);
	Novi->godrod = godrod;
	return Novi;
}

struct osoba* ReturnFirst(struct osoba** head, char* ime, char* prezime, int godrod) {
	struct osoba* Novi = NULL;
	Novi = Create(ime, prezime, godrod);
	if (Novi == NULL) {
		printf("Error allocating memory");
		return NULL;
	}
	Novi->next = (*head);
	(*head) = Novi;
	return Novi;
	
}

int ListOut(struct osoba* head) {
	struct osoba* temp=head;
	if (temp == NULL) {
		printf("No elements to print\n");
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
	struct osoba* temp = head;
	if (temp == NULL) {
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
		printf("Error allocating memory");
		return EXIT_FAILURE;
	}
	last->next=NULL;
	if (beforelast == NULL) {
		beforelast = last;
	}
	else {
		beforelast->next = last;
	}
	return EXIT_SUCCESS;
}

struct osoba* ReturnSurname(struct osoba* head, char* prezime) {
	struct osoba* temp = head;
	if (temp == NULL) {
		printf("No elements to return");
		return NULL;
	}
	while (1) {
		if (!strcmp(temp->prezime, prezime)) {
			return temp;
		}
		else if (temp->next == NULL) {
			printf("Person not found");
			return NULL;
		}
		temp = temp->next;
	}
	
}

int DeletePerson(struct osoba** head, char* prezime) {
	struct osoba* temp=(*head);
	if (temp == NULL) {
		printf("No elements to delete");
		return EXIT_FAILURE;
	}
	struct osoba* toDelete = NULL;
	toDelete = ReturnSurname((*head), prezime);
	if (toDelete == (*head)) {
		free(toDelete);
		(*head) = NULL;
	}
	while (1) {
		if (temp->next == toDelete) {
			temp->next = toDelete->next;
			free(toDelete);
			return EXIT_SUCCESS;
		}
		temp = temp->next;
		if (temp->next == NULL) {
			printf("Person with surname not found");
			return EXIT_FAILURE;
		}
	}

}
