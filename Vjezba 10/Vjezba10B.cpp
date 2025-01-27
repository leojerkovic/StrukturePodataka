#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista;
typedef struct lista* plista;
typedef struct lista {
	char naziv_grada[30];
	int broj_stanovnika;
	plista next;
}Lista;

struct stablo;
typedef struct stablo* pstablo;
typedef struct stablo {
	char naziv_drzave[30];
	Lista gradoviNaziv;
	Lista gradoviBroj;
	pstablo L;
	pstablo R;
}Stablo;

void printaj(pstablo);
void printajstablonaziv(pstablo);
void printajstabloclanove(pstablo);
int SortiraniUnosListeNaziv(plista,int,const char*);
int SortiraniUnosListeBroj(plista, int, const char*);
pstablo UcitavanjeStablaNaziv(pstablo, const char*);
pstablo PristupListiNaziv(pstablo, int, const char*, const char*);
pstablo PristupListiBroj(pstablo, int, const char*, const char*);
pstablo UcitavanjeDatoteka(pstablo);

int main() {
	pstablo root = NULL;
	root=UcitavanjeDatoteka(root);
	printaj(root);
	return 0;
}

void printaj(pstablo cvor) {
	printajstablonaziv(cvor);
	printf("\n\n");
	printajstabloclanove(cvor);
}

void printajstablonaziv(pstablo cvor) {
	if (cvor != NULL) {
		printajstablonaziv(cvor->L);
		printf("%s ", cvor->naziv_drzave);
		printajstablonaziv(cvor->R);
	}
}

void printajstabloclanove(pstablo cvor) {
	plista temp;
	if (cvor != NULL) {
		printajstabloclanove(cvor->L);
		temp = cvor->gradoviBroj.next;
		printf("%s sortiran po broju stanovnika:\n", cvor->naziv_drzave);
		while (temp != NULL) {
			printf("%s %d\n", temp->naziv_grada, temp->broj_stanovnika);
			temp = temp->next;
		}
		printf("\n");
		temp = cvor->gradoviNaziv.next;
		printf("%s sortiran po nazivu grada:\n", cvor->naziv_drzave);
		while (temp != NULL) {
			printf("%s %d\n", temp->naziv_grada, temp->broj_stanovnika);
			temp = temp->next;
		}
		printf("\n");
		printajstabloclanove(cvor->R);
	}
}

int SortiraniUnosListeNaziv(plista head, int br, const char* naziv) {
	plista novi = NULL;
	novi = (plista)malloc(sizeof(Lista));
	if (novi == NULL) {
		printf("Greska u alokaciji memorije...\n");
		return EXIT_FAILURE;
	}
	strcpy(novi->naziv_grada, naziv);
	novi->broj_stanovnika = br;
	novi->next = NULL;
	if (head->next == NULL) {
		head->next = novi;
		return EXIT_SUCCESS;
	}
	while (head->next != NULL) {
		if (strcmp(head->next->naziv_grada, naziv) > 0) {
			novi->next = head->next;
			head->next = novi;
			return EXIT_SUCCESS;
		}
		head = head->next;
	}
	novi->next = head->next;
	head->next = novi;
	return EXIT_SUCCESS;
}

int SortiraniUnosListeBroj(plista head, int br, const char* naziv) {
	plista novi = NULL;
	novi = (plista)malloc(sizeof(Lista));
	if (novi == NULL) {
		printf("Greska u alokaciji memorije...\n");
		return EXIT_FAILURE;
	}
	strcpy(novi->naziv_grada, naziv);
	novi->broj_stanovnika = br;
	novi->next = NULL;
	if (head->next == NULL) {
		head->next = novi;
		return EXIT_SUCCESS;
	}
	while (head->next != NULL) {
		if (head->next->broj_stanovnika > br) {
			novi->next = head->next;
			head->next = novi;
			return EXIT_SUCCESS;
		}
		head = head->next;
	}
	novi->next = head->next;
	head->next = novi;
	return EXIT_SUCCESS;
}


pstablo UcitavanjeStablaNaziv(pstablo cvor, const char* naziv) {
	if (cvor == NULL) {
		cvor = (pstablo)malloc(sizeof(Stablo));
		if (cvor == NULL) {
			printf("Greska u alokaciji memorije...\n");
			return NULL;
		}
		strcpy(cvor->naziv_drzave, naziv);
		cvor->gradoviBroj.next=NULL;
		cvor->gradoviNaziv.next=NULL;
		cvor->L = NULL;
		cvor->R = NULL;
		return cvor;
	}
	if (strcmp(naziv, cvor->naziv_drzave) < 0) {
		cvor->L = UcitavanjeStablaNaziv(cvor->L, naziv);
	}
	else {
		cvor->R = UcitavanjeStablaNaziv(cvor->R, naziv);
	}
	return cvor;
}

pstablo PristupListiNaziv(pstablo root, int br, const char* naziv_grada, const char* naziv_drzave) {	
	if (root == NULL) {
		return NULL;
	}
	if (strcmp(root->naziv_drzave, naziv_drzave) == 0) {
		SortiraniUnosListeNaziv(&root->gradoviNaziv, br, naziv_grada);
		return root;
	}
	root->L = PristupListiNaziv(root->L, br, naziv_grada, naziv_drzave);
	root->R = PristupListiNaziv(root->R, br, naziv_grada, naziv_drzave);

	return root;
}
pstablo PristupListiBroj(pstablo root, int br, const char* naziv_grada, const char* naziv_drzave) {	
	if (root == NULL) {
		return NULL;
	}
	if (strcmp(root->naziv_drzave, naziv_drzave) == 0) {
		SortiraniUnosListeBroj(&root->gradoviBroj, br, naziv_grada);
		return root;
	}
	root->L = PristupListiBroj(root->L,br,naziv_grada,naziv_drzave);
	root->R = PristupListiBroj(root->R, br, naziv_grada, naziv_drzave);

	return root;
}

pstablo UcitavanjeDatoteka(pstablo root) {
	FILE* dat1 = NULL;
	FILE* dat2 = NULL;
	dat1 = fopen("drzave.txt", "r");
	if (dat1 == NULL) {
		printf("Datoteka se nije otvorila...\n");
		return NULL;
	}
	int vrati;
	int br;
	char naziv[30];
	char naziv2[30];
	char dat[30];

	while (true) {

		vrati = fscanf(dat1, "%s %s\n", naziv, dat);
		if (vrati != 2) {
			break;
		}
		root = UcitavanjeStablaNaziv(root, naziv);

		dat2 = fopen(dat, "r");
		if (dat2 == NULL) {
			printf("Datoteka se nije otvorila...\n");
			return NULL;
		}

		while (true) {
			vrati = fscanf(dat2, "%s %d\n", naziv2, &br);
			if (vrati != 2) {
				break;
			}
			root = PristupListiBroj(root, br, naziv2, naziv);
			root = PristupListiNaziv(root, br, naziv2, naziv);
		}
		fclose(dat2);

	}
	fclose(dat1);
	return root;
}