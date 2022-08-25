#ifndef FEATURE_HEADER_GUARD
#define FEATURE_HEADER_GUARD

#include "FeatureType.h"

class Feature
{
public:
    Feature() = default;
    virtual ~Feature() 
    {
        if (points)
        {
            delete[] points;
        }
    };

    double* getPoints()
    {
        return points;
    }

    const int getPointsSize() const
    {
        return pointsSize;
    }

    virtual void draw() const = 0;

    bool isValid() 		
    {
        return type != FeatureType::eUnknown && points != nullptr;
    }

protected:
    double* points = nullptr;
    FeatureType type = FeatureType::eUnknown;
    int pointsSize = 0;
};

#endif // FEATURE_HEADER_GUARD