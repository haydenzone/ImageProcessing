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
