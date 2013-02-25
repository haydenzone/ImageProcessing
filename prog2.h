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
#include <iostream>

using namespace std;

class MyApp : public QObject
{
    Q_OBJECT;

protected:
    qreal Clamp(qreal value, qreal left, qreal right);
    int CreateSum(int filter[3][3]);

    virtual bool ApplyFilter(Image &image, int filter[3][3]);
    virtual bool SmoothingFilter(Image &image);
    virtual bool SharpeningFilter(Image &image);
    virtual bool PlusShapedMedianFilter(Image &image);
    virtual bool OutOfRangeNoiseCleaner(double threshold, Image &image);
    virtual bool Emboss(Image &image);
    virtual bool SobolMagnitude(Image &image);
    virtual bool SobolDirection(Image &image);


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
    bool Menu_Filters_Sharpen(Image &image);
    bool Menu_Filters_PlusShapedMedian(Image &image);
    bool Menu_Filters_OutOfRangeNoiseClean(Image &image);
    bool Menu_Filters_Embossing(Image &image);

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
};

#endif // PROG2_H
