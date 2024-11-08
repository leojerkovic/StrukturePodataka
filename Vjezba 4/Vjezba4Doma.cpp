#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct polinom {
	int eksp;
	int koef;
	struct polinom* next;
};

int SortiranUnos(struct polinom*,int,int);
int IspisPolinoma(struct polinom*);
int CitanjeIzDat(struct polinom*, const char*);
int UkupnoBrisanje(struct polinom*);
int SpecificnoBrisanje(struct polinom*, int);
int Pronadi(struct polinom*, int);
struct polinom* ZbrajanjePolinoma(struct polinom*, struct polinom*);
struct polinom* MnozenjePolinoma(struct polinom*, struct polinom*);

int main() {
	struct polinom* head=(struct polinom*)malloc(sizeof(struct polinom));
	if (head != NULL) {
		head->next = NULL;
	}
	else {
		free(head);
	}
	struct polinom* head2 = (struct polinom*)malloc(sizeof(struct polinom));
	if (head2 != NULL) {
		head2->next = NULL;
	}
	else {								//Radi visual studia malloc head-a i uvjeti
		free(head2);
	}
	struct polinom* head3;
	struct polinom* head4;
	CitanjeIzDat(head,"polinomi.txt");  //testiranje unosa iz datoteke i rucno preko funkcije
	SortiranUnos(head2, 2, 3);
	SortiranUnos(head2, 2, -3);
	SortiranUnos(head2, 5, 6);
	SortiranUnos(head2, 7, 5);
	SortiranUnos(head2, 1, 9);
	SortiranUnos(head2, 2, 1);

	head3=ZbrajanjePolinoma(head, head2);	//testiranje funckija
	head4 = MnozenjePolinoma(head, head3);
	//IspisPolinoma(head3);
	IspisPolinoma(head4);

	return 0;
}

int SortiranUnos(struct polinom* head, int eksp, int koef) {
	struct polinom* temp=NULL;
	temp = (struct polinom*)malloc(sizeof(struct polinom));
	if (temp == NULL) {
		printf("Memory allocation failed...");
		return EXIT_FAILURE;
	}
	temp->eksp = eksp;
	temp->koef = koef;
	if (head == NULL) {
		printf("No head to add element to...");
		free(temp);
		return EXIT_FAILURE;
	}
	if (head->next == NULL) {
		temp->next = head->next;
		head->next = temp;
		return EXIT_SUCCESS;
	}
	struct polinom* pretzamj = head;
	struct polinom* zamj = head->next;
	while (1) {
		if (temp->eksp < zamj->eksp) {
			pretzamj = pretzamj->next;
			zamj = zamj->next;
			if (zamj == NULL) {
				temp->next=pretzamj->next;
				pretzamj->next = temp;
				return EXIT_SUCCESS;
			}
		}
		else if (temp->eksp > zamj->eksp) {
			pretzamj->next = temp;
			temp->next = zamj;
			return EXIT_SUCCESS;
		}
		else if (temp->eksp == zamj->eksp) {
			zamj->koef += koef;
			if (zamj->koef == 0) {
				pretzamj->next = zamj->next;
				free(zamj);
				free(temp);
				return EXIT_SUCCESS;
			}
			free(temp);
			return EXIT_SUCCESS;
		}
	}
}

int IspisPolinoma(struct polinom* head) {
	if (head == NULL||head->next == NULL) {
		printf("No elements to print...");
		return EXIT_FAILURE;
	}
	struct polinom* temp=head;
	while (1) {
		temp = temp->next;
		printf("%dx^%d", temp->koef, temp->eksp);
		if (temp->next == NULL) {
			printf("\n");
			return EXIT_SUCCESS;
		}
		else {
			printf(" + ");
		}
	}

}

int CitanjeIzDat(struct polinom* head, const char* name) {
	FILE* dat = NULL;
	dat = fopen(name, "r");
	if (dat == NULL) {
		printf("Error opening file...");
		return EXIT_FAILURE;
	}
	int eksp, koef;
	while (feof(dat) == 0) {
		fscanf(dat, " %d %d", &koef, &eksp);
		SortiranUnos(head, eksp, koef);
	}
	fclose(dat);
	return EXIT_SUCCESS;
}

int UkupnoBrisanje(struct polinom* head) {
	if (head==NULL||head->next == NULL) {
		printf("No elements to return...");
		return EXIT_FAILURE;
	}
	struct polinom* cur=head->next;
	struct polinom* next=cur->next;
	head->next = NULL;
	while (1) {
		free(cur);
		if (next == NULL) {
			return EXIT_SUCCESS;
		}
		cur = next;
		next = next->next;
	}
}

int SpecificnoBrisanje(struct polinom* head, int eksp) {
	if (head==NULL||head->next == NULL) {
		printf("Empty list...");
		return EXIT_FAILURE;
	}
	struct polinom* tempprev = head;
	struct polinom* temp = head->next;
	while (1) {
		if (temp->eksp == eksp) {
			tempprev->next = temp->next;
			free(temp);
			return EXIT_SUCCESS;
		}
		else if (temp->next == NULL && temp->eksp != eksp) {
			printf("Not found...");
			return EXIT_FAILURE;
		}
		tempprev = temp;
		temp = temp->next;
	}
}

int Pronadi(struct polinom* head, int eksp) {
	if (head==NULL||head->next == NULL) {
		printf("Empty list...");
		return EXIT_FAILURE;
	}
	struct polinom* temp = head->next;
	while (1) {
		if (temp->eksp == eksp) {
			return 1;
		}
		else if (temp->next == NULL && temp->eksp != eksp) {
			return 0;
		}
		temp = temp->next;
	}
}


struct polinom* ZbrajanjePolinoma(struct polinom* head1, struct polinom* head2){
	if (head1 == NULL || head2 == NULL || head1->next == NULL || head2->next == NULL) {
		printf("No elements to add...");
		return NULL;
	}
	struct polinom* i = head1;
	struct polinom* j = head2->next;

	int a;
	printf("Zbrajanje - Unesi (1) ako zelis unos u novu listu ili (2) ako zelis u postojece prebrisat: "); scanf("%d", &a);

	if (a == 1) {
		struct polinom* head = NULL;
		head = (struct polinom*)malloc(sizeof(struct polinom));
		if (head == NULL) {
			printf("Memory allocation failed...");
			return NULL;
		}
		head->next = NULL;

		i = head1->next;
		j = head2->next;

		while (i != NULL) {
			SortiranUnos(head, i->eksp, i->koef);
			i = i->next;
		}
		while (j != NULL) {
			SortiranUnos(head, j->eksp, j->koef);
			j = j->next;
		}
		return head;
	}
	else {
		while (j != NULL) {
			SortiranUnos(i, j->eksp, j->koef);
			j = j->next;
		}
		j = head2;
		UkupnoBrisanje(j);
		return i;
	}

	
	/*while (1) {
		if (i->eksp == j->eksp) {
			SortiranUnos(head, i->eksp, i->koef + j->koef);
		}
		else if (i->eksp != j->eksp) {
			if (i->eksp < j->eksp) {
				SortiranUnos(head, i->eksp, i->koef);
			}
		}

	}*/
}

struct polinom* MnozenjePolinoma(struct polinom* head1, struct polinom* head2) {
	if (head1 == NULL || head2 == NULL || head1->next == NULL || head2->next == NULL) {
		printf("No elements to multiply...");
		return NULL;
	}
	struct polinom* temp1 = head1->next;
	struct polinom* temp2 = head2->next;

	int temp_eksp;
	int temp_koef;

	int a;
	printf("Mnozenje - Unesi (1) ako zelis unos u novu listu ili (2) ako zelis u postojece prebrisat: "); scanf("%d", &a);
	
	int i,n=0;
	if (a == 1) {
		struct polinom* head = NULL;
		head = (struct polinom*)malloc(sizeof(struct polinom));
		if (head == NULL) {
			printf("Memory allocation failed...");
			return NULL;
		}
		head->next = NULL;
		while (temp1!=NULL) {
			while (temp2 != NULL) {
				SortiranUnos(head, temp1->eksp + temp2->eksp, temp1->koef * temp2->koef);
				temp2 = temp2->next;
			}
			temp2 = head2->next;
			temp1 = temp1->next;
		}
		return head;
	}
	else {
		while (temp1 != NULL) {
			temp_koef = temp1->koef;
			temp_eksp = temp1->eksp;
			temp1 = head1;
			SpecificnoBrisanje(temp1, temp_eksp);
			while (temp2 != NULL) {
				if (!Pronadi(temp1, temp_eksp + temp2->eksp)) {
					n++;
				}
				SortiranUnos(temp1, temp_eksp + temp2->eksp, temp_koef * temp2->koef);
				temp2 = temp2->next;
			}
			temp2 = head2->next;
			for (i = 0; i < n+1; i++) {
				temp1 = temp1->next;
			}
		}
		temp1 = head1;
		temp2 = head2;
		free(temp2);
		return temp1;
	}
}
