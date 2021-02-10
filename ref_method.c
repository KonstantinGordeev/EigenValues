#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 2.20e-16 // машинный эпсилон

void ref_method(int n, double *A) {
	double a, normx, sk, s;
	int i, j, k, m;
	double *X1, *X2;
	
	X1 = (double*)malloc((n-1)*sizeof(double));
	X2 = (double*)malloc((n-1)*sizeof(double));
	
	for (i=0; i<n-1;i++){  //Разложение Q_n Q_{n-1} ... Q_1 R
		
		a=sqrt(A[i*n+i]*A[i*n+i] + A[(i+1)*n+i]*A[(i+1)*n+i]); //вычисление ||a||
		if (a < EPS) {
			printf("Error! The matrix is degenerate\n");
			exit(1);
		}
		
		X1[i] = A[i*n+i] - a;  // Вектор отражения
		X2[i] = A[(i+1)*n+i];
		normx = sqrt(X1[i]*X1[i] + X2[i]*X2[i]);
		
		if (normx > EPS) { // Проверка на нетривиальность отражения
			X1[i] /= normx;
			X2[i] /= normx;
			
			A[i*n+i]=a;
            A[(i+1)*n+i]=0;
			
			for (j = i+1; j < n; j++) {  // Умножение на матрицу отражения слева
				sk = X1[i] * A[i*n+j] + X2[i] * A[(i+1)*n+j];
				A[i*n+j] -= 2 * X1[i] * sk;
				A[(i+1)*n+j] -= 2 * X2[i] * sk;
			}
		}
	}

	for (i = 0; i < n-1; i++) {   // Перемножение R Q_1^t ... Q_{n-1}^t Q_n^t
		if ((X1[i]!=0) || (X2[i]!=0)) {
			for (j = 0; j < n; j++) {  // Умножение на матрицу отражения справа
				sk = X1[i] * A[j*n+i] + X2[i] * A[j*n+i+1];
				A[j*n+i] -= 2*X1[i]*sk;
				A[j*n+i+1] -= 2*X2[i]*sk;
			}
		}
	}
}