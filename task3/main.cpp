#include "FeatureReader.h"
#include "FeatureBuilder.h"

int main()
{
    FeatureReader featureReader;
    if (!featureReader.isInitialized())
    {
        return 1;
    }

    FeatureType featureType = FeatureType::eUnknown;
    featureReader.readFeatureType(&featureType);

    Feature* feature = FeatureBuilder::createFeature(featureType);	
    featureReader.readFeaturePoints(feature->getPoints(), feature->getPointsSize());

    if (!feature->isValid())
    {
        return 1;
    }			  				  
    return 0;
}