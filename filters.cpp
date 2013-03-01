#include "prog2.h"
#include "imageHelper.h"

bool SmoothingFilter(Image &image);
bool SharpeningFilter(Image &image);
bool PlusShapedMedianFilter(Image &image);
bool OutOfRangeNoiseCleaner(double threshold, Image &image);
bool Emboss(Image &image);


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



/****************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Provides a menu option for applying an out of range noise clean
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
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
 * Applies a 3x3 smoothing filter to the image
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool SmoothingFilter(Image &image)
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
bool SharpeningFilter(Image &image)
{
    int sharpeningFilter[3][3] = {{0, -1, 0},
                                  {-1, 5, -1},
                                  {0, -1, 0}};

    return ApplyFilter(image, sharpeningFilter);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 *
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Filters_Embossing(Image &image)
{
    return Emboss(image);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Creates a 3D like effect on the image being processed
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool Emboss(Image &image)
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
bool PlusShapedMedianFilter(Image &image)
{
    int filter[3][3] = {{0, 1, 0},
                        {1, 1, 1},
                        {0, 1, 0}};

    return ApplyFilter(image, filter);
}



/***************************************************************************//**
 * @author David Jarman
 *
 * @par Description:
 * Performs an out of range noise cleaner
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool OutOfRangeNoiseCleaner(double threshold, Image &image)
{
    //Copy the image so we don't process transformed pixers
    Image copy = image;

    for (int row = 1; row < image.Height() - 1; row++)
    {
        for (int col = 1; col < image.Width() - 1; col++)
        {
            //Sum the intensities of the pixels around the pixel
            //we are processing
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
/***************************************************************************//**
 * @author Hayden Waisanen
 *
 * @par Description:
 * Implements Gaussian smoothing.
 *
 * @param[in] image
 *
 * @returns bool
 *
 ******************************************************************************/
bool MyApp::Menu_Filters_GaussianSmoothing(Image &image)
{
    double sigma = 3.0;         //Sigma for the filter
    double gaus_filter[50][50]; //Array used to store filter
    int x, y;                   //Temporary index variables
    Image img_copy = image;     //Copy of input image
    double total = 0;           //Temporary total variable
    int row_i, col_i;           //Temporary index variable

    //Prompt for sigma
    if ( !Dialog( "Choose sigma" ).Add( sigma, "Sigma" ).Show() )
        return false;


    //Estimate filter dimensions to ensure a sum of ~1
    //(Calculated with regression analysis)
    int dimension = sigma*5+5;

    //Clip dimension at 49
    dimension = (dimension > 50)?49:dimension;
    if(dimension%2==0) dimension++; //Make sure dimension is odd


    //Generate the gaussian filter 5x5
    sigma *= sigma; //Square sigma
    for( int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            //Convert i and j to x and y for gaussian calculation
            x = i - (dimension-1)/2;
            y = j - (dimension-1)/2;
            gaus_filter[i][j] = (1 / (2 * 3.14159 * sigma ) ) * exp( -1 * ( double(x*x + y*y) / (2*sigma) ));

        }
    }

    int offset = (dimension-1)/2;

    //Loop through every pixel in the image
    for(int row = 0; row < image.Height(); row++)
    {
        for( int col = 0; col < image.Width(); col++)
        {
            total = 0.0;
            //Apply the filter
            for( int i = 0; i < dimension; i++)
            {
                for( int j = 0; j < dimension; j++)
                {
                    row_i = i -offset;
                    col_i = j -offset;

                    total += gaus_filter[i][j]*double(inten(img_copy,row+row_i,col+col_i));
                }
            }

            //Set calculated intensity
            image[row][col] = total;

        }
    }
    return true;
}
