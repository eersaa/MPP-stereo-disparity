__kernel void znccMax(__global char* img1, __global char* img2,
                     __global char* avg1, __global char* avg2, 
                     __global char* std1, __global char* std2, 
                     __global char* DispMaxOut, int windowSize, int height, int width, int leftToRight, int maxDisp)
{
	int ind = get_global_id(0);

    int windowSizeHalf = windowSize / 2;
    int x = ind % width;
    int y = ind / width;
    int sum = 0;
    int count = 0;
    int x2r = 0;
    int d = 0;
    int minDisp = 0;
    int dispRange = maxDisp - minDisp;
    float zncc = 0;

    for (d = minDisp; d < maxDisp; d++) {
        sum = 0;
        count = 0;

        // Loop through the window to get the ZNCC value
        for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            if (leftToRight == 1) {
              x2r = x2 - d;
            }
            else {
              x2r = x2 + d;
            }

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && x2r >= 0 && x2r < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += (img1[y2 * width + x2] - avg1[ind]) * (img2[y2 * width + x2r] - avg2[ind]);

              count++;
            }
          }
        }
    }

    float znccVal = sum / (std1[ind] * std2[ind]);

    if (znccVal > zncc) {
    zncc = znccVal;
    DispMaxOut[y * width + x] = (255*abs(d))/dispRange;
    }
}