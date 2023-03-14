#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    // Length of vectors
    unsigned int n = 10000;
    int matSize = 100;

    // Host input vectors
    double *matrixA;
    double *matrixB;
    // Host output vector
    double *matrixR;

    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(double);

    // Allocate memory for each vector on host
    matrixA = (double*)malloc(bytes);
    matrixB = (double*)malloc(bytes);
    matrixR = (double*)malloc(bytes);

    // Initialize vectors on host
    int i;
    for( i = 0; i < n; i++ )
    {
        matrixA[i] = i + 1;
        matrixB[i] = i + 2;
    }

    int i = 0;
    int j = 0;

    //fill matrices
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            matrixA[i][j] = i + 1;
            matrixB[i][j] = j + 2;
        }
    }

    //calculate result
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            matrixR[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    //print result
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            sum = matrixR[i][j];
            printf("result %d: %.1f\n", i, sum);
        }
    }
}