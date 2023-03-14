#include <stdio.h>
#include <stdlib.h>
void Add_Matrix (float ** matrixA, float ** matrixB, float ** matrixR, int matSize) {
    int i = 0;
    int j = 0;
    float sum = 0;

    //calculate result matrix
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            matrixR[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    //print result
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            sum = matrixR[i][j];
            printf("result [%d][%d]: %.1f\n", i, j, sum);
        }
        printf("Line Change:\n\n");
    }
}

int main( int argc, char* argv[] )
{
    // Length of vectors
    int matSize = 100;

    
    float **matrixA;
    float **matrixB;
    float **matrixR;

    // Allocate memory for each vector on host
    matrixA = (float**)malloc(matSize * sizeof(float*));
    matrixB = (float**)malloc(matSize * sizeof(float*));
    matrixR = (float**)malloc(matSize * sizeof(float*));
    

    int i = 0;
    int j = 0;
    float sum = 0;

    /*
    float* matrixA[matSize][matSize];
    float* matrixB[matSize][matSize];
    float* matrixR[matSize][matSize];
    //float*** matrixR = malloc(matSize * sizeof(float**));
    */

    for (i = 0; i < matSize; i++) {
        matrixA[i] = (float *)malloc(matSize * sizeof(float*));
    }   

    for (i = 0; i < matSize; i++){
        matrixB[i] = (float *)malloc(matSize * sizeof(float*));
    }


    for (i = 0; i < matSize; i++){
        matrixR[i] = (float *)malloc(matSize * sizeof(float*));
    }
    

    //fill matrices
    for (i=0; i<matSize; i++) {
        for (j=0; j<matSize; j++) {
            matrixA[i][j] = i + 1;
            matrixB[i][j] = j + 2;
        }
    }

    Add_Matrix(matrixA, matrixB, matrixR, matSize);

    free(matrixA);
    free(matrixB);
    free(matrixR);
}