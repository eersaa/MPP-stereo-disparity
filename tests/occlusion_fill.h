
int occlusionFill(int pixel_index, int *image, int width, int height)
{
    int fillPixelValue = 0;
    int leftRange = 0 - pixel_index;
    int rightRange = width - pixel_index;

    for (int i = leftRange; i < rightRange; i++)
    {
        for (int j = 0; j < height; j++)
        {
            fillPixelValue = *(image + pixel_index + i + j * width);
        }
        if (fillPixelValue != 0)
        {
            break;
        }
    }

    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}
