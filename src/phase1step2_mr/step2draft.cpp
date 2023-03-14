#include <stdio.h>
#include <stdlib.h>


matSize = 100;


//defining matrices
int ** matrixA;
matrixA = calloc(matSize, sizeof(int*));

int ** matrixB;
matrixB = calloc(matSize, sizeof(int*));

int ** matrixR;
matrixR = calloc(matSize, sizeof(int*));

//fill matrices
for (i=0, i<matSize, i++) {
    for (j=0, j<matSize, j++) {
        matrixA[i][j] = 1;
        matrixB[i][j] = 2;
    }
}

//calc result
for (i=0, i<matSize, i++) {
    for (j=0, j<matSize, j++) {
        matrixR[i][j] = matrixA[i][j] + matrixB[i][j];
    }
}

printf(matrixR);
