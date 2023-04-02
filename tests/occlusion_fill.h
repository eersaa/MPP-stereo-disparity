
int occlusionFill(int pixel_index, int *image, int width)
{
    int fillPixelValue = 0;
    int leftRange = 0 - pixel_index;
    int rightRange = width - pixel_index;

    for (int i = leftRange; i < rightRange; i++)
    {
        if (*(image + pixel_index + i) != 0)
        {
            fillPixelValue = *(image + pixel_index + i);
            break;
        }
    }

    if (fillPixelValue == 0)
    {
        fillPixelValue = 1;
    }
    return fillPixelValue;
}
