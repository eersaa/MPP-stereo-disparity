// Wrapper created based on the example from the lodepng library
#include "calculations_wrapper.h"

using namespace calculations_wrapper;

unsigned calculationsWrapper::calc_zncc()
{
    //zncc algorithm
    for (int j = 0; j < imHeight; j++) {
        for (int i = 0; i < imWidth; i++) {
            for (int d = 0; d < maxDisp; d++) {
                for (int y = 0; y < winSize; y++) {
                    for (int x = 0; x < winSize; x++) {
                        //Calculate the mean value for each window
                        windowSum = windowSum + image[j+4-y][i+4-x];
                        windowSum2 = windowSum2 + image2[j+4-y][i+4-x];
                    }   
                }
                windowMean = windowSum / (imWidth * imHeight);
                windowMean2 = windowSum2 / (imWidth * imHeight);

                //Calculate stdev for each window
                for (int y = 0; y < winSize; y++) {
                    for (int x = 0; x < winSize; x++) {
                        windowstd = windowstd + image[j+4-y][i+4-x];
                        windowstd2 = windowstd2 + image2[j+4-y][i+4-x];
                    }   
                }
                windowstd = (pow(windowstd, 0.5)) / (2 * winSize + 1);
                windowstd2 = (pow(windowstd2, 0.5)) / (2 * winSize + 1);

                for (int y = 0; y < winSize; j++) {
                    for (int x = 0; x < imWidth; j++) {
                        //calculate the zncc value for each window
                    znccVal = znccVal + (image[j+4-y][i+4-x] - windowMean) * (image[j+4-y][i+4-x] - windowMean2);
                    }
                }
                znccVal = znccVal / (/*pow((2 * winSize + 1), 2) */ windowstd * windowstd2);

                if (znccVal > currentMaxSum) {
                    currentMaxSum = znccVal;
                    bestDispVal = znccVal;
                }
            }
            int disparity_image_pixel = bestDispVal;
    
    return 0;
}