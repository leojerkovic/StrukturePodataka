#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stablo;
typedef struct stablo* pstablo;
typedef struct stablo {
	int El;
	pstablo R;
	pstablo L;
}Stablo;

struct red;
typedef struct red* pred;
typedef struct red {
	pstablo root;
	pred next;
}Red;

int randbroj(int, int);
pstablo Unos(pstablo,int);
void Inorder(pstablo);
void Preorder(pstablo);
void Postorder(pstablo);
void Levelorder(pstablo);
int push(pred, pstablo);
pstablo pop(pred);
pstablo PronadiMin(pstablo);
pstablo PronadiMax(pstablo);
pstablo Brisi(pstablo, int);
pstablo Pronadi(pstablo, int);

int main() {
	srand(time(NULL));
	pstablo root = NULL;
	int test[15];
	for (int i = 0; i < 15; i++) {
		test[i] = randbroj(1, 100);
		root = Unos(root, test[i]);
	}
	printf("Random niz unosa u stablo:\n");
	for (int i = 0; i < 15; i++) {
		printf("%d ", test[i]);	
	}
	printf("\n");
	printf("\n");
	printf("Preorder:\n");
	Preorder(root); printf("\n");
	printf("Inorder:\n");
	Inorder(root); printf("\n");
	printf("Postorder:\n");
	Postorder(root); printf("\n");
	printf("Levelorder:\n");
	Levelorder(root); printf("\n");
	printf("\n");
	root = Brisi(root, test[3]);
	root = Brisi(root, test[6]);
	root = Brisi(root, test[9]);
	printf("Nakon brisanja elemenata %d, %d i %d:\n", test[3], test[6], test[9]);
	printf("\n");
	printf("Preorder:\n");
	Preorder(root); printf("\n");
	printf("Inorder:\n");
	Inorder(root); printf("\n");
	printf("Postorder:\n");
	Postorder(root); printf("\n");
	printf("Levelorder:\n");
	Levelorder(root); printf("\n");
	printf("\n");
	printf("Pronadi %d u stablu: %d\n", test[10],Pronadi(root,test[10])->El);
	return 0;
}

int randbroj(int prvi, int drugi) {
	return prvi + rand() % (drugi - prvi + 1);
}

pstablo Unos(pstablo cvor,int El) {
	if (cvor == NULL) {
		cvor = (pstablo)malloc(sizeof(Stablo));
		if (cvor == NULL) {
			printf("Greska u alokaciji memorije...\n");
			return NULL;
		}
		cvor->El = El;
		cvor->L = NULL;
		cvor->R = NULL;
		return cvor;
	}
	if (El < cvor->El) {
		cvor->L = Unos(cvor->L, El);
	}
	else {
		cvor->R = Unos(cvor->R, El);
	}
	return cvor;
}

void Inorder(pstablo cvor) {
	if (cvor != NULL) {
		Inorder(cvor->L);
		printf("%d ", cvor->El);
		Inorder(cvor->R);
	}
}

void Preorder(pstablo cvor) {
	if (cvor != NULL) {
		printf("%d ", cvor->El);
		Preorder(cvor->L);		
		Preorder(cvor->R);
	}
}

void Postorder(pstablo cvor) {
	if (cvor != NULL) {
		Postorder(cvor->L);		
		Postorder(cvor->R);
		printf("%d ", cvor->El);
	}
}

void Levelorder(pstablo cvor) {
	pstablo print;
	red head;
	head.next = NULL;
	push(&head, cvor);
	while (true) {
		print = pop(&head);
		if (print == NULL) {
			break;
		}
		if (print->L != NULL) {
			push(&head, print->L);
		}
		if (print->R != NULL) {
			push(&head, print->R);
		}
		printf("%d ", print->El);
	}
}

int push(pred head, pstablo cvor) {
	if (cvor == NULL) {
		return EXIT_FAILURE;
	}
	pred novi = NULL;
	novi = (pred)malloc(sizeof(Red));
	if (novi == NULL) {
		printf("Greska u alokaciji memorije...\n");
		return EXIT_FAILURE;
	}
	novi->root = cvor;
	
	novi->next = head->next;
	head->next = novi;
}

pstablo pop(pred head) {
	pstablo ret;
	pred del;
	if (head->next == NULL) {
		return NULL;
	}
	while (head->next->next != NULL) {
		head = head->next;
	}
	del = head->next;
	head->next = del->next;
	ret = del->root;
	free(del);
	return ret;
}

pstablo PronadiMin(pstablo cvor) {
	if (cvor == NULL) {
		return NULL;
	}
	if (cvor->L == NULL) {
		return cvor;
	}
	return PronadiMax(cvor->L);
}

pstablo PronadiMax(pstablo cvor) {
	if (cvor != NULL) {
		while (cvor->R != NULL) {
			cvor = cvor->R;
		}
	}
	return cvor;
}

pstablo Brisi(pstablo cvor, int El) {
	if (cvor == NULL) {
		return NULL;
	}
	if (cvor->El == El) {

		//temp je najveci element u lijevom podstablu sta se brise
		pstablo temp = PronadiMax(cvor->L);
				
		if (temp == NULL) { //ako ga nema
			pstablo del = cvor;
			cvor = cvor->R;
			free(del);
			return cvor;
		}
		
		if (cvor->L == temp) { //ako je odma lijevo od elementa sta se brise
			pstablo del = cvor;
			cvor = cvor->L;
			cvor->R = del->R;
			free(del);
			return cvor;
		}

		//pronadi ga dublje i obrisi s funkcijom
		cvor->El = temp->El;
		cvor->L=Brisi(cvor->L, temp->El);
		return cvor;

	}
	if (El < cvor->El) {
		cvor->L = Brisi(cvor->L, El);
	}
	else {
		cvor->R = Brisi(cvor->R, El);
	}
	return cvor;
}

pstablo Pronadi(pstablo cvor, int El) {
	if (cvor == NULL) {
		return NULL;
	}
	if (cvor->El == El) {
		return cvor;
	}
	if (El < cvor->El) {
		return Pronadi(cvor->L, El);
	}
	else {
		return Pronadi(cvor->R, El);
	}
}