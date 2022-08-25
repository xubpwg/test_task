#ifndef FEATURE_BUILDER_HEADER_GUARD
#define FEATURE_BUILDER_HEADER_GUARD

#include "CircleFeature.h"
#include "TriangleFeature.h"
#include "SquareFeature.h"

class FeatureBuilder
{
public:
    static Feature* createFeature(FeatureType type)
    {
        switch(type)
        {
        case FeatureType::eCircle:
            return new CircleFeature();
        case FeatureType::eSquare:
            return new SquareFeature();
        case FeatureType::eTriangle:
            return new TriangleFeature();
        default:
            return nullptr;
        }
    }
};

#endif // FEATURE_BUILDER_HEADER_GUARD