#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int deviousGlobalnaVarijabla = 0;

struct stablo;
typedef struct stablo* pstablo;
typedef struct stablo {
	int El;
	pstablo L;
	pstablo R;
}Stablo;

void printajNaZaslon(pstablo);
int printajUDat(pstablo);
void rekPrintDat(pstablo,FILE*);
void levelOrderPrint(pstablo);
pstablo insert(pstablo,int);
pstablo replace(pstablo);
int sumiraj(pstablo);
int randbroj(int,int);

int main() {
	srand(time(NULL));
	pstablo root = NULL;
	for (int i = 0; i < 10; i++) {
		root=insert(root, randbroj(10,90));
	}
	printajNaZaslon(root);
	printajUDat(root);
	printf("\n");
	root = replace(root);
	printajNaZaslon(root);
	printajUDat(root);
	return 0;
}

void printajNaZaslon(pstablo root) {
	if (root != NULL) {
		printajNaZaslon(root->L);
		printf("%d ", root->El);
		printajNaZaslon(root->R);
	}
}

int printajUDat(pstablo root) {
	FILE* dat = NULL;
	if (deviousGlobalnaVarijabla == 0) {
		dat = fopen("sigme.txt", "w");
		if (dat == NULL) {
			return EXIT_FAILURE;
		}
		deviousGlobalnaVarijabla = 1;
	}
	else {
		dat = fopen("sigme.txt", "a");
		if (dat == NULL) {
			return EXIT_FAILURE;
		}
	}
	rekPrintDat(root, dat);
	fprintf(dat, "\n");
	fclose(dat);
	return EXIT_SUCCESS;
}

void rekPrintDat(pstablo root,FILE* dat) {
	if (root != NULL) {
		rekPrintDat(root->L, dat);
		fprintf(dat,"%d ", root->El);
		rekPrintDat(root->R, dat);
	}
}

pstablo insert(pstablo root,int br) {
	if (root == NULL) {
		root = (pstablo)malloc(sizeof(Stablo));
		if (root == NULL) {
			return NULL;
		}
		root->El = br;
		root->L = NULL;
		root->R = NULL;
		return root;
	}
	if (br < root->El) {
		root->R = insert(root->R, br);
	}
	else {
		root->L= insert(root->L, br);
	}
	return root;
}

pstablo replace(pstablo root) {
	if (root == NULL) {
		return NULL;
	}
	int suma = 0;
	if (root->L != NULL) {
		suma += sumiraj(root->L);
	}
	if (root->R != NULL) {
		suma += sumiraj(root->R);
	}
	root->El = suma;

	root->R = replace(root->R);
	root->L = replace(root->L);

	return root;
}

int sumiraj(pstablo root) {
	if (root == NULL) {
		return 0;
	}
	return root->El + sumiraj(root->L) + sumiraj(root->R);
}

int randbroj(int prvi,int drugi) {
	return prvi + rand() % (drugi - prvi + 1);
}