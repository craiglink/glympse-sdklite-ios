//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import <UIKit/UIKit.h>

#import "GlympseTicketActionsDelegate.h"

@class GlympseTicketTableCell;

@interface HistoryMainViewController :
    UIViewController<GlympseTicketActionsDelegate, GLYListenerLite, UITableViewDataSource, UITableViewDelegate>
{
    NSMutableArray * _wrappedTickets;
}

@property (retain, nonatomic) IBOutlet UIButton *sendGlympseBtn;
@property (retain, nonatomic) IBOutlet UITableView *glympseTableView;


@property (retain, nonatomic) NSTimer *refreshTimer;

- (IBAction)sendGlympseBtn_TouchUpInside:(id)sender;

#pragma mark - Glympse: Platform Methods

/**
 * Glympse: toggle notification observing
 */
- (void)enableObservingGlympsePlatformEvents:(BOOL)doObserve;

/**
 * Glympse: present "Send Wizard" ViewController
 */
- (void)sendGlympse;

#pragma mark - Glympse: View-Helper Methods

#pragma mark -- Active Glympse actions
- (void)expireGlympse:(Glympse::GTicketLite)glympseTicket;
- (void)plusFifteenMins:(Glympse::GTicketLite)glympseTicket;
- (void)modifyGlympse:(Glympse::GTicketLite)glympseTicket;

#pragma mark -- Derive status information from Glympse ticket
- (BOOL)isActiveTicket:(Glympse::GTicketLite)glympseTicket;

#pragma mark -- Update UI in response to platform events
- (void)rebuildGlympseTable;


@end
