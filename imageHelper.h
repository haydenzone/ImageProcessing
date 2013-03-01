#ifndef IMAGEHELPER_H
#define IMAGEHELPER_H

/******************************************************************************
 * Includes
 ******************************************************************************/
#include <qtimagelib.h>
#include <QtCore/qmath.h>

/******************************************************************************
 * Prototypes
 ******************************************************************************/
void intensity_distribution(Image& image, int x_0, int y_0, int n, int intensities[]);
int inten(Image &image, int row, int col);
void applyNbyNfilter(Image &image, int n, int (*filter)(int, int, int, Image&));
void generate_kirsch_filters(int target[][3][3]);
qreal Clamp(qreal value, qreal left, qreal right);
int CreateSum(int filter[3][3]);
bool ApplyFilter(Image &image, int filter[3][3]);

#endif // IMAGEHELPER_H
