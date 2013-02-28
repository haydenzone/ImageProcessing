#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <qtimagelib.h>

/******************************************************************************
 * Prototypes
 ******************************************************************************/
void intensity_distribution(Image& image, int x_0, int y_0, int n, int intensities[]);
int inten(Image &image, int row, int col);
void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&));
void generate_kirsch_filters(int target[][3][3]);

#endif // IMAGEHELPER_H
