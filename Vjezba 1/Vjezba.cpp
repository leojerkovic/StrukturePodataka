#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1024

int NumOfRows(const char* filename) {
	FILE* dat = NULL;
	dat = fopen(filename, "r");
	int NumOfRows = 0;
	int n;
	char Buffer[MAX];
	if (!fp) return -1;
	while (1) {
		fgets(Buffer, n, dat);
		NumOfRows++;
		if (feof(dat) != 0) break;

	}

}


int main() {
	printf("Hello World!");
	return 0;
}