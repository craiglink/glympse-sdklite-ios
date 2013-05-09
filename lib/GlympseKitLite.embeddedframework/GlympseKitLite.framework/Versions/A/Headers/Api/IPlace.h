//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPLACE_H__GLYMPSE__
#define IPLACE_H__GLYMPSE__

namespace Glympse 
{
    
/*J*
// Helps Doxygen to find dependencies properly. 
import com.glympse.android.core.GLatLng;
import com.glympse.android.core.GComparable;
**/
    
/*C*/
struct IPlace;
typedef O< IPlace > GPlace;
/**/
    
/** 
 * Specifies a named place and location. Currently, the Place object is only used for destinations 
 * of Glympses and only supports latitude and longitude for location.
 */
/*O*public**/ struct IPlace : public ILatLng, public IComparable
{
    /**
     * Gets the friendly name of this place.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets the address of this place.
     */    
    public: virtual GString getAddress() = 0;        

    /**
     * Clones current place object. 
     */
    public: virtual GPlace clone() = 0;      
};
    
}

#endif // !IPLACE_H__GLYMPSE__
