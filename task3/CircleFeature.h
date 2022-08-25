#ifndef CIRCLE_FEATURE_HEADER_GUARD
#define CIRCLE_FEATURE_HEADER_GUARD

#include "Feature.h"
#include "FeatureDrawer.h"

class CircleFeature : public Feature
{
public:
    CircleFeature()
    {
        type = FeatureType::eCircle;
        pointsSize = 3;
        points = new double[pointsSize];
    }             

    void draw() const override
    {
        FeatureDrawer::drawCircle(points[0], points[1], points[2]);
    }
};

#endif // CIRCLE_FEATURE_HEADER_GUARD