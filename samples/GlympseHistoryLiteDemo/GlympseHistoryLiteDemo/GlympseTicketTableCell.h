//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "GlympseTicketActionsDelegate.h"

@interface GlympseTicketTableCell : UITableViewCell<GLYListenerLite>
{
    Glympse::GTicketLite _glympseTicket;
}

@property (assign, nonatomic) Glympse::GTicketLite glympseTicket; 

- (IBAction)actionsCtrl_ValueChanged:(id)sender;

- (void)refreshDurationAndWatchers;

@property (assign, nonatomic) id<GlympseTicketActionsDelegate> delegate;

@end
