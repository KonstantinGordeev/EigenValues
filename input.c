#include <stdio.h>
#include <stdlib.h>

void matr_file(int n, char *filename, double *A);
double element_value(int k, int n, int i, int j);
void matr_input(int k, int n, double *A);
int max(int x, int y);

void matr_input(int k, int n, double *A) {
	int i;
	
	for (i = 0; i < n*n; i++) {
		A[i] = element_value(k, n, i/n + 1, i%n + 1);  // a_{i j} = A[i*n+j]
	}
}


double element_value(int k, int n, int i, int j) {
	if (k == 1) return ( n - max(i, j) + 1 );
	if (k == 2) {
		if (i == j) return 2;
		else if (i-j == 1 || j-i == 1) return -1;
		else return 0;
	}
	if (k == 3) {
		if (i == j && i != n) return 1;
		else if (i == n) return j;
		else if (j == n) return i;
		else return 0;
	}
	if (k == 4) return ( 1./(i+j-1) );
	if (k != 0) {
		printf("Error! Incorrect formula number.\n");
		return -1;
	}
}


void matr_file(int n, char *filename, double *A){
	FILE *IN;
	int i;
	
	IN = fopen(filename, "r");
	if (IN == NULL) {
		printf("Error! The file cannot be opened.\n");
		exit(1);
	}
	
	for (i=0; i<n*n; i++) {
		if (fscanf(IN, "%lf", &A[i]) != 1) {
			fclose(IN);
			printf("Error! The file doesn't satisfy the requirements.\n");
			exit(1);
		}	
	}
}

int max(int x, int y) {
	if ( x >= y ) return x;
	else return y;
}
		
