#ifndef SQUARE_FEATURE_HEADER_GUARD
#define SQUARE_FEATURE_HEADER_GUARD

#include "Feature.h"
#include "FeatureDrawer.h"

class SquareFeature : public Feature
{
public:
    SquareFeature()
    {
        type = FeatureType::eSquare;
        pointsSize = 8;
        points = new double[pointsSize];
    } 

    void draw() const override
    {
        FeatureDrawer::drawPolygon(points, pointsSize);
    }
};

#endif // SQUARE_FEATURE_HEADER_GUARD