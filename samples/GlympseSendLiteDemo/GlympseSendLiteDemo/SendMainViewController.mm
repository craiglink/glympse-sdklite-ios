//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "SendMainViewController.h"
#import "GlympseLiteWrapper.h"

@interface SendMainViewController () <GLYListenerLite>
{
    Glympse::GTicketLite _glympseTicket;
}
@end

@implementation SendMainViewController

#pragma mark - Object Lifecycle

- (void)dealloc
{
    [self enableObservingGlympsePlatformEvents:NO];
    
    if (self.refreshTimer != nil)
    {
        [self.refreshTimer invalidate];
        self.refreshTimer = nil;
    }
    
    [_sendGlympseBtn release];
    [_recipientsCtrl release];
    [_durationStatusCtrl release];
    [_watchedStatusCtrl release];
    [_actionsCtrl release];
    [super dealloc];
}

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self updateGlympseTicketUi];
    
    [self enableObservingGlympsePlatformEvents:YES];
    
}


#pragma mark - View/Control Event Handlers

- (IBAction)sendGlympseBtn_TouchUpInside:(id)sender
{
    [self sendGlympse];
}

- (IBAction)actionsCtrl_ValueChanged:(id)sender
{
    switch (_actionsCtrl.selectedSegmentIndex)
    {
        case 0:
            [self expireGlympse];
            break;
        case 1:
            [self plusFifteenMins];
            break;
        case 2:
            [self modifyGlympse];
            break;
        default:
            break;
    }
}

#pragma mark - GlympseLite: Events (aka Notifications)

/**
 * Respond to GlympseLite platform events here
 * Glympse sends this message on the same thread you started it, so its safe to update the UI directly from here
 */
- (void)glympseEvent:(const Glympse::GGlympseLite &)glympse
                code:(int)code
              param1:(const Glympse::GCommon &)param1
              param2:(const Glympse::GCommon &)param2
{
    if (0 != (code & Glympse::LC::EVENT_SYNCED))
    {
        // Look for an active Glympse ticket: if there is one, grab it
        [self checkForGlympseTicket];
        
        [self updateGlympseTicketUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_CREATED))
    {
        if (![self hasActiveTicket])
        {
            _glympseTicket = (Glympse::GTicketLite)param1;
        }

        [self updateGlympseTicketUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_INVITE_SENT))
    {
        // Update UI for each invite sent: this will catch newly added invites from a "Modify"
        [self updateGlympseTicketUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_EXPIRED))
    {
        // If the expired ticket is our Demo's ticket: stop refresh timer and update UI one last time.
        //  Note: This is necessary because a Glympse account could have multiple active tickets that expired!
        //        However, for this Demo, we are trying to illustrate how to interact with just a single ticket.
        if (_glympseTicket != NULL && _glympseTicket->equals(param1))
        {
            // Timer was created on the MainThread, so its safe to invalidate it here
            [self.refreshTimer invalidate];
            
            // Manually update UI one last time to show Expired status
            [self updateGlympseTicketUi];
            [self refreshDurationAndWatchers];
            
            // Release timer
            self.refreshTimer = nil;
        }
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_REMOVED))
    {
        // If the removed ticket is our Demo's ticket: stop refresh timer and update UI one last time.
        if (_glympseTicket != NULL && _glympseTicket->equals(param1))
        {
            // Timer was created on the MainThread, so its safe to invalidate it here
            [self.refreshTimer invalidate];
            
            // Release ticket
            _glympseTicket = NULL;
            
            // Manually update UI one last time to remove
            [self updateGlympseTicketUi];
            [self refreshDurationAndWatchers];
            
            // Release timer
            self.refreshTimer = nil;
        }
    }
    else if (0 != (code & Glympse::LC::EVENT_WIZARD_CANCELLED))
    {
        // If we're NOT modifying an active ticket...
        if (![self hasActiveTicket])
        {
            _glympseTicket = NULL; //ditched cancelled new ticket
        }
        self.sendGlympseBtn.enabled = YES;
    }
}


#pragma mark - GlympseLite: Platform Methods
/**
 * Glympse: toggle notification observing
 */
- (void)enableObservingGlympsePlatformEvents:(BOOL)doObserve
{
    if (doObserve)
    {
        // Check if platform already Synced up: we started platform before we started listening to its events
        if ([GlympseLiteWrapper instance].glympse->isSynced())
        {
            [self checkForGlympseTicket];
            
            [self updateGlympseTicketUi];
        }
        
        [GLYGlympseLite subscribe:self onPlatform:[GlympseLiteWrapper instance].glympse];
    }
    else
    {
        [GLYGlympseLite unsubscribe:self onPlatform:[GlympseLiteWrapper instance].glympse];
    }
}

/**
 * Glympse: present "Send Wizard" ViewController
 */
- (void)sendGlympse
{
    if ([self hasActiveTicket])
    {
        self.sendGlympseBtn.enabled = NO;
        return;
    }
    
    _glympseTicket =
        Glympse::LiteFactory::createTicket(0, Glympse::CoreFactory::createString("Hello, from Send Demo!"), NULL);
    
    bool succeeded = [GlympseLiteWrapper instance].glympse->sendTicket(_glympseTicket, 0);
    if (!succeeded)
    {
        _glympseTicket = NULL;
        self.sendGlympseBtn.enabled = YES;
        self.recipientsCtrl.text = @"Ticket send failed.";
    }
}

#pragma mark -- Active Glympse actions

- (void)expireGlympse
{
    if ([self hasActiveTicket])
    {
        _glympseTicket->expire();
    }
}
- (void)plusFifteenMins
{
    if ([self hasActiveTicket])
    {
        _glympseTicket->add15Minutes();
    }
}
- (void)modifyGlympse
{
    if ([self hasActiveTicket])
    {
        _glympseTicket->modify(0);
    }
}


#pragma mark - GlympseLite: View Helper Methods

#pragma mark -- Update UI in response to platform events
/**
 * Glympse: update ui to reflect current glympse ticket status ...
 *          + start a UI update timer if we have an active ticket
 */
- (void)updateGlympseTicketUi
{
    if ([self hasActiveTicket])
    {
        self.sendGlympseBtn.enabled = NO;
        self.actionsCtrl.hidden = NO;
        
        self.watchedStatusCtrl.hidden = NO;
        self.durationStatusCtrl.hidden = NO;

        // Launch a UI refresh timer: only if one isn't already started, and only if we have a valid active ticket.
        if (self.refreshTimer == nil)
        {
            self.refreshTimer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                                 target:self
                                                               selector:@selector(refreshDurationAndWatchers)
                                                               userInfo:nil
                                                                repeats:YES];
        }
    }
    else
    {
        self.sendGlympseBtn.enabled = [GlympseLiteWrapper instance].glympse->isSynced();
        self.actionsCtrl.hidden = YES;
        
        // Only hide "watched" and "duration" controls if we don't have a ticket object
        //  otherwise they will display the "expired" state and total, past "watched" count
        if (_glympseTicket == NULL)
        {
            self.watchedStatusCtrl.hidden = YES;
            self.durationStatusCtrl.hidden = YES;
        }
    }
    
    self.recipientsCtrl.text = [self getRecipientsAsString];
}

- (void)refreshDurationAndWatchers
{
    self.watchedStatusCtrl.text = [self getNumberWatchingAsString];
    self.durationStatusCtrl.text = [self getTimeRemainingAsString];
}

- (void)checkForGlympseTicket
{
    // Check for a ticket object if we don't have one yet
    if (_glympseTicket == NULL)
    {
        Glympse::GArray<Glympse::GTicketLite>::ptr tickets = [GlympseLiteWrapper instance].glympse->getTickets();
        
        // Just grab first ticket in array since we intentionally
        //  avoid creating more than one ticket at a time in this demo.
        if (tickets->length() > 0)
        {
            _glympseTicket = tickets->at(0);
        }
    }
}

#pragma mark -- Derive status information from the active Glympse

- (BOOL)hasActiveTicket
{
    // Check for valid ticket object AND whether it has expired
    return _glympseTicket != NULL && _glympseTicket->getExpireTime() > [GlympseLiteWrapper instance].glympse->getTime();
}

- (NSString *)getRecipientsAsString
{
    if (_glympseTicket != NULL)
    {
        NSMutableString *recipients = [[NSMutableString alloc] initWithString:@"Recipient(s): "];
        Glympse::GArray<Glympse::GInviteLite>::ptr invites = _glympseTicket->getInvites();
        for (Glympse::int32 i = 0; i < invites->length(); i++)
        {
            if (i > 0)
            {
                [recipients appendString:@", "];
            }
            
            Glympse::GInviteLite invite = invites->at(i);
            NSString *recipientText = nil;
            if (invite->getType() == Glympse::LC::INVITE_TYPE_LINK)
            {
                recipientText = [NSString stringWithFormat:@"LINK: %@",
                                 [NSString stringWithUTF8String:invite->getUrl()->toCharArray()]];
            }
            else
            {
                if (invite->getName() != NULL)
                {
                    recipientText = [NSString stringWithUTF8String:invite->getName()->toCharArray()];
                }
                else if(invite->getAddress() != NULL)
                {
                    recipientText = [NSString stringWithUTF8String:invite->getAddress()->toCharArray()];
                }
                else
                {
                    recipientText = @"Unnamed Invite";
                }
            }
            
            [recipients appendString:recipientText];
        }
        if (invites->length() < 1)
        {
            [recipients appendString:@"(No Recipients)"];
            
        }
        return recipients;
    }
    else if([GlympseLiteWrapper instance].glympse->isSynced())
    {
        return @"No Active Glympse";
    }
    else
    {
        return @"Syncing with Glympse server...";
    }
}

- (NSString *)getNumberWatchingAsString
{
    if (_glympseTicket != NULL)
    {
        Glympse::int32 count = 0;
		Glympse::int64 currentTimeMs = [GlympseLiteWrapper instance].glympse->getTime();
		Glympse::GArray<Glympse::GInviteLite>::ptr invites = _glympseTicket->getInvites();
        
        if (_glympseTicket->getExpireTime() > currentTimeMs)
        {
            for (Glympse::int32 i = 0; i < invites->length(); i++)
            {
                // If someone viewed it within the last 3 minutes, consider them actively "watching"
                if(currentTimeMs - invites->at(i)->getLastViewTime() < (3L * 60000))
                {
                    count++;
                }
            }
            return [NSString stringWithFormat:@"%d watching", count];
        }
        // else: ticket is expired, count total views.
        else
        {
            for (Glympse::int32 i = 0; i < invites->length(); i++)
            {
                count += invites->at(i)->getViewers();
            }
            return [NSString stringWithFormat:@"%d watched", count];
        }
    }
    else
    {
        return @"--";
    }
}

- (NSString *)getTimeRemainingAsString
{
    if (_glympseTicket != NULL)
    {
        Glympse::int64 currentTimeMs = [GlympseLiteWrapper instance].glympse->getTime();
        Glympse::int64 expireTimeMs = _glympseTicket->getExpireTime();
        Glympse::int64 durationMs = expireTimeMs - currentTimeMs;
        if (durationMs <= 0)
        {
            return @"Expired";
        }
        else
        {
            return [self formatDuration:durationMs withPostfix:@" remaining"];
        }
    }
    else
    {
        return @"--";
    }
}

#pragma mark -- Misc. helper methods

- (NSString *)formatDuration:(Glympse::int64)durationMs withPostfix:(NSString *)postfix
{
    if (durationMs < 0)
    {
        durationMs = 0;
    }
    
    if (postfix == nil)
    {
        postfix = [NSString string];
    }
    
    static const int MS_PER_SECOND = 1000;
    static const int MS_PER_MINUTE = 60000;
    static const int MS_PER_HOUR   = 3600000;
    static const int MS_PER_DAY    = 86400000;

    int days    = (int)(durationMs / MS_PER_DAY   );
    int hours   = (int)(durationMs / MS_PER_HOUR  ) % 24;
    int minutes = (int)(durationMs / MS_PER_MINUTE) % 60;
    int seconds = (int)(durationMs / MS_PER_SECOND) % 60;
    
    // "10 days"
    if (days >= 10)
    {
        return [NSString stringWithFormat:@"%d days%@", days, postfix];
    }
    // "1 day, 2:33"
    else if (days > 0)
    {
        return [NSString stringWithFormat:@"%d day(s), %d hr(s), %d min%@", days, hours, minutes, postfix];
    }
    // "2:33:44"
    else if (hours > 0)
    {
        return [NSString stringWithFormat:@"%d hr(s), %d min, %d sec%@", hours, minutes, seconds, postfix];
    }
    // "33:44"
    return [NSString stringWithFormat:@"%d min, %d sec%@", minutes, seconds, postfix];
}

@end











