#include "prog2.h"
#include <qmath.h>

//Prototypes
void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&));
void intensity_distribution(Image& image, int x_0, int y_0, int n, int intensities[]);
int mean_filter(int x, int y, int n, Image& image);
int range_filter(int x, int y, int n, Image& image);
int std_filter(int x, int y, int n, Image& image);

void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&))
{
    int span;   //Stores (n-1)/2, or how far the filter extends from the center
    Image img_copy = image;

    //Force n to an odd number if it is not
    if(n%2 == 0) n--;

    //Calculate span
    span = (n-1)/2;

    //Loop through and apply filter (cutting out span on edges)
    for(int row = span; row < (image.Height()-span); row++)
        for(int col = span; col < (image.Width()-span); col++)
            image[row][col].SetIntensity( filter(row, col, n, img_copy));

    return;
}

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
void intensity_distribution(Image& image, int x_0, int y_0, int n, int intensities[])
{
    for(int row = x_0; row < x_0+n; row++)
        for(int col = y_0; col < y_0+n; col++)
            intensities[image[row][col]]++;
    return;
}
int median_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int middle_index = (n*n)/2;
    int total;
    int intensity;

    intensity_distribution(image, x_0, y_0, n, intensities);

    intensity = 0;
    total = intensities[intensity++];
    while(total < middle_index)
        total += intensities[intensity++];

    return intensity-1;
}
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

    return total/(n*n);
}
int range_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int total = 0;
    int max_i = 256; //1 above max pixel intensity
    int min_i = -1; //1 below min pixel intensity

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Find first nonzero intensity in both directions (max and min)
    while(intensities[++min_i] == 0);
    while(intensities[--max_i] == 0);

    return max_i - min_i;
}
int std_filter(int x, int y, int n, Image& image)
{
    int intensities[256] = {0};
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);
    int total = 0;
    int mean;
    int max_i = 256; //1 above max pixel intensity
    int min_i = -1; //1 below min pixel intensity
    int std;

    //Get intensity distribution
    intensity_distribution(image, x_0, y_0, n, intensities);

    //Calculate the mean
    for(int i = 0; i < 256; i++)
        total += i*intensities[i];
    mean = total/(n*n);

    total = 0;
    for(int i = 0; i < 256; i++)
        total += intensities[i] * (i - mean) * (i - mean);

    std = total / (n*n);
    std = qSqrt(std);

    return std;
}

bool MyApp::Menu_NeighborhoodFilters_Maximum(Image &image)
{
    int n = 0;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, max_filter);
    return true;
}
bool MyApp::Menu_NeighborhoodFilters_Minimum(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, min_filter);
    return true;
}
bool MyApp::Menu_NeighborhoodFilters_Median(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, median_filter);
    return true;
}
bool MyApp::Menu_NeighborhoodFilters_Mean(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, mean_filter);
    return true;
}
bool MyApp::Menu_NeighborhoodFilters_Range(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, range_filter);
    return true;
}

bool MyApp::Menu_NeighborhoodFilters_StandardDeviation(Image &image)
{
    int n = 3;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, std_filter);
    return true;
}
