#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/resource.h>

double get_full_time(); // время работы (системное)
void output(int n, int l, int m, double *A);
double norm_1(int n, double *A, double *x);
double norm_2(int n, double *A, double *x);
int min(int x, int y);
void matr_file(int n, char *filename, double *A);
void matr_input(int k, int n, double *A);
void rot_method(int n, double *A);
void ref_method(int n, double *A);

int main(int argc, char *argv[]) {
	
	double norm_A[2], *A, *x, e;
	int i, j, n, m, k, p;
	double start, end;	// таймеры

	start = get_full_time();
	
	if ( (argc < 5) || (argc > 6) )	 {
		printf("Error! Incorrect number of parameters.\n");
		return -1;
	}
	
	n = atoi(argv[1]);	// размерность
	m = atoi(argv[2]);	// число выводимых значений в матрице
	e = atof(argv[3]);	// точность нахождения собственных значений
	k = atoi(argv[4]);	// номер формулы инициализации
	
	if ( ( (k == 0) && (argc != 6) ) || ( (k != 0) && (argc != 5) ) ) {
		printf("Error! Incorrect number of formula.\n");
		return -1;
	}
	
	A = (double*)malloc(n*n*sizeof(double));  // выделение памяти под матрицу
	if (A == NULL) return -1;
	
	x = (double*)malloc(n*sizeof(double));	// выделение памяти под вектор собственных значений
	if (x == NULL) return -1;
	
	if (k != 0) {   // Ввод матрицы
		matr_input(k, n, A);
	}
	else {
		matr_file(n, argv[5], A);
	}
	
	printf("The matrix A : \n");
	output(n, n, m, A);
	
	rot_method(n, A); // Приведение к почти верхнетреугольному виду
	
	printf("The matrix A after rotation: \n");
	output(n, n, m, A);

	p = 1;	   // Флаг диагональности матрицы
	i = 0;	   // Счетчик циклов
	while (p != 0){
		ref_method(n, A);  // QR разложение и перемножение RQ
		i += 1;
		p = 0;
		for (j = 0; j < n-1; j++) { // Проверка на диагональность матрицы
		   if (fabs(A[n*(j+1)+j]) > e) {
				p = 1;
				break;
		   }
		}
	}

	printf("The matrix A after %d reflections: \n", i);
	output(n, n, m, A);

	for (j=0;j<n;j++){
		x[j]=A[j*n+j];
	}
	
	printf("The eigen values : \n");
	output(n, 1, m, x);
	
	if (k != 0) {	   // Повторная инициализация матрицы для подсчета норм
		matr_input(k, n, A);
	}
	else {
		matr_file(n, argv[5], A);
	}
	
	printf("The norm of the first discrepancy equals %10.3e \n", norm_1(n, A, x));
	printf("The norm of the second discrepancy equals %10.3e \n", norm_2(n, A, x));
	
	end = get_full_time();
	printf("Program execution time :  %lf s\n", (end - start) );
	
	free(A);
	free(x);
	return 0;
}

void output(int n, int l, int m, double *A) {

	int i, counter_i = 0;
	int newl = min(l, m);
	int newc = min(n, m);
	
	for (i = 0; i < newl*newc; i++){
		printf(" %10.3e", A[i + (n - newc) * counter_i]);
		if ( (i+1) % newc == 0 ) {
			counter_i += 1;
			printf("\n");
		}
	}
}

int min(int x, int y){
	if (x >= y) return y;
	else return x;
}

double norm_1(int n, double *A, double *x) {
	int i;
	double tr = 0, sx = 0, norm;
	
	for (i = 0; i < n; i++) {
		tr += A[i*n+i];
		sx += x[i];
	}
	
	norm = fabs(tr - sx);
	return norm;
}

double norm_2(int n, double *A, double *x) {
	int i, j;
	double sA = 0, sx2 = 0, norm;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			sA += fabs(A[i*n+j]);
		}
		sx2 += x[i]*x[i];
	}
	
	norm = fabs(sA - sx2);
	return norm;
}

// Из учебника Богачева
double get_full_time() {
	struct timeval tm;
	
	gettimeofday(&tm, 0);
	
	return tm.tv_sec + (tm.tv_usec)/1000000.;
}