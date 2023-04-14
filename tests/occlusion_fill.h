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

int distance(int pixel_index, int index)
{
    return abs(pixel_index - index);
}

double euclideanDistanceBetweenTwoPixels(int pixel1_index, int pixel2_x_index, int pixel2_y_index)
{
    return sqrt(pow(distance(pixel1_index, pixel2_x_index), 2) + pow(distance(pixel1_index, pixel2_y_index), 2));
}

int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;

    double minDist = width + height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double dist = euclideanDistanceBetweenTwoPixels(pixel_index, x, y);
            pixelValue = *(image + x + y * width);

            if (pixelValue != 0
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
