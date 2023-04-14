__kernel void standardDeviation(__global char* in, __global char* out, __global float* avg, int windowSize, int height, int width)
{
	int ind = get_global_id(0);

    int windowSizeHalf = windowSize / 2;
    int x = ind % width;
    int y = ind / width;
    int sum = 0;
    int count = 0;

    for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += pow((in[y2 * width + x2] - avg[ind]), 2);

              count++;
            }
          }
        }

    float std = pow(sum, 0.5);


	out[ind] = std;
}