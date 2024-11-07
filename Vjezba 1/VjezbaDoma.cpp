#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

typedef struct{
	char ime[20],prezime[20];
	int bodovi;
}student;

int NumOfRows(const char* filename) {
	FILE* dat = NULL;
	dat = fopen(filename, "r");
	int NumOfRows = 0;
	int n;
	char Buffer[MAX];
	if (!dat){ 
		printf("ERROR OPENING FILE");
		return -1;
	}
	while (1) {
		fgets(Buffer, n, dat);
		NumOfRows++;
		if (feof(dat) != 0) break;

	}
	if (fclose(dat)) printf("ERROR CLOSING FILE");
	return NumOfRows;
}

student* Loading(int n,const char* filename){
	FILE *dat;
	dat=fopen(filename,"r");
	if (!dat){ 
		printf("ERROR OPENING FILE");
		return NULL;
	}
	student* niz;
	niz = (student*)malloc(n*sizeof(student));
	int i;
	for(i=0;i<n;i++){
		fscanf(dat,"%s %s %d",niz[i].ime,niz[i].prezime,&niz[i].bodovi); fgetc(dat);
	}
	if (fclose(dat)) printf("ERROR CLOSING FILE");
	return niz;
}

int main(){
	student *niz;
	niz=Loading(NumOfRows("studentidoma.txt"),"studentidoma.txt");
	int i,n=NumOfRows("studentidoma.txt");
	int MaxBodovi=30;
	for(i=0;i<n;i++){
		printf("%s %s %d %f\n",niz[i].ime,niz[i].prezime,niz[i].bodovi,(float)niz[i].bodovi/MaxBodovi*100);
	}
	return 0;
}
