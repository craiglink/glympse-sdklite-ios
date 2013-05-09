//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef COREFACTORY_H__GLYMPSE__
#define COREFACTORY_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The CoreFactory class provides factory methods for constructing all API primitives.
 */
/*O*public**/ class CoreFactory
{
    private: CoreFactory();
    
    /**
     * Constructs string object.
     */
    public: static GString createString(const char* value);   
    
    /**
     * Constructs string object.
     */
    public: static GString createString(const char* value, int32 length);       
    
    /**
     * Constructs GDrawable from platform specific image.
     */
    public: static GDrawable createDrawable(void* image);
    
    /**
     * Constructs GDrawable from a graphic file.
     */
    public: static GDrawable createDrawable(const GString& path, int32 rotation);
    
    /**
     * Constructs uninitialized primitive object of specific type.
     * It might be useful for array and object primitives
     * (CC::PRIMITIVE_TYPE_ARRAY, CC::PRIMITIVE_TYPE_OBJECT).
     *
     * @param type Primitive type. See CC for details. 
     */
    public: static GPrimitive createPrimitive(int32 type);
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_DOUBLE type.
     */
    public: static GPrimitive createPrimitive(double value);    
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_LONG type.
     */
    public: static GPrimitive createPrimitive(int64 value);        
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_BOOL type.
     */
    public: static GPrimitive createPrimitive(bool value);            
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_STRING type.
     */
    public: static GPrimitive createPrimitive(const GString& value);  
    
    /**
     * Constructs initialized primitive object of CC::PRIMITIVE_TYPE_NULL type.
     */
    public: static GPrimitive createPrimitive();
    
    /**
     * Creates new location profile for iOS. 
     *
     * @param profile Location profile identifier.
     * @param distance Minimum distance between location updates (in meters).
     * @param accuracy The accuracy of the location data.
     * @param activity The type of user activity associated with the location updates.  
     * @param autoPause A bool value indicating whether the location provider object may pause location updates.
     * @return Constructed and configured profile object that can be applied to location manager.
     * using ILocationManager#updateProfile().
     */
    public: static GLocationProfile createProfile(int32 profile, double distance, double accuracy, int32 activity, bool autoPause);

    /**
     * Creates new location profile for BB, version 10+.
     *
     * @param profile Location profile identifier.
     * @param source A combination of any of CC::LOCATION_SOURCE_* values.
     * @param frequency Desired frequency between location updates (in milliseconds).
     * @param accuracy The accuracy of the location data (in meters).
     * @return Constructed and configured profile object that can be applied to location manager.
     * using ILocationManager#updateProfile().
     */
    public: static GLocationProfile createProfile(int32 profile, int32 source, int32 frequency, double accuracy);

    /**
     * Creates new location object from location data.
     *
     * time, latitude and longitude fields must be specified. Any other field can be set to Float.NaN.
     *
     * @param time Location timestamp (milliseconds since 1/1/1970). It is preferable to use server time here.
     * @param latitude Location latitude in degrees.
     * @param longitude Location longitude in degrees.
     * @param speed Location speed in meters per second over ground. Speed must be positive.
     * @param bearing Location bearing in degrees. Bearing is the horizontal direction of travel of this device,
     * and is not related to the device orientation. The input must be in range [0.0, 360.0].
     * @param altitude Location altitude in meters above sea level.
     * @param haccuracy Horizontal accuracy of this location in meters.
     * @param vaccuracy Vertical accuracy of this location in meters.
     */
    public: static GLocation createLocation(int64 time, double latitude, double longitude,
        float speed, float bearing, float altitude, float haccuracy, float vaccuracy);
    
    /**
     * Creates new region object. 
     *
     * @param latitude The latitude of the central point of the alert region.
     * @param longitude The longitude of the central point of the alert region.
     * @param radius The radius of the central point of the alert region, in meters.
     * @param rid Unique identifier of a region.
     * @return Region object.
     */
    public: static GRegion createRegion(double latitude, double longitude, double radius, const GString& rid);
};
    
}

#endif // !COREFACTORY_H__GLYMPSE__
