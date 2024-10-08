#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1024

int NumOfRows(const char* filename) {
	FILE* dat = NULL;
	dat = fopen(filename, "r");
	int NumOfRows = 0;
	int n;
	char Buffer[MAX];
	if (!dat) return -1;
	while (1) {
		fgets(Buffer, n, dat);
		NumOfRows++;
		if (feof(dat) != 0) break;

	}
	return NumOfRows;

}


int main() {
	printf("Hello World!\n");
	printf("Ima %d redova u datoteci!\n",NumOfRows("studenti.txt"));
	return 0;
}