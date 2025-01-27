#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stablo;
typedef struct stablo* pstablo;
typedef struct stablo {
	char naziv_grada[30];
	int broj_stanovnika;
	pstablo L;
	pstablo R;
}Stablo;

struct lista;
typedef struct lista* plista;
typedef struct lista {
	char naziv_drzave[30];
	pstablo gradoviBroj;
	pstablo gradoviNaziv;
	plista next;
}Lista;

int printaj(plista);
void printajstablo(pstablo);
int SortiraniUnosListe(plista);
pstablo UcitavanjeStablaBroj(pstablo, int, const char*);
int StabloZaCvorBroj(plista, const char*, FILE*);
pstablo UcitavanjeStablaNaziv(pstablo, int, const char*);
int StabloZaCvorNaziv(plista, const char*, FILE*);
int UcitavanjeDatoteka(plista);

int main() {
	Lista head;
	head.next = NULL;
	UcitavanjeDatoteka(&head);
	printaj(&head);
	return 0;
}

int printaj(plista head) {
	plista temp=head->next;
	if (temp == NULL) {
		printf("Lista je prazna...\n");
		return EXIT_FAILURE;
	}
	while (temp != NULL) {
		printf("%s ", temp->naziv_drzave);
		temp = temp->next;
	}
	printf("\n\n");
	temp = head->next;
	while (temp != NULL) {
		printf("%s sortiran po stanovnicima:\n",temp->naziv_drzave);
		printajstablo(temp->gradoviBroj);
		printf("\n");
		printf("%s sortiran po nazivu:\n", temp->naziv_drzave);
		printajstablo(temp->gradoviNaziv);
		printf("\n");
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

void printajstablo(pstablo cvor) {
	if (cvor != NULL) {
		printajstablo(cvor->L);
		printf("%s %d\n", cvor->naziv_grada, cvor->broj_stanovnika);
		printajstablo(cvor->R);
	}

}

int SortiraniUnosListe(plista head,const char* naziv_drzave) {
	plista novi = NULL;
	novi = (plista)malloc(sizeof(Lista));
	if (novi == NULL) {
		printf("Greska u alokaciji memorije...\n");
		return EXIT_FAILURE;
	}
	strcpy(novi->naziv_drzave, naziv_drzave);
	novi->gradoviBroj = NULL;
	novi->gradoviNaziv = NULL;
	novi->next = NULL;
	if (head->next == NULL) {
		head->next = novi;
		return EXIT_SUCCESS;
	}
	while (head->next != NULL) {
		if (strcmp(head->next->naziv_drzave, naziv_drzave) > 0) {
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

pstablo UcitavanjeStablaBroj(pstablo cvor, int br, const char* naziv) {
	if (cvor == NULL) {
		cvor = (pstablo)malloc(sizeof(Stablo));
		if (cvor == NULL) {
			printf("Greska u alokaciji memorije...\n");
			return NULL;
		}
		cvor->broj_stanovnika = br;
		strcpy(cvor->naziv_grada,naziv);
		cvor->L = NULL;
		cvor->R = NULL;
		return cvor;
	}
	if (br < cvor->broj_stanovnika) {
		cvor->L=UcitavanjeStablaBroj(cvor->L, br, naziv);
	}
	else {
		cvor->R=UcitavanjeStablaBroj(cvor->R, br, naziv);
	}
	return cvor;
}

int StabloZaCvorBroj(plista head, const char* naziv, FILE* dat) {
	plista temp;
	temp = head->next;
	while (strcmp(temp->naziv_drzave, naziv) != 0) {
		temp = temp->next;
	}
	int vrati;
	char nazivgrad[30];
	int br;
	while (true) {
		vrati=fscanf(dat, "%s %d\n", nazivgrad, &br);
		if (vrati != 2) {
			break;
		}
		temp->gradoviBroj = UcitavanjeStablaBroj(temp->gradoviBroj, br, nazivgrad);
	}
	return EXIT_SUCCESS;
}

pstablo UcitavanjeStablaNaziv(pstablo cvor, int br, const char* naziv) {
	if (cvor == NULL) {
		cvor = (pstablo)malloc(sizeof(Stablo));
		if (cvor == NULL) {
			printf("Greska u alokaciji memorije...\n");
			return NULL;
		}
		cvor->broj_stanovnika = br;
		strcpy(cvor->naziv_grada, naziv);
		cvor->L = NULL;
		cvor->R = NULL;
		return cvor;
	}
	if (strcmp(naziv,cvor->naziv_grada)<0) {
		cvor->L = UcitavanjeStablaNaziv(cvor->L, br, naziv);
	}
	else {
		cvor->R = UcitavanjeStablaNaziv(cvor->R, br, naziv);
	}
	return cvor;
}
int StabloZaCvorNaziv(plista head, const char* naziv, FILE* dat) {
	plista temp;
	temp = head->next;
	while (strcmp(temp->naziv_drzave, naziv) != 0) {
		temp = temp->next;
	}
	int vrati;
	char nazivgrad[30];
	int br;
	while (true) {
		vrati=fscanf(dat, "%s %d\n", nazivgrad, &br);
		if (vrati != 2) {
			break;
		}
		temp->gradoviNaziv = UcitavanjeStablaNaziv(temp->gradoviNaziv, br, nazivgrad);
	}
	return EXIT_SUCCESS;
}

int UcitavanjeDatoteka(plista head) {
	FILE* dat1 = NULL;
	FILE* dat2 = NULL;
	dat1 = fopen("drzave.txt", "r");
	if (dat1 == NULL) {
		printf("Datoteka se nije otvorila...\n");
		return EXIT_FAILURE;
	}
	int vrati;
	char naziv[30];
	char dat[30];
	
	while (true) {

		vrati = fscanf(dat1, "%s %s\n", naziv, dat);
		if (vrati != 2) {
			break;
		}
		SortiraniUnosListe(head, naziv);

		dat2 = fopen(dat, "r");
		if (dat2 == NULL) {
			printf("Datoteka se nije otvorila...\n");
			return EXIT_FAILURE;
		}
		StabloZaCvorBroj(head, naziv, dat2);
		rewind(dat2);
		StabloZaCvorNaziv(head, naziv, dat2);
		fclose(dat2);

	}

	fclose(dat1);
	return EXIT_SUCCESS;
}