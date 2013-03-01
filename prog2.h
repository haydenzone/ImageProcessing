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
 * @date February 4, 2013
 ******************************************************************************/
#include <qtimagelib.h>
#include <iostream>

using namespace std;

class MyApp : public QObject
{
    Q_OBJECT;

public slots:
    //Palette Functions
    bool Menu_PreDefined_GrayScale(Image &image);
    bool Menu_PreDefined_DisplayHistogram(Image &image);
    bool Menu_PreDefined_HistogramStretch(Image &image);
    bool Menu_PreDefined_HistogramEquilization(Image &image);
    bool Menu_PreDefined_BinaryThreshold(Image &image);
    bool Menu_PreDefined_GaussianNoise(Image &image);
    bool Menu_PreDefined_ImpulseNoise(Image &image);

    //Filters
    bool Menu_Filters_Smooth(Image &image);
    bool Menu_Filters_Sharpen(Image &image);
    bool Menu_Filters_PlusShapedMedian(Image &image);
    bool Menu_Filters_OutOfRangeNoiseClean(Image &image);
    bool Menu_Filters_Embossing(Image &image);
    bool Menu_Filters_GaussianSmoothing(Image &image);

    //Neighborhood Filters
    bool Menu_NeighborhoodFilters_Maximum(Image &image);
    bool Menu_NeighborhoodFilters_Minimum(Image &image);
    bool Menu_NeighborhoodFilters_Median(Image &image);
    bool Menu_NeighborhoodFilters_Mean(Image &image);
    bool Menu_NeighborhoodFilters_Range(Image &image);
    bool Menu_NeighborhoodFilters_StandardDeviation(Image &image);

    //Edge Detectors
    bool Menu_Edge_SobolMagnitude(Image &image);
    bool Menu_Edge_SobolDirection(Image &image);
    bool Menu_Edge_Laplacian(Image &image);
    bool Menu_Edge_KirschMagnitude(Image &image);
    bool Menu_Edge_KirschDirection(Image &image);
};

#endif // PROG2_H
