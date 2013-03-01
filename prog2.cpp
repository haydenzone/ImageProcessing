/***************************************************************************//**
 * @file
 * @brief Demostrates some neighborhood processing on images
 *
 * @mainpage Program 2 - Neighborhood Processing
 *
 * @section course_section Course Information
 *
 * @author Hayden Waisanen
 * @author David Jarman
 *
 * @date February 28, 2013
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
 *      of neighborhood processes including:
 *          - Smoothing filter
 *          - Sharpening filter
 *          - Median filter
 *          - Noise cleaning
 *          - Statistical filters
 *              - Mean
 *              - Median
 *              - Min, Max
 *              - Range
 *              - Standard Deviation
 *          - Embossing
 *          - Edge Detection
 *              - Sobol
 *              - Kirsch
 *              - Laplacian
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 * @verbatim
 * $ qmake
 * $ prog2.exe
 * @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  none
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
<<<<<<< HEAD
   @verbatim
   Date          Modification
   ------------  ---------------------------------------------------------------
   Feb  4, 2013  Initial commit - Hayden Waisanen
   Feb  5, 2013  Initial files added - Hayden Waisanen
   Feb  6, 2013  Added authors. - Hayden Waisanen
   Feb 11, 2013  Added all predefined imagelib methods - David Jarman
   Feb 12, 2013  Added a generic way to apply filters - David Jarman
   Feb 12, 2013  Implemented sharpening - David Jarman
   Feb 12, 2013  Implemented the plus shaped median filter - David Jarman
   Feb 21, 2013  Added file for neighborhood filters. Implemented maximum and
                 minimum. - Hayden Waisanen
   Feb 21, 2013  Completed N x N statistical filters - Hayden Waisanen
   Feb 24, 2013  Added embossing and out of range filtering - David Jarman
   Feb 24, 2013  Sobol edge and magnitude added - David Jarman
   Feb 24, 2013  Fixed an off by 1 error in the applyNbyNfilter function - Hayden Waisanen
   Feb 25, 2013  Moved edge detection functions into their own file. - Hayden Waisanen
   Feb 27, 2013  Implemented Kirsch edge functions (possible bugs...) - Hayden Waisanen
   Feb 27, 2013  Took Weiss's implementation notes to heart - David Jarman
   Feb 28, 2013  Optimized min and max filter - Hayden Waisanen
   Feb 28, 2013  Rotated kirsch filters to produce a result similar to
                 Weiss - Hayden Waisanen
   Feb 28, 2013  Implemented Gaussian Smoothing - Hayden Waisanen
   Feb 28, 2013  Added readme - Hayden Waisanen
   Feb 28, 2013  Implemented inten function which will allow for dealing with
                 edges of images - Hayden Waisanen
   Feb 28, 2013  Implemented inten for the gaussian filter - Hayden Waisanen

   @endverbatim
=======
 * @verbatim
 * Date          Modification
 * ------------  ---------------------------------------------------------------
 *
 *  @endverbatim
>>>>>>> origin/David-Commenting
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "prog2.h"
#include "imageHelper.h"
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
