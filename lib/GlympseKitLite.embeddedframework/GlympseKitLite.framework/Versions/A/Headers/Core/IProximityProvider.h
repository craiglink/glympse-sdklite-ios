//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IPROXIMITYPROVIDER_H__GLYMPSE__
#define IPROXIMITYPROVIDER_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The IProximityProvider provides standard interface for geo-fencing. The following scenarios are supported:
 * - device enters a region;
 * - device leaves a region.
 *
 * Proximity provider may or may not stop monitoring regions automatically after delivering notification.
 *
 * Here is how to set external provider. It is only allowed to call IGlympse#getLocationManager()
 * method after starting the platform (by calling IGlympse#start()).
 *
 * @code
 * GGlympse glympse = ...;
 * glympse->start();
 * glympse->getLocationManager()->setProximityProvider(new CustomProximityProvider());
 * @endcode
 */
/*O*public**/ struct IProximityProvider : public ICommon
{
    /**
     * Attaches location listener to the provider.
     */
    public: virtual void setLocationListener(const GLocationListener& locationListener) = 0;
    
    /**
     * Starts monitoring the region.
     *
     * @note Some provider implementations require unique identifier to be associated with 
     * the region to be able to identify it accross application sessions. IRegion::getId()
     * is provided for this purpose. Make sure that this ID is unique during the entire 
     * application lifetime and does not overlap with other regions registered for monitoring.
     *
     * @param region Region object to start monitoring.
     */
    public: virtual void startMonitoring(const GRegion& region) = 0;
    
    /**
     * Starts monitoring the list of regions. 
     */
    public: virtual void startMonitoring(const GArray<GRegion>::ptr& regions) = 0;    
    
    /**
     * Stops monitoring the region.
     */
    public: virtual void stopMonitoring(const GRegion& region) = 0;
    
    /**
     * This method is called, when location manager is notified on new location point by location provider. 
     *
     * @note This mechanizm should not be treated as trusted, as location manager propagates location
     * updates to proximity provider only, when location provider is started (which is often related 
     * to the presence of active outgoing tickets). Proximity provider should rely on another source
     * of location data or consume OS API, if geo-fencing functionality is required, while location
     * manager is stopped.
     *
     * @param location New location object.
     */
    public: virtual void locationChanged(const GLocation& location) = 0;
    
    /**
     * Stops monitoring all regions and returns the list. 
     * 
     * @return The list of regions monitored by the provider.
     */
    public: virtual GArray<GRegion>::ptr detachRegions() = 0;
};
    
/*C*/typedef O< IProximityProvider > GProximityProvider;/**/
    
}

#endif // !IPROXIMITYPROVIDER_H__GLYMPSE__
