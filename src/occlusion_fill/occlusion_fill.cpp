#include "occlusion_fill.h"


int getNearestFillPixelValue(int pixel_index, int pix_x, int pix_y, unsigned char *image, int width, int height)
{
    int fillPixelValue = 0;
    int pixelValue = 0;
    int windowSizeHalf = 10;

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
     
    
    if (fillPixelValue == 0)
    {
        fillPixelValue = 0;
    }
    return fillPixelValue;
}

void fillZeroPixels(unsigned char *image, unsigned char *outImage, int width, int height)
{
    unsigned char* imageCopy = (unsigned char*)malloc(width * height);
    int windowSizeHalf = 1;

    // Loop through the image
    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {

        if (image[y * width + x] > 202) {
            int sum = 0;
            int count = 0;
            /*
            // Loop through the window
            for (int i = -windowSizeHalf; i <= windowSizeHalf; i++) {
                for (int j = -windowSizeHalf; j <= windowSizeHalf; j++) {
                    int x2 = x + j;
                    int y2 = y + i;

                    // Check that the pixel is inside the image
                    if (x2 >= 0 && x2 < (int)width && y2 >= 0 && y2 < (int)height && image[y2 * width + x2] != 0) {
                        if (image[y2 * width + x2] != 0) {
                            sum += image[y2 * width + x2];
                            count++;
                        }
                    }
                }
            }

            // Set the pixel value
            imageCopy[y * width + x] = sum / count;*/
            imageCopy[y * width + x] = 0;

            }
        else {
            imageCopy[y * width + x] = image[y * width + x];
        }
        }
    }

    // Copy the image back
    image = imageCopy;


    int pixel_index = 0;
    for (int runs = 0; runs < 10; runs++) {
        pixel_index = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (image[pixel_index] == 0)
                {
                    outImage[pixel_index] = getNearestFillPixelValue(pixel_index, x, y, image, width, height);
                }
                else
                {
                    outImage[pixel_index] = image[pixel_index];
                }
                pixel_index++;
            }
        }
        image = outImage;
    }
    free(imageCopy);
}

void occFillOptimizedC(unsigned char *image, unsigned char *outImage, int width, int height)
{

    //side search
    /*
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
        


    }*/

    //8-way search
    int dir = 0;
    int x2 = 0;
    int y2 = 0;
    bool found = false;

    for (int runs = 0; runs < 20; runs++) {

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                if (image[y * width + x] == 0)
                {
                    found = false;
                    // Loop through 8 directions to find the nearest non-zero pixel
                    for (int maxDist = 0; maxDist < 7; maxDist++) {
                        if (found) {
                            break;
                        }

                        for (dir = 0; dir < 8; dir++) {
                            switch (dir) {
                            case 0: x2 = x + maxDist; y2 = y; break;
                            case 1: x2 = x - maxDist; y2 = y; break;
                            case 2: x2 = x + maxDist; y2 = y + (maxDist / 2); break;
                            case 3: x2 = x + maxDist; y2 = y - (maxDist / 2); break;
                            case 4: x2 = x - maxDist; y2 = y + (maxDist / 2); break;
                            case 5: x2 = x - maxDist; y2 = y - (maxDist / 2); break;
                            case 6: x2 = x; y2 = y + maxDist; break;
                            case 7: x2 = x; y2 = y - maxDist; break;
                            }
                            // Check that the pixel is inside the image
                            if (x2 >= 0 && x2 < (int)width && y2 >= 0 && y2 < (int)height) {
                                if (image[y2 * width + x2] != 0) {
                                    outImage[y * width + x] = image[y2 * width + x2];
                                    found = true;
                                }
                            }

                            if (found) {
                                break;
                            }
                        }
                    }
                }
                else
                {
                    outImage[y * width + x] = image[y * width + x];
                }

            }
        }
        image = outImage;
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
