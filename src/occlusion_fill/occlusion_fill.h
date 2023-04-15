#ifndef OCCLUSION_FILL_H
#define OCCLUSION_FILL_H

#include <math.h>

int pixelRow(int pixel_index, int width);
int verDistance(int pixel_index, int row_index, int width);
int pixelColumn(int pixel_index, int width);
int horDistance(int pixel_index, int column_index, int width);
int euclideanDistanceBetweenTwoPixels(int pixel1_index, int pixel2_x_index, int pixel2_y_index, int image_width);
int getPixelValueFromImage(int pixel_x_index, int pixel_y_index, int *image, int width);
bool pixelIsZero(int pixel_value);
bool pixelDistanceIsLessThanLastMinimum(int distance, int last_min_distance);

int getNearestFillPixelValue(int pixel_index, int *image, int width, int height);
void fillZeroPixels(int *image, int width, int height);

#endif  // OCCLUSION_FILL_H