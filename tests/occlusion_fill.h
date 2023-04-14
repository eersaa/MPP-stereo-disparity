#include <math.h>

int pixelRow(int pixel_index, int width)
{
    return pixel_index / width;
}

int verDistance(int pixel_index, int row_index, int width)
{
    return abs(pixelRow(pixel_index, width) - row_index);
}

int pixelColumn(int pixel_index, int height)
{
    return pixel_index / height;
}

int horDistance(int pixel_index, int column_index, int height)
{
    return abs(pixelColumn(pixel_index, height) - column_index);
}

int euclideanDistanceBetweenTwoPixels(int pixel1_index, int pixel2_x_index, int pixel2_y_index, int image_width, int image_height)
{
    return sqrt(pow(horDistance(pixel1_index, pixel2_x_index, image_height), 2) + pow(verDistance(pixel1_index, pixel2_y_index, image_width), 2));
}

int getPixelValueFromImage(int pixel_x_index, int pixel_y_index, int *image, int width)
{
    return *(image + pixel_x_index + pixel_y_index * width);
}

bool pixelIsNotZero(int pixel_value)
{
    return pixel_value != 0;
}

int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;

    int minDist = width + height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int dist = euclideanDistanceBetweenTwoPixels(pixel_index, x, y, width, height);
            pixelValue = getPixelValueFromImage(x, y, image, width);

            if (pixelIsNotZero(pixelValue)
                && dist < minDist)
            {
                minDist = dist;
                fillPixelValue = pixelValue;
            }
        }
    }    
    
    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}
