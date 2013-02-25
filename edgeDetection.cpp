#include "prog2.h"
#include <qmath.h>

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

            image[row][col] = ((atan2(partial_x, partial_y) + M_PI) / (2 * M_PI)) * 255.0;
        }
    }

    return true;
}
