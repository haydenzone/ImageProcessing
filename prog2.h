#ifndef PROG2_H
#define PROG2_H

/***************************************************************************//**
 * @file
 * @brief Demostrates some point processing on images
 *
 * @mainpage Program 2 - Point Processing
 *
 * @authors Hayden Waisanen
 *
 * @date February 4, 2023
 ******************************************************************************/
#include <qtimagelib.h>

using namespace std;

class MyApp : public QObject
{
    Q_OBJECT;

protected:
    qreal Clamp(qreal value, qreal left, qreal right);
    bool ApplyFilter(Image &image, int filter[3][3]);
    int CreateSum(int filter[3][3]);
    virtual bool SmoothingFilter(Image &image);

public slots:
    //Palette Functions
    bool Menu_PreDefined_GrayScale(Image &image);
    bool Menu_PreDefined_DisplayHistogram(Image &image);
    bool Menu_PreDefined_HistogramStretch(Image &image);
    bool Menu_PreDefined_HistogramEquilization(Image &image);
    bool Menu_PreDefined_BinaryThreshold(Image &image);
    bool Menu_PreDefined_GaussianNoise(Image &image);
    bool Menu_PreDefined_ImpulseNoise(Image &image);

    bool Menu_Filters_Smooth(Image &image);
};

#endif // PROG2_H
