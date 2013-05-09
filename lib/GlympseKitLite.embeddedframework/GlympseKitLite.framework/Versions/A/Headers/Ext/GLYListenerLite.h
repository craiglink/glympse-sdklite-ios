//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

@protocol GLYListenerLite <NSObject>

- (void)glympseEvent:(const Glympse::GGlympseLite&)glympse
                code:(int)code
              param1:(const Glympse::GCommon&)param1
              param2:(const Glympse::GCommon&)param2;

@end
