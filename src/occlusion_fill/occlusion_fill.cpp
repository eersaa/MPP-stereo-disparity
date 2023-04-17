#include "occlusion_fill.h"


int getNearestFillPixelValue(int pixel_index, unsigned char *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;

    int minDist = width + height;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int dist = euclideanDistanceBetweenTwoPixels(pixel_index, x, y, width);
            pixelValue = getPixelValueFromImage(x, y, image, width);

            if (!pixelIsZero(pixelValue)
                && pixelDistanceIsLessThanLastMinimum(dist, minDist))
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

void fillZeroPixels(unsigned char *image, unsigned char *outImage, int width, int height)
{

    for (int pixel_index = 0; pixel_index < width * height; pixel_index++)
    {
        *(outImage + pixel_index) = getNearestFillPixelValue(pixel_index, image, width, height);
    }

    for (int pixel_index = 0; pixel_index < width * height; pixel_index++)
    {
        *(image + pixel_index) = *(outImage + pixel_index);
    }

}

void occFillOptimizedC(unsigned char *image, unsigned char *outImage, int width, int height)
{
    bool flip = false;
    bool found = false;
    int seeker = 0;

    for (int pixel_index = 0; pixel_index < width * height; pixel_index++)
    {
        if (image[pixel_index] == 0)
        {
            found = false;
            for (int ind = 0; ind < 65; ind++)
            {
                if (flip)
                {
                    seeker = -ind;
                    flip = false;
                } 
                else
                {
                    seeker = ind;
                    flip = true;
                }

                if (image[pixel_index + seeker] != 0)
                {
                    outImage[pixel_index] = image[pixel_index + seeker];
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                outImage[pixel_index] = 1;
            }
        }
        else
        {
            outImage[pixel_index] = image[pixel_index];
        }
    }
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
