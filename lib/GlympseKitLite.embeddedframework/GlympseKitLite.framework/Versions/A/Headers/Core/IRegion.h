//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IREGION_H__GLYMPSE__
#define IREGION_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The IRegion interface defines a geographical area that can be tracked.
 * It extends ILatLng with radius, accuracy and id properties.
 * Id was added to have a chance to match regions across application sessions. 
 */
/*O*public**/ struct IRegion : public ILatLng, public IComparable
{
    /**
     * The radius (measured in meters) that defines the region’s outer boundary.
     */
    public: virtual double getRadius() = 0;
    
    /**
     * Represents the accuracy of a coordinate value in meters.
     */
    public: virtual double getAccuracy() = 0;
    
    /**
     * Unique identifier of the region object.
     */ 
    public: virtual GString getId() = 0;
};
    
/*C*/typedef O< IRegion > GRegion;/**/
    
}

#endif // !IREGION_H__GLYMPSE__
