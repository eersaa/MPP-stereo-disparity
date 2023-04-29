__kernel void average(__global char* in, __global char* out, int windowSize, int height, int width)
{
	int ind = get_global_id(0);

    int windowSizeHalf = windowSize / 2;
    int x = ind % width;
    int y = ind / width;
    int sum = 0;
    int count = 0;

    // Loop through the window to get the average value
        for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
          for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = x + j;
            int y2 = y + i;

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width && y2 >= 0 && y2 < (int)height) {
              sum += in[y2 * width + x2];

              count++;
            }
          }
        }

        if (count == 0) {
          count = 1;
        }

        float avg = sum / count;

        out[ind] = avg;


	
}