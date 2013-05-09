//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

/**
 * Helper interface for wrapping ICommon-based objects into NSObject shells.
 */
@protocol GCommonWrapper<NSObject>

- (Glympse::GCommon)unwrap;

@end

/**
 * GLYGlympseLite exposes set of convenience helpers for subscribing on platform events.
 * Some helpers for wrapping GCommon-based objects into NSObject shells are also provided.
 */
@interface GLYGlympseLite : NSObject

#pragma mark Factory methods

+ (Glympse::GDrawable)createDrawable:(UIImage*)image;

+ (id<GCommonWrapper>)wrapGCommon:(const Glympse::GCommon&)object;

#pragma mark Listeners section

+ (void)subscribe:(id<GLYListenerLite>)listener onPlatform:(const Glympse::GGlympseLite&)platform;

+ (void)unsubscribe:(id<GLYListenerLite>)listener onPlatform:(const Glympse::GGlympseLite&)platform;

@end
