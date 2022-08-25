#ifndef FEATURE_READER_HEADER_GUARD
#define FEATURE_READER_HEADER_GUARD

#include <cstdio>

#include "FeatureType.h"

class FeatureReader
{
public:
    FeatureReader()
    {
        fd = std::fopen("features.dat", "r");
    }

    ~FeatureReader()
    {
        std::fclose(fd);
    }

    const bool isInitialized() const
    {
        return fd != nullptr;
    }

    bool readFeatureType(FeatureType* type)
    {        
        if (std::fread(type, sizeof(FeatureType), 1, fd) != sizeof(FeatureType))
        {
            return false;
        }
        return true;
    }

    bool readFeaturePoints(double* points, int pointsSize)
    {     
        return std::fread(points, sizeof(double), pointsSize, fd) == pointsSize * sizeof(double);	
    }

private:
    std::FILE* fd = nullptr;
};

#endif // FEATURE_READER_HEADER_GUARD