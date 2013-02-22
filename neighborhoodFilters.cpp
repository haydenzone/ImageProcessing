#include "prog2.h"

//Prototypes
void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&));

void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&))
{
    int span;   //Stores (n-1)/2, or how far the filter extends from the center
    Image img_copy = image;

    //Force n to an odd number if it is not
    if(n%2 == 1) n--;

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
    int max = 0;
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);

    //Loop through and find the max
    for(int row = x_0; row < x_0+n-1; row++)
        for(int col = y_0; col < y_0+n-1; col++)
            if( image[row][col] > max)
                max = image[row][col];

    return max;
}
int min_filter(int x, int y, int n, Image& image)
{
    int max = 266;
    //Calculate upper left corner of n x n square
    int x_0 = x - ((n-1)/2);
    int y_0 = y - ((n-1)/2);

    //Loop through and find the max
    for(int row = x_0; row < x_0+n-1; row++)
        for(int col = y_0; col < y_0+n-1; col++)
            if( image[row][col] < max)
                max = image[row][col];

    return max;
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
    int n = 0;
    if ( !Dialog( "Choose N dimension" ).Add( n, "N" ).Show() )
        return false;

    applyNbyNfilter(image, n, min_filter);
    return true;
}
