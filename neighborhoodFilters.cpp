/***************************************************************************//**
 * @file neighborhoodFilters.cpp
 ******************************************************************************/

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "prog2.h"
#include <qmath.h>
#include "imageHelper.h"

/******************************************************************************
 * Prototypes
 ******************************************************************************/
int mean_filter(int x, int y, int n, Image& image);
int range_filter(int x, int y, int n, Image& image);
int std_filter(int x, int y, int n, Image& image);
int min_filter(int x, int y, int n, Image& image);
int max_filter(int x, int y, int n, Image& image);

/*******************************************************************************
 *
 *      Filter Functions
 *
 ******************************************************************************/

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the maximum intensity in the n by n region centered
 * at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int max_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int max_i = 256; //1 above max pixel intensity

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Find first nonzero intensity in both directions (max and min)
    while(intensities[--max_i] == 0);

    return max_i;
}


/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the minimum intensity in the n by n region centered
 * at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int min_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int min_i = -1; //1 below min pixel intensity

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Find first nonzero intensity in both directions (max and min)
    while(intensities[++min_i] == 0);

    return min_i;
}


/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the median intensity in the n by n region centered
 * at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int median_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int middle_index = (n*n)/2;
    int total;
    int intensity;

    //Get the intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Pin point index of the median intensity
    intensity = 0;
    total = intensities[intensity++];
    while(total < middle_index)
        total += intensities[intensity++];

    return intensity-1;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the mean intensity in the n by n region centered
 * at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int mean_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int total = 0;

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Calculate the sum
    for(int i = 0; i < 256; i++)
        total += i*intensities[i];

    return total/(n*n); //Return mean
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the range of intensities for the n by n region centered
 * at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int range_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int max_i = 256; //1 above max pixel intensity
    int min_i = -1; //1 below min pixel intensity

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Find first nonzero intensity in both directions (max and min)
    while(intensities[++min_i] == 0);
    while(intensities[--max_i] == 0);

    return max_i - min_i;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function returns the standard deviation of intensities for the n by n
 * region centered at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int std_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int total = 0;
    int mean;
    int std;

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Calculate the mean
    for(int i = 0; i < 256; i++)
        total += i*intensities[i];
    mean = total/(n*n);


    //Calculate the standard deviation
    total = 0;
    for(int i = 0; i < 256; i++)
        total += intensities[i] * (i - mean) * (i - mean);
    std = total / (n*n);
    std = qSqrt(std);

    return std;
}

/*******************************************************************************
 *
 *      Menu Functions
 *
 ******************************************************************************/

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies max_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_Maximum(Image &image)
{
    int n = 0;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, max_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies min_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_Minimum(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, min_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies median_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_Median(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, median_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies mean_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_Mean(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, mean_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies range_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_Range(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, range_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Prompts user for N and applies std_filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_NeighborhoodFilters_StandardDeviation(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, std_filter);
    return true;
}
