#include "prog2.h"
#include <qmath.h>
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


bool MyApp::Menu_Edge_LaPlacian(Image &image)
{

    applyNbyNfilter(image, 3, laplacian_filter);
    return true;
}

int laplacian_filter( int x, int y, int n, Image & image )
{
    int filter[3][3] = {{-1, -1, -1},
                        {-1, 8, -1},
                        {-1, -1, -1}};

    int sum = 0;
    for(int i = 0; i < 3; i++)
    {
        for( int j = 0; j < 3;  j++)
        {
            sum += filter[i][j]*image[x-1+i][y-1+j];
        }
    }

    //Scale sum from (-1*8*255, 8*255) to (0, 255)
    sum += (8*255); //Make sure the number is positive
    sum *= 255;
    sum /= (8*255+8*255);

    return sum;
}

bool MyApp::Menu_Edge_KirschMagnitude(Image &image)
{

    applyNbyNfilter(image, 3, kirsch_magnitude_filter);
    return true;
}
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
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                target[i][j][k] = filter[i][j][k];
    return;
}
int kirsch_magnitude_filter( int x, int y, int n, Image & image )
{
    int filter[8][3][3];

    int sum = 0;
    int max_sum = 0;
    int max_i = 0;

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
                sum += filter[filter_i][i][j]*image[x-1+i][y-1+j];
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

bool MyApp::Menu_Edge_Kirsch(Image &image)
{
    applyNbyNfilter(image, 3, kirsch_filter);
    return true;
}
int kirsch_filter( int x, int y, int n, Image & image )
{
    int filter[8][3][3];
    int sum = 0;
    int max_sum = 0;
    int max_i = 0;

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
                sum += filter[filter_i][i][j]*image[x-1+i][y-1+j];
            }
        }
        if(sum > max_sum)
        {
            max_i = filter_i;
            max_sum = sum;
        }
    }

    //Map max_i into an intensity

    return (((max_i)%8)*255)/8;
}
