//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILATLNG_H__GLYMPSE__
#define ILATLNG_H__GLYMPSE__

namespace Glympse 
{

/**
 * Specifies a single location point (latitude and longitude).
 */
/*O*public**/ struct ILatLng : public virtual ICommon
{
    public: virtual bool hasLocation() = 0;

    public: virtual double getLatitude() = 0;
    
    public: virtual double getLongitude() = 0;    
    
    public: virtual int32 getLatitudeE6() = 0;
    
    public: virtual int32 getLongitudeE6() = 0;
};
    
/*C*/typedef O< ILatLng > GLatLng;/**/ 
    
}
    
#endif // !ILATLNG_H__GLYMPSE__
