/***************************************************************************//**
 * @file edgeDetection.cpp
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
int laplacian_filter( int x, int y, int n, Image & image );
int kirsch_magnitude_filter( int x, int y, int n, Image & image );
int kirsch_filter( int x, int y, int n, Image & image );

bool MyApp::Menu_Edge_SobolMagnitude(Image &image)
{
    return this->SobolMagnitude(image);
}


bool MyApp::SobolMagnitude(Image &image)
{
    int edge[3] = {1, 2, 1};
    Image copy = image;

    for (int row = 1; row < image.Height() - 1; row++)
    {
        for (int col = 1; col < image.Width() - 1; col++)
        {
            double partial_x = Clamp((copy[row-1][col+1] * edge[0] +
                               copy[row][col+1]    * edge[1] +
                               copy[row+1][col+1]  * edge[2]) -
                               (
                               copy[row-1][col-1] * edge[0] +
                               copy[row][col-1]   * edge[1] +
                               copy[row+1][col-1] * edge[2]
                               ), 0, 255);

            double partial_y = Clamp((copy[row+1][col-1] * edge[0] +
                               copy[row+1][col]    * edge[1] +
                               copy[row+1][col+1] * edge[2]) -
                               (
                               copy[row-1][col-1] * edge[0] +
                               copy[row-1][col]   * edge[1] +
                               copy[row-1][col+1] * edge[2]
                               ), 0, 255);

            image[row][col] = Clamp(qAbs(partial_x) + qAbs(partial_y), 0, 255);
        }
    }

    return true;
}


bool MyApp::Menu_Edge_SobolDirection(Image &image)
{
    return this->SobolDirection(image);
}


bool MyApp::SobolDirection(Image &image)
{
    int edge[3] = {1, 2, 1};
    Image copy = image;

    for (int row = 1; row < image.Height() - 1; row++)
    {
        for (int col = 1; col < image.Width() - 1; col++)
        {
            double partial_x = (copy[row-1][col+1] * edge[0] +
                               copy[row][col+1]    * edge[1] +
                               copy[row+1][col+1]  * edge[2]) -
                               (
                               copy[row-1][col-1] * edge[0] +
                               copy[row][col-1]   * edge[1] +
                               copy[row+1][col-1] * edge[2]
                               );

            double partial_y = (copy[row+1][col-1] * edge[0] +
                               copy[row+1][col]    * edge[1] +
                               copy[row+1][col+1] * edge[2]) -
                               (
                               copy[row-1][col-1] * edge[0] +
                               copy[row-1][col]   * edge[1] +
                               copy[row-1][col+1] * edge[2]
                               );

            double angle = atan2(partial_x, partial_y);
            image[row][col] = ((angle < 0 ? angle + 2 * M_PI : angle) / (2 * M_PI)) * 255.0;
        }
    }

    return true;
}

/*******************************************************************************
 *
 *      Filter Functions
 *
 ******************************************************************************/

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function calculates the laplacian filter output for an 3 x 3 region
 * centered at x-y in image.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int laplacian_filter( int x, int y, int n, Image & image )
{
    //Laplacian filter
    int filter[3][3] = {{-1, -1, -1},
                        {-1, 8, -1},
                        {-1, -1, -1}};

    //Apply the filter
    int sum = 0;
    for(int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3;  j++)
        {
            sum += filter[i][j]*inten(image,x-1+i,y-1+j);
        }
    }

    //Scale sum from (-1*8*255, 8*255) to (0, 255)
    sum += (8*255); //Make sure the number is positive
    sum *= 255;
    sum /= (8*255+8*255);

    return sum;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function calculates which kirsch filter has the biggest response on the
 * n X n region centered at x-y. The response is then clipped (as specified
 * from the program requirements), and returned.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int kirsch_magnitude_filter( int x, int y, int n, Image & image )
{
    int filter[8][3][3];    //Kirsch filters

    int sum = 0;        //Response of filter
    int max_sum = 0;    //Maximum response
    int max_i = 0;      //Index of filter with max response

    //Generate the filter
    generate_kirsch_filters(filter);
    for(int filter_i = 0; filter_i < 8; filter_i++)
    {
        //Apply the filter and calculate the sum
        sum = 0;
        for(int i = 0; i < 3; i++)
        {
            for( int j = 0; j < 3;  j++)
            {
                sum += filter[filter_i][i][j]*inten(image,x-1+i,y-1+j);
            }
        }
        if(sum > max_sum)
        {
            max_i = filter_i;
            max_sum = sum;
        }



    }

    //Scale sum from (-3*5*255, 3*5*255) to (0, 255)
    max_sum /= 3;
    if(max_sum < 0 )max_sum = 0;
    if(max_sum > 255 )max_sum = 255;

    return max_sum;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * This function calculates which kirsch filter has the biggest response on the
 * n X n region centered at x-y. The index of the filter is then mapped into
 * a particular intensity value between 0 and 244.
 *
 * @param[in] x         - center index for row
 * @param[in] y         - center index for col
 * @param[in] n         - dimension of area to filter
 * @param[in] image
 *
 * @returns int
 *
 ******************************************************************************/
int kirsch_filter( int x, int y, int n, Image & image )
{
    int filter[8][3][3];    //Kirsch filters
    int sum = 0;            //Response from filter
    int max_sum = 0;        //Highest response
    int max_i = 0;          //Index of filter with highest response

    //Generate the filters
    generate_kirsch_filters(filter);

    //Apply filters
    for(int filter_i = 0; filter_i < 8; filter_i++)
    {
        //Calculate response from filter
        sum = 0;
        for(int i = 0; i < 3; i++)
        {
            for( int j = 0; j < 3;  j++)
            {
                sum += filter[filter_i][i][j]*inten(image,x-1+i,y-1+j);
            }
        }

        //Keep track of the filter with the highest response
        if(sum > max_sum)
        {
            max_i = filter_i;
            max_sum = sum;
        }
    }

    //Map max_i into an intensity
    return (((max_i)%8)*255)/8;
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
 * Applies teh kirsch direction filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Edge_KirschDirection(Image &image)
{
    applyNbyNfilter(image, 3, kirsch_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Applies the kirsch magnitude filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Edge_KirschMagnitude(Image &image)
{
    applyNbyNfilter(image, 3, kirsch_magnitude_filter);
    return true;
}

/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Applies the laplacian
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Edge_Laplacian(Image &image)
{

    applyNbyNfilter(image, 3, laplacian_filter);
    return true;
}
