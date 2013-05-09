//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------


#import <Foundation/Foundation.h>

@protocol GlympseTicketActionsDelegate

- (void)expireGlympse:(Glympse::GTicketLite)glympseTicket;
- (void)plusFifteenMins:(Glympse::GTicketLite)glympseTicket;
- (void)modifyGlympse:(Glympse::GTicketLite)glympseTicket;

@end
