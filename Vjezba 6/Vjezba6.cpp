#include <stdio.h>
#include <stdlib.h>
#define DATUM_VECI -1
#define DATUM_ISTI 0
#define DATUM_MANJI 1

struct artikl;
typedef struct artikl* artiklposition;
typedef struct artikl {
	char ime[15];
	int kolicina;
	double cijena;
	artiklposition next;
}artikl;

struct racun;
typedef struct racun* racunposition;
typedef struct racun {
	char datum[15];
	artikl head;
	racunposition next;
}racun;

int UcitajRacune(racunposition);
int UbaciSortiranoRacun(racunposition, racunposition);
int UsporediDatume(racunposition, racunposition);


int main() {
	printf("Lol");
	return 0;
}

int UcitajRacune(racunposition head) {
	FILE* dat = NULL;
	dat = fopen("racuni.txt", "r");
	if (!dat) {
		printf("Datoteka se nije otvorila...");
		return EXIT_FAILURE;
	}
	racunposition temp = NULL;
	while (feof(dat) != 0) {
		temp = (racunposition)malloc(sizeof(racun));
		fscanf(dat, "%s", temp->datum); fgetc(dat);

	}

}

int UbaciSortiranoRacun(racunposition head, racunposition R) {
	if (head->next == NULL) {
		R->next = head->next;
		head->next = R;
		return EXIT_SUCCESS;
	}
	racunposition temp = head->next;
	while (1) {
		if (UsporediDatume(R, temp) == DATUM_MANJI) {

		}
		temp = temp->next;
	}




}

int UsporediDatume(racunposition R1, racunposition R2) {
	int god1, god2;
	int mj1, mj2;
	int dan1, dan2;
	sscanf(R1->datum, "%d-%d-%d", &god1, &mj1, &dan1);
	sscanf(R2->datum, "%d-%d-%d", &god2, &mj2, &dan2);
	if (god1 > god2) {
		return DATUM_VECI;
	}
	else if (mj1 > mj2) {
		return DATUM_VECI;
	}
	else if (dan1 > dan2) {
		return DATUM_VECI;
	}
	else {};

	if (god1 == god2 && mj1 == mj2 && dan1 == dan2) {
		return DATUM_ISTI;
	}
	else {
		return DATUM_MANJI;
	}

}