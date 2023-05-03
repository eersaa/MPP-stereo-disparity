__kernel void cross_check(__global char* image1, __global char* image2, int threshold, __global char* outImage)
{
  int col = get_global_id(0);
  int row = get_global_id(1);
  int width = get_global_size(0);
  int height = get_global_size(1);
  int pixel_index = (row*width + col);

  //outImage[pixel_index] = crossCheck(image1[pixel_index], image2[pixel_index], threshold);

  // test code without functions
    unsigned char returnValue = 0;
    if (!(abs(image1[pixel_index] - image2[pixel_index]) > threshold))
    {
        returnValue = image1[pixel_index];
    }

    outImage[pixel_index] = returnValue;
}
/*
__kernel void occlusion_fill(__global char* image, __global char* outImage, int windowSize)
{
  int col = get_global_id(0);
  int row = get_global_id(1);
  int width = get_global_size(0);
  int height = get_global_size(1);
  int pixel_index = (row*width + col);

  if (image[pixel_index] == 0)
  {
    outImage[pixel_index] = getNearestFillPixelValue(pixel_index, row, col, image, width, height);
  }

  else
  {
    outImage[pixel_index] = image[pixel_index];
  }
}

//cross check functions
bool differenceIsOverThreshold(unsigned char pixel1, unsigned char pixel2, int threshold)
{
    return abs(pixel1 - pixel2) > threshold;
}

unsigned char crossCheck(unsigned char pixel1, unsigned char pixel2, int threshold)
{
    unsigned char returnValue = 0;
    if (!differenceIsOverThreshold(pixel1, pixel2, threshold))
    {
        returnValue = pixel1;
    }

    return returnValue;
}

//occlusion fill functions
int getNearestFillPixelValue(int pixel_index, int pix_x, int pix_y, unsigned char *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;
    int windowSizeHalf = 30;

    int minDist = width + height;

    // Loop through the window to get the average value
    for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
        for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
            int x2 = pix_x + j;
            int y2 = pix_y + i;

            // Check that the pixel is inside the image
            if (x2 >= 0 && x2 < (int)width &&  y2 >= 0 && y2 < (int)height) {
                int dist = euclideanDistanceBetweenTwoPixels(pixel_index, x2, y2, width);
                pixelValue = getPixelValueFromImage(x2, y2, image, width);

                if (!pixelIsZero(pixelValue)
                    && pixelDistanceIsLessThanLastMinimum(dist, minDist))
                {
                    minDist = dist;
                    fillPixelValue = pixelValue;
                }
                
            }
        }
    }
     
    return fillPixelValue;
}

int pixelRow(int pixel_index, int width)
{
    return pixel_index / width;
}

int verDistance(int pixel_index, int row_index, int width)
{
    return abs(pixelRow(pixel_index, width) - row_index);
}

int pixelColumn(int pixel_index, int width)
{
    return pixel_index % width;
}

int horDistance(int pixel_index, int column_index, int width)
{
    return abs(pixelColumn(pixel_index, width) - column_index);
}

int euclideanDistanceBetweenTwoPixels(int pixel1_index, int pixel2_x_index, int pixel2_y_index, int image_width)
{
    return sqrt(pow(horDistance(pixel1_index, pixel2_x_index, image_width), 2) + pow(verDistance(pixel1_index, pixel2_y_index, image_width), 2));
}

int getPixelValueFromImage(int pixel_x_index, int pixel_y_index, unsigned char *image, int width)
{
    return *(image + pixel_x_index + pixel_y_index * width);
}

bool pixelIsZero(int pixel_value)
{
    return pixel_value == 0;
}

bool pixelDistanceIsLessThanLastMinimum(int distance, int last_min_distance)
{
    return distance < last_min_distance;
}
*/