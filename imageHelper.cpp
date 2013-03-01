/***************************************************************************//**
 * @file imageHelper.cpp
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "imageHelper.h"

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This helper function simply counts the intensities in the n x n region extending
 * down and to the right from index x_0-y_0.
 *
 * @param[in] image
 * @param[in] x_0       - start x
 * @param[in] y_0       - start y
 * @param[in] n         - dimension of region
 * @param[in,out] intensities    - storage for intensity counts
 *
 * @returns void
 *
 ******************************************************************************/
void intensity_distribution(Image& image, int x_0, int y_0, int n, int intensities[])
{
    for(int row = x_0; row < x_0+n; row++)
        for(int col = y_0; col < y_0+n; col++)
            intensities[inten(image,row,col)]++;
    return;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 *     Allows for dealing with edges for neighborhood operations. Maps image
 *     indexes that are out of range back onto an index in the image. It does
 *     this by wrapping the indexs around to the otherside of the image (using
 *     modulus on the image size.
 *
 * @param[in] image     - the image being indexed into
 * @param[in] row       - row index
 * @param[in] col       - col index
 *
 * @returns int     - intensity of the pixel at the [row][col]
 *
 ******************************************************************************/
int inten(Image &image, int row, int col)
{
    int height = image.Height();
    int width = image.Width();

    //Adjust row and col index back onto the image
    int adjusted_row = (row+height) % height;
    int adjusted_col = (col+width) % width;
    return image[adjusted_row][adjusted_col];
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function takes an n x n filter function and applies it to every
 * pixel in the inputted image. Using function pointers prevents the need to
 * continuously copy for loops on the image.
 *
 * @param[in] image
 * @param[in] n         - dimension of area to filter
 * @param[in] filter    - pointer to filter function
 *
 * @returns void
 *
 ******************************************************************************/
void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&))
{
    int span;   //Stores (n-1)/2, or how far the filter extends from the center
    Image img_copy = image;

    //Force n to an odd number if it is not
    if(n%2 == 0) n--;

    //Calculate span
    span = (n-1)/2;

    //Loop through and apply filter
    for(int row = 0; row < (image.Height()); row++)
        for(int col = 0; col < (image.Width()); col++)
            image[row][col].SetIntensity( filter(row, col, n, img_copy));

    return;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Simply returns the pregenerated kirsch filters
 *
 * @param[in] target[][3][3] - Array to store kirsch
 *
 * @returns void
 *
 ******************************************************************************/
void generate_kirsch_filters(int target[][3][3])
{
    static int filter[8][3][3] = {
                            {
                                {-3, -3, 5},
                                {-3, 0, 5},
                                {-3, -3, 5}
                            },
                            {
                                {-3, 5, 5},
                                {-3, 0, 5},
                                {-3, -3, -3}
                            },
                            {
                                {5, 5, 5},
                                {-3, 0, -3},
                                {-3, -3, -3}
                            },
                            {
                                {5, 5, -3},
                                {5, 0, -3},
                                {-3, -3, -3}
                            },
                            {
                                {5, -3, -3},
                                {5, 0, -3},
                                {5, -3, -3}
                            },
                            {
                                {-3, -3, -3},
                                {5, 0, -3},
                                {5, 5, -3}
                            },
                            {
                                {-3, -3, -3},
                                {-3, 0, -3},
                                {5, 5, 5}
                            },
                            {
                                {-3, -3, -3},
                                {-3, 0, 5},
                                {-3, 5, 5}
                            }
                        };

    //Copy into target array
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                target[i][j][k] = filter[i][j][k];
    return;
}


/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Clamps the value between the left and right values so that
 * left <= value <= right
 *
 * @param[in] filter
 *
 * @returns qreal
 *
 ******************************************************************************/
qreal Clamp(qreal value, qreal left, qreal right)
{
    //Swap left and right if left is greater than right
    if(left > right)
    {
        int temp = left;
        left = right;
        right = temp;
    }

    return value < left ? left : value > right ? right : value;
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Creates a sum based on the filter
 *
 * @param[in] filter
 *
 * @returns int
 *
 ******************************************************************************/
int CreateSum(int filter[3][3])
{
    int sum = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            sum += filter[i][j];
        }
    }

    return sum;
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Applies a generic filter to the image
 *
 * @param[in] image
 * @param[in] filter
 * @param[in] n
 *
 * @returns bool
 *
 ******************************************************************************/
bool ApplyFilter(Image &image, int filter[3][3])
{
    int offset = 1;
    int sum = CreateSum(filter);

    Image copyImage = image;

    if(sum <= 0)
    {
        return false;
    }

    double normalFilter[3][3] = {{0}, {0}, {0}};

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            normalFilter[i][j] = filter[i][j] / (double)sum;
        }
    }

    for(int col = offset; col < image.Height() - offset; col++)
    {
        for(int row = offset; row < image.Width() - offset; row++)
        {
            double newIntensity = 0.0;

            for(int colFilter = 0; colFilter < 3; colFilter++)
            {
                for(int rowFilter = 0; rowFilter < 3; rowFilter++)
                {
                    int imageCol = col - offset + colFilter;
                    int imageRow = row - offset + rowFilter;

                    newIntensity += normalFilter[colFilter][rowFilter] * copyImage[imageCol][imageRow].Intensity();
                }
            }

            int clampedIntensity = Clamp(newIntensity + .5, 0, 255);

            image[col][row].SetIntensity(clampedIntensity);
        }
    }

    return true;
}
