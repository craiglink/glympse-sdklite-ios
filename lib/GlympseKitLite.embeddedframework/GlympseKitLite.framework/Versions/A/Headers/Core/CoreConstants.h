//------------------------------------------------------------------------------
//
// Copyright (c) Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef CORECONSTANTS_H__GLYMPSE__
#define CORECONSTANTS_H__GLYMPSE__

namespace Glympse 
{
 
/**
 * Basic enumerations belonging to Core layer. 
 */
/*O*public**/ class CoreConstants
{
    /**
     * @name Primitive Types
     *
     * Enumeration of all types supported by IPrimitive object. 
     */

    public: static const int32 PRIMITIVE_TYPE_ARRAY         = 0x00000001;
    public: static const int32 PRIMITIVE_TYPE_OBJECT        = 0x00000002;
    public: static const int32 PRIMITIVE_TYPE_DOUBLE        = 0x00000004;
    public: static const int32 PRIMITIVE_TYPE_LONG          = 0x00000008;
    public: static const int32 PRIMITIVE_TYPE_BOOLEAN       = 0x00000010;
    public: static const int32 PRIMITIVE_TYPE_STRING        = 0x00000020;
    public: static const int32 PRIMITIVE_TYPE_NULL          = 0x00000040;

    /**
     * @name Location Provider States
     *
     * Location provider changes its internal state between one of these values.
     */
    
    public: static const int32 LOCATION_STATE_NOT_DETERMINED  = 1;
    public: static const int32 LOCATION_STATE_DENIED          = 2;
    public: static const int32 LOCATION_STATE_ACQUIRED        = 3;
    public: static const int32 LOCATION_STATE_ERROR           = 4;
    
    /**
     * @name Log Levels
     * 
     * Log level specifies the level of details of log messages.
     * Log levels are ordered from the most informative INFO to the least informative CRITICAL.
     * Log levels are applied through IGlympse#overrideLoggingLevels().
     */
    
    public: static const int32 INFO         = 1;
    public: static const int32 DUMP         = 2;
    public: static const int32 NOTICE       = 3;
    public: static const int32 WARNING      = 4;
    public: static const int32 ERROR        = 5;
    public: static const int32 CRITICAL     = 6;
    public: static const int32 NONE         = 7;
    
    /**
     * @name Location Profiles
     *
     * The list of all supported location profiles on the system.
     */
    
    /**
     * Indentifies the case, when profile is not set. 
     */
    public: static const int32 LOCATION_PROFILE_NOT_SET                 = -1;
    
    /**
     * Application is running in the background without active outgoing tickets.
     */
    public: static const int32 LOCATION_PROFILE_NO_ACTIVE_BACKGROUND    = 0;
    
    /**
     * Application is running in the foreground without active outgoing tickets.
     */
    public: static const int32 LOCATION_PROFILE_NO_ACTIVE_FOREGROUND    = 1;
    
    /**
     * Application is running with active outgoing tickets, but nobody is watching.
     */
    public: static const int32 LOCATION_PROFILE_ACTIVE_NOT_WATCHED      = 2;

    /**
     * Application is running with active outgoing tickets and somebody is watching.
     */
    public: static const int32 LOCATION_PROFILE_ACTIVE_IS_WATCHED       = 3;
    
    /**
     * Total amount of profiles. 
     */
    public: static const int32 LOCATION_PROFILES_COUNT                  = 4;
    
    /**
     * @name Location Sources
     *
     * The list of supported location sources.
     */

    public: static const int32 LOCATION_SOURCE_NETWORK    = 0x00000001;
    public: static const int32 LOCATION_SOURCE_GPS        = 0x00000002;
    public: static const int32 LOCATION_SOURCE_PASSIVE    = 0x00000004;
    public: static const int32 LOCATION_SOURCE_ALL
        = LOCATION_SOURCE_NETWORK
        | LOCATION_SOURCE_GPS;
    
    /**
     * @name Location Modes
     *
     * The list of modes supported by location manager (and applied to location providers).
     */
    
    /**
     * Inherits default Client API behavior. 
     */
    public: static const int32 LOCATION_MODE_DEFAULT    = 0;
    
    /**
     * Disables location provider even if Client API assumes that it should be started.
     */ 
    public: static const int32 LOCATION_MODE_DISABLED   = 1;
};
    
}

#endif // !CORECONSTANTS_H__GLYMPSE__
