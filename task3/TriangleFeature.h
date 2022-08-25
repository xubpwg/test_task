#ifndef TRIANGLE_FEATURE_HEADER_GUARD
#define TRIANGLE_FEATURE_HEADER_GUARD

#include "Feature.h"
#include "FeatureDrawer.h"

class TriangleFeature : public Feature
{
public:
    TriangleFeature()
    {
        type = FeatureType::eTriangle;
        pointsSize = 6;
        points = new double[pointsSize];
    }

    void draw() const override
    {
        FeatureDrawer::drawPolygon(points, pointsSize);
    }
};

#endif // TRIANGLE_FEATURE_HEADER_GUARD