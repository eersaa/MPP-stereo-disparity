//#include stuffs
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("2d-resize\n");
    double sampleMat[12][12];
    for (int i=0; i<12; i++) {
        for (int j=0; j<12; j++) {
            sampleMat[i][j] = i+j;
        }
    }
    printf("samplemat:\n");
    for (int i=0; i<12; i++) {
        for (int j=0; j<12; j++) {
            printf("%.1f", sampleMat[i][j]);
            printf(" ");
        }
        printf("\n");
    }

    double resultMat[3][3];
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            resultMat[i][j] = sampleMat[i*4][j*4];
        }
    }

    printf("resultmat:\n");
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            printf("%.1f", resultMat[i][j]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");

    printf("1d-resize\n");

    printf("sampleMat-1d\n");
    /*
    double sampleMat1d[12*12];
    int id = 0;
    for (int i=0; i<12; i++) {
        for (int j=0; j<12; j++) {
            sampleMat1d[id] = sampleMat[i][j];
            printf("%.1f ",sampleMat1d[id]);
            id++;
        }
        id++;
        printf("\n");
    }
    printf("\n");
    */
    int height = 8;
    int width = 12;
    int currow = 0;
    int curcol = 0;
    int ind = 0;
    int indmax = 11;

    int brl = 0;
    double sampleMat1d[12*12];
    for (int i=0; i<(12*12); i++) {
        sampleMat1d[i] = ind;
        printf("%.1f ",sampleMat1d[i]);
        
        if(ind>=indmax){
            ind = ind - 10;
            indmax++;
        } else {
            ind++;
        }

        if(brl > 10) {
            printf("\n");
            brl = 0;
        } else {
            brl++;
        }
        
    }
    printf("\n");

    ind = 0;
    printf("resultVector\n");
    double resultMat1d[9];
    for (int i=0; i<9; i++) {
        resultMat1d[i] = sampleMat1d[ind];
        printf("%.1f ",resultMat1d[i]);
        ind = ind + 4;
        if (ind >= (width + (currow * width))) {
            currow = currow + 4;
            ind = (currow * width);
            printf("\n");
        }
    }
    
    printf("\n");
    


    return 0;
}
