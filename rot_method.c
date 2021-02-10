#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void rot_method(int n, double *A) {
	double cos, sin, s, buf;
	int i, j, k;
	
	for (i = 0; i < n-1; i++) {
		
		if (A[(i+1)*n+i] == 0) {  // Защита от деления на 0
			for (j = i + 2; j < n; j++) {
				if (A[j*n+i] != 0) {
					// cos = 0; sin = -1
					for (k = i; k < n; k++) {        // Умножение на T слева (по столбцам)
						buf = A[(i+1)*n+k];
						A[(i+1)*n+k] = A[j*n+k];
						A[j*n+k] = - buf;
					}
					
					for (k = i; k < n; k++) {        // Умножение на T^t справа (по строкам)
						buf = A[k*n+(i+1)];          // Буфер используется, т.к. измененное 
						A[k*n+(i+1)] = A[k*n+j];     // значение требуется использовать дальше
						A[k*n+j] = - buf;
					}
					break;
				}
				if (j == n - 1) {
					printf("Error: the matrix is degenerate\n");
					return ;
				}
			}
		}
		
		for (j = i + 2; j < n; j++){
			
			cos =   A[(i+1)*n+i] / sqrt(A[(i+1)*n+i] * A[(i+1)*n+i] + A[j*n+i] * A[j*n+i]);
			sin = - A[j*n+i] / sqrt(A[(i+1)*n+i] * A[(i+1)*n+i] + A[j*n+i] * A[j*n+i]);
					
			for (k = i; k < n; k++) {        // Умножение на T слева (по столбцам)
				buf = A[(i+1)*n+k];
				A[(i+1)*n+k] = buf * cos - A[j*n+k] * sin;
				A[j*n+k] = buf * sin + A[j*n+k] * cos;
			}
			
			for (k = i; k < n; k++) {        // Умножение на T^t справа (по строкам)
				buf = A[k*n+(i+1)];
				A[k*n+(i+1)] = buf * cos - A[k*n+j] * sin;
				A[k*n+j] = buf * sin + A[k*n+j] * cos;
			}
		}
	}
}