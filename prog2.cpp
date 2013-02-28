/***************************************************************************//**
 * @file
 * @brief Demostrates some point processing on images
 *
 * @mainpage Program 1 - Point Processing
 *
 * @section course_section Course Information
 *
 * @authors Hayden Waisanen
 *
 * @date February 4, 2013
 *
 * @par Instructor:
 *         Professor Weiss
 *
 * @par Course:
 *         CSC464/564 Image Processing – Spring 2013
 *
 * @par Location:
 *         McLaury - Room 313
 *
 * @section program_section Program Information
 *
 * @details This program utilizes the the ImageLib to implement a series
 *      of point processes including:
 *          - Grayscale
 *          - Sepia
 *          - Histogram Equilization
 *          - Contrast Stretch
 *          - Brightness
 *          - Posterize
 *          - etc.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   $ qmake
   $ prog3.exe
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  none
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  ---------------------------------------------------------------
   Jan 27, 2013  Began experimenting with qtimagelib
   Jan 30, 2013  Completed: grayscal, brightness, contrast
   Feb  1, 2013  Completed: sepia, pseudocolor, histogram, log, gamm
   Feb  2, 2013  Completed: all but histogram equilization
   Feb  4, 2013  Documentation and Testing
   @endverbatim
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "prog2.h"
#include <QtCore/qmath.h>
#include <QDebug>
/***************************************************************************//**
 * @author Hayden Waisanen
 * @author David Jarman
 *
 * @par Description:
 * Launches GUI.
 *
 * @param[in] argc
 * @param[in] argv
 *
 * @returns int
 *
 ******************************************************************************/
int main( int argc, char *argv[] )
{
    MyApp obj;
    ImageApp app( argc, argv );
    app.AddActions( &obj );
    return app.Start();
}

/*******************************************************************************
 * Menu Functions
 ******************************************************************************/

/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Converts an image to grayscale
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_GrayScale(Image &image)
{
    return grayscale(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Displays the histogram of the image in a seperate window
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_DisplayHistogram(Image &image)
{
    displayHistogram(image);

    return true;
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Performs a histogram stretch on the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_HistogramStretch(Image &image)
{
    return histogramStretch(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Performs a histogram equilization on the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_HistogramEquilization(Image &image)
{
    return histogramEqualize(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Turns the image into black and white based on an intensity threshold
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_BinaryThreshold(Image &image)
{
    int threshold = 128;
    Dialog thresholdDialog;
    thresholdDialog.Add(threshold, "Enter threshold", 0, 255);
    if(!thresholdDialog.Show())
    {
        return false;
    }

    return binaryThreshold(image, threshold);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Adds Gaussian noise to the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_GaussianNoise(Image &image)
{
    double sigma = 8.0;
    Dialog noiseDialog;
    noiseDialog.Add(sigma, "Enter sigma", 0.0, 100.0);
    if(!noiseDialog.Show())
    {
        return false;
    }

    gaussianNoise(image, sigma);

    return true;
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Adds impulse noise to the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_PreDefined_ImpulseNoise(Image &image)
{
    int probability = 64;
    Dialog noiseDialog;
    noiseDialog.Add(probability, "Enter probability", 0, 1000);
    if(!noiseDialog.Show())
    {
        return false;
    }

    impulseNoise(image, probability);

    return true;
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Provides a menu option for smoothing an image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Filters_Smooth(Image &image)
{
    return SmoothingFilter(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Provides a menu option for sharpening an image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Filters_Sharpen(Image &image)
{
    return SharpeningFilter(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Provides a menu option for applying a plus shaped median filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Filters_PlusShapedMedian(Image &image)
{
    return PlusShapedMedianFilter(image);
}

bool MyApp::Menu_Filters_OutOfRangeNoiseClean(Image &image)
{
    int threshold = 128;
    Dialog thresholdDialog;
    thresholdDialog.Add(threshold, "Enter threshold", 0, 255);
    if(!thresholdDialog.Show())
    {
        return false;
    }

    return OutOfRangeNoiseCleaner(threshold, image);
}


/*******************************************************************************
 * Transform Functions
 ******************************************************************************/


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
qreal MyApp::Clamp(qreal value, qreal left, qreal right)
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
int MyApp::CreateSum(int filter[3][3])
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
bool MyApp::ApplyFilter(Image &image, int filter[3][3])
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

    try
    {
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
    }
    catch(exception& ex)
    {
        return false;
    }

    return true;
}

/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Applies a 3x3 smoothing filter to the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::SmoothingFilter(Image &image)
{
    int smoothingFilter[3][3] = {{1, 2, 1},
                                 {2, 4, 2},
                                 {1, 2, 1}};

    return ApplyFilter(image, smoothingFilter);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Applies a 3x3 sharpening filter to the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::SharpeningFilter(Image &image)
{
    int sharpeningFilter[3][3] = {{0, -1, 0},
                                  {-1, 5, -1},
                                  {0, -1, 0}};

    return ApplyFilter(image, sharpeningFilter);
}



bool MyApp::Menu_Filters_Embossing(Image &image)
{
    return Emboss(image);
}


bool MyApp::Emboss(Image &image)
{
    for (int row = 0; row < image.Height() - 1; row++)
    {
        for (int col = 0; col < image.Width() - 1; col++)
        {
            image[row][col] = (image[row][col] - image[row+1][col+1]) / 2.0 + 128.5;
        }
    }

    return true;
}


/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Applies a 3x3 plus shaped median filter
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::PlusShapedMedianFilter(Image &image)
{
    int filter[3][3] = {{0, 1, 0},
                        {1, 1, 1},
                        {0, 1, 0}};

    return ApplyFilter(image, filter);
}


bool MyApp::OutOfRangeNoiseCleaner(double threshold, Image &image)
{
    Image copy = image;

    for (int row = 1; row < image.Height() - 1; row++)
    {
        for (int col = 1; col < image.Width() - 1; col++)
        {
            double p_bar = 0.0;
            for (int p_row = row - 1; p_row <= row + 1; p_row++)
            {
                for (int p_col = col - 1; p_col <= col + 1; p_col++)
                {
                    if (p_row != row && p_col != col)
                    {
                        p_bar += copy[p_row][p_col];
                    }
                }
            }

            p_bar /= 8.0;

            double p_0 = copy[row][col];

            if (qAbs(p_0 - p_bar) > threshold)
            {
                image[row][col] = p_bar + .5;
            }
        }
    }

    return true;
}

bool MyApp::Menu_Filters_GaussianSmoothing(Image &image)
{
    double sigma = 3.0;
    double gaus_filter[50][50];
    int x, y;
    Image img_copy = image;
    double total = 0;
    int row_i, col_i;

    //Prompt for sigma
    if ( !Dialog( "Choose sigma" ).Add( sigma, "Sigma" ).Show() )
        return false;


    //Estimate filter dimensions to ensure a sum of 1
    //(Calculated with regression analysis)
    int dimension = sigma*5+5;

    //Clip dimension at 50
    dimension = (dimension > 50)?50:dimension;
    if(dimension%2==0) dimension++; //Make sure dimension is odd


    //Generate the gaussian filter 5x5
    sigma *= sigma; //Square sigma
    for( int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            x = i - (dimension-1)/2;
            y = j - (dimension-1)/2;
            gaus_filter[i][j] = (1 / (2 * 3.14159 * sigma ) ) * exp( -1 * ( double(x*x + y*y) / (2*sigma) ));

        }
    }

    int offset = (dimension-1)/2;
    for(int row = offset; row < image.Height()-offset; row++)
    {
        for( int col = offset; col < image.Width()-offset; col++)
        {
            total = 0.0;
            //Apply the filter
            for( int i = 0; i < dimension; i++)
            {
                for( int j = 0; j < dimension; j++)
                {
                    row_i = i -offset;
                    col_i = j -offset;

                    total += gaus_filter[i][j]*double(img_copy[row+row_i][col+col_i]);
                }
            }

            image[row][col] = total;

        }
    }
    return true;
}


