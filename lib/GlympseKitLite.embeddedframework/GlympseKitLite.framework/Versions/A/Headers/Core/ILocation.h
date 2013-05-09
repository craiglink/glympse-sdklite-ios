//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATION_H__GLYMPSE__
#define ILOCATION_H__GLYMPSE__

namespace Glympse 
{
        
/*C*/
struct ILocation;
typedef O< ILocation > GLocation;
/**/

/**
 * Specifies a single location point (latitude and longitude) at a given time, 
 * with optional altitude, bearing, speed, and accuracy information.
 */
/*O*public**/ struct ILocation : public ILatLng
{    
    public: virtual bool hasProvider() = 0;
    
    public: virtual bool hasAltitude() = 0;    
    
    public: virtual bool hasBearing() = 0;    
    
    public: virtual bool hasSpeed() = 0;    
    
    public: virtual bool hasHAccuracy() = 0;    
    
    public: virtual bool hasVAccuracy() = 0;        
    
    public: virtual bool hasTime() = 0;

    public: virtual int32 getProvider() = 0;

    public: virtual float getAltitude() = 0;

    public: virtual float getBearing() = 0;
    
    public: virtual float getSpeed() = 0;
    
    public: virtual float getHAccuracy() = 0;
    
    public: virtual float getVAccuracy() = 0;
    
    public: virtual int64 getTime() = 0;    
    
    public: virtual GLocation clone() = 0;        
        
    /**
     * @return Distance in meters, or NaN, if distance could not be calculated. 
     */
    public: virtual double distance(const GLatLng& location) = 0;
};
    
}

#endif // !ILOCATION_H__GLYMPSE__
