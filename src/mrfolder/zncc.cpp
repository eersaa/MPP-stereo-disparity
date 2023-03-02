/*

*/

#include <stdio.h>

int imWidth = 0;
int imHeight = 0;
int winSize = 9;
int maxDisp = 0;
int znccVal = 0;
int currentMaxSum = 0;
int bestDispVal = 0;

int windowSum = 0;
int windowMean = 0;

int image[1000][1000];

int main(int argc, char const *argv[])
{
    //zncc algorithm
    for (int j = 0; j < imHeight; j++) {
        for (int i = 0; i < imWidth; i++) {
            for (int d = 0; d < maxDisp; d++) {
                for (int y = 0; y < winSize; y++) {
                    for (int x = 0; x < winSize; x++) {
                        //Calculate the mean value for each window
                        windowSum = windowSum + image[j+4-y][i+4-x];
                    }   
                }
                windowMean = windowSum / (imWidth * imHeight);

                for (int j = 0; j < winSize; j++) {
                    for (int j = 0; j < imWidth; j++) {
                        //calculate the zncc value for each window
                    }
                }
                if (znccVal > currentMaxSum) {
                    currentMaxSum = znccVal;
                    bestDispVal = znccVal;
                }
            }
            int disparity_image_pixel = bestDispVal;
        }
    }



}