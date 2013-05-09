//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILOCATIONLISTENER_H__GLYMPSE__
#define ILOCATIONLISTENER_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Common interface for receiving updates from location and proximity providers.
 */
/*O*public**/ struct ILocationListener : public virtual ICommon
{
    /**
     * @name ILocationProvider Section
     *
     * Group of methods called by ILocationProvider.
     */
    
    /**
     * Notifies on new location.
     */
    public: virtual void locationChanged(const GLocation& location) = 0;
    
    /**
     * Location provider state changed. See CC::LOCATION_STATE_* for more details.
     *
     * This method is called by ILocationProvider.
     */
    public: virtual void stateChanged(int32 state) = 0;
    
    /**
     * @name IProximityProvider Section
     *
     * Group of methods called by IProximityProvider.     
     */    
    
    /**
     * Fired when region is entered.
     */
    public: virtual void regionEntered(const GRegion& region) = 0;

    /**
     * Fired when region is left.
     */
    public: virtual void regionLeft(const GRegion& region) = 0;
};
    
/*C*/typedef O< ILocationListener > GLocationListener;/**/
    
}

#endif // !ILOCATIONLISTENER_H__GLYMPSE__
