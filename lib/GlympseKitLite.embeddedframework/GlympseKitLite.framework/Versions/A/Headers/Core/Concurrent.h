//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CONCURRENT_H__GLYMPSE__
#define CONCURRENT_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The Concurrent class provides set of basic concurrency primitives.
 */
class Concurrent
{
    /**
     * Increments (increases by one) the value of the specified variable as an atomic operation.
     * The function returns the resulting incremented value.
     */    
    public: static int32 increment(int32* ptr);            
        
    /**
     * Decrements (decreases by one) the value of the specified variable as an atomic operation.
     * The function returns the resulting decremented value.
     */    
    public: static int32 decrement(int32* ptr);                
    
    /**
     * Returns local system UTC time in milliseconds.
     */
    public: static int64 getTime();
    
    /**
     * Background operation is not supported by the platform.
     * Application is completely terminated, once it goes to the background.
     * Platforms: iOS (prior to 4.0), Windows Phone 7.x.
     */ 
    public: static const int32 BACKGROUND_NONE = 0x0;
    
    /**
     * Background operation is partially supported by the platform.
     * Application is only notified on specific events (location updates).
     * Platforms: iOS (4.0 and above). 
     */ 
    public: static const int32 BACKGROUND_EVENTS = 0x1;    
    
    /**
     * Background operation is supported by the platform without any limitations.
     * Application main event loop functions as usual. 
     * Platforms: Android, BlackBerry, Windows Phone 8.0 and above.
     */ 
    public: static const int32 BACKGROUND_FULL = 0x2;        
    
    /**
     * Returns background mode supported by the platform. 
     */
    public: static int32 getBackgroundMode();
    
    /**
     * Sends current thread to sleep for the specified amount of time in milliseconds.
     */
    public: static void sleep(int64 delay);
};
    
}

#endif // !CONCURRENT_H__GLYMPSE__
