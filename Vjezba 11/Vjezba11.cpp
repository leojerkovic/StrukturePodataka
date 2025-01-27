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

struct hashtab;
typedef struct hashtab* phash;
typedef struct hashtab {
	int vel;
	plista* liste;
}HashT;

int printaj(phash);
void printajstablo(pstablo);
int Hash(const char*,int);
int InitHashTab(phash,int);
int UnosUHashTab(phash,plista);
pstablo UcitavanjeStablaBroj(pstablo, int, const char*);
int StabloZaCvorBroj(phash, const char*, FILE*);
pstablo UcitavanjeStablaNaziv(pstablo, int, const char*);
int StabloZaCvorNaziv(phash, const char*, FILE*);
int UcitavanjeDatoteka(phash);

int main() {
	HashT Tab;
	InitHashTab(&Tab, 11);
	UcitavanjeDatoteka(&Tab);
	printaj(&Tab);
	return 0;
}

int printaj(phash Tab) {
	plista temp;
	for (int i = 0; i < Tab->vel; i++) {
		if (Tab->liste[i] == NULL) {
			continue;
		}
		temp = Tab->liste[i];
		while (temp != NULL) {
			printf("%s ", temp->naziv_drzave);
			temp = temp->next;
		}
	}
	printf("\n\n");
	for (int i = 0; i < Tab->vel; i++) {
		if (Tab->liste[i] == NULL) {
			continue;
		}
		temp = Tab->liste[i];
		while (temp != NULL) {
			printf("%s sortiran po stanovnicima:\n", temp->naziv_drzave);
			printajstablo(temp->gradoviBroj);
			printf("\n");
			printf("%s sortiran po nazivu:\n", temp->naziv_drzave);
			printajstablo(temp->gradoviNaziv);
			printf("\n");
			temp = temp->next;
		}
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

int Hash(const char* naziv, int vel) {
	int vrati=0;
	while (*(naziv) != '\0') {
		vrati += *(naziv++);
	}
	return vrati % vel;
}

int InitHashTab(phash tab,int vel) {
	tab->vel = vel;
	tab->liste = NULL;
	tab->liste = (plista*)malloc(vel * sizeof(plista));
	if (tab->liste == NULL) {
		printf("Greska u alokaciji memorije...\n");
		return EXIT_FAILURE;
	}
	for (int i = 0; i < vel; i++) {
		tab->liste[i] = NULL;
	}
	return EXIT_SUCCESS;
}

int UnosUHashTab(phash Tab,const char* naziv_drzave) {
	plista prvi = Tab->liste[Hash(naziv_drzave, Tab->vel)];
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
	if (prvi == NULL) {
		Tab->liste[Hash(naziv_drzave, Tab->vel)] = novi;
		return EXIT_SUCCESS;
	}
	if (strcmp(prvi->naziv_drzave, naziv_drzave) > 0) {
		novi->next = Tab->liste[Hash(naziv_drzave, Tab->vel)];
		Tab->liste[Hash(naziv_drzave, Tab->vel)] = novi;
		return EXIT_SUCCESS;
	}
	while (prvi->next != NULL) {
		if (strcmp(prvi->next->naziv_drzave, naziv_drzave) > 0) {
			novi->next = prvi->next;
			prvi->next = novi;
			return EXIT_SUCCESS;
		}
		prvi = prvi->next;
	}
	novi->next = prvi->next;
	prvi->next = novi;
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

int StabloZaCvorBroj(phash Tab, const char* naziv, FILE* dat) {
	plista temp;
	temp = Tab->liste[Hash(naziv, Tab->vel)];
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
int StabloZaCvorNaziv(phash Tab, const char* naziv, FILE* dat) {
	plista temp;
	temp = Tab->liste[Hash(naziv, Tab->vel)];
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

int UcitavanjeDatoteka(phash Tab) {
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
		UnosUHashTab(Tab, naziv);

		dat2 = fopen(dat, "r");
		if (dat2 == NULL) {
			printf("Datoteka se nije otvorila...\n");
			return EXIT_FAILURE;
		}
		StabloZaCvorBroj(Tab, naziv, dat2);
		rewind(dat2);
		StabloZaCvorNaziv(Tab, naziv, dat2);
		fclose(dat2);

	}

	fclose(dat1);
	return EXIT_SUCCESS;
}