//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef __cplusplus
    #error You must rename your files to .mm to use the Glympse ObjC++ library.
#endif

#ifndef IGLYMPSELITE_H__GLYMPSE__
    #error GlympseLite header undefined -- Be sure to import "GlympseLite.h" in your project's .pch file.
#endif

/**
 * Singleton class that provides convenience functions for managing the Glympse platform lifespan
 */
@interface GlympseLiteWrapper : NSObject

{
@private
    Glympse::GGlympseLite _glympse;
    
    Glympse::GString _serverAddress;
    Glympse::GString _apiKey;
}

/**
 * @returns Singleton instance of GlympseLiteWrapper class
 */
+ (GlympseLiteWrapper *)instance;


/**
 * Property to access this singleton's instance of the GGlympseLite C++ object.
 */
@property (nonatomic, readonly) Glympse::GGlympseLite glympse;


/**
 * Glympse: platform creation and startup. Optionally requests server for history of expired glympses
 * See GGlympseLite documentation for getTickets() and setRestoreHistory(bool restore) for more information.
 * @param restoreHistory YES to include expired glympses in ticket array.
 */
- (void) startWithHistory:(BOOL)restoreHistory;


/**
 * Glympse: platform shutdown and cleanup
 */
- (void) stop;

@end
