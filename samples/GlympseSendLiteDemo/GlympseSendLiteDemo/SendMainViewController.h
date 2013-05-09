//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import <UIKit/UIKit.h>


@interface SendMainViewController : UIViewController
{
}

@property (retain, nonatomic) IBOutlet UIButton *sendGlympseBtn;
@property (retain, nonatomic) IBOutlet UITextView *recipientsCtrl;
@property (retain, nonatomic) IBOutlet UITextField *durationStatusCtrl;
@property (retain, nonatomic) IBOutlet UITextField *watchedStatusCtrl;
@property (retain, nonatomic) IBOutlet UISegmentedControl *actionsCtrl;

@property (retain, nonatomic) NSTimer *refreshTimer;

- (IBAction)sendGlympseBtn_TouchUpInside:(id)sender;

- (IBAction)actionsCtrl_ValueChanged:(id)sender;

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
- (void)expireGlympse;
- (void)plusFifteenMins;
- (void)modifyGlympse;

#pragma mark -- Update UI in response to platform events
- (void)updateGlympseTicketUi;
- (void)refreshDurationAndWatchers;
- (void)checkForGlympseTicket;

#pragma mark -- Derive status information from the active Glympse
- (BOOL)hasActiveTicket;
- (NSString *)getRecipientsAsString;
- (NSString *)getNumberWatchingAsString;
- (NSString *)getTimeRemainingAsString;


@end
