//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "GlympseTicketTableCell.h"

#import "GlympseLiteWrapper.h"

@interface GlympseTicketTableCell()
{
    IBOutlet UITextView *_recipientsCtrl;
    
    IBOutlet UITextField *_watchStatusCtrl;
    IBOutlet UITextField *_durationStatusCtrl;
    IBOutlet UISegmentedControl *_actionsCtrl;
}

@end

@implementation GlympseTicketTableCell

@dynamic glympseTicket;

#pragma mark - Dynamic Property Implementation

- (void)setGlympseTicket:(Glympse::GTicketLite)glympseTicket
{
    _glympseTicket = glympseTicket;
    [self updateGlympseTicketUi];
    [self refreshDurationAndWatchers];
}

- (Glympse::GTicketLite)glympseTicket
{
    return _glympseTicket;
}


#pragma mark - Control Event Handlers


- (IBAction)actionsCtrl_ValueChanged:(id)sender
{
    switch (_actionsCtrl.selectedSegmentIndex)
    {
        case 0:
            [_delegate expireGlympse:_glympseTicket];
            break;
        case 1:
            [_delegate plusFifteenMins:_glympseTicket];
            break;
        case 2:
            [_delegate modifyGlympse:_glympseTicket];
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
    if (_glympseTicket == NULL)
    {
        return;
    }
    
    if (0 != (code & Glympse::LC::EVENT_INVITE_SENT))
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
            // Manually update UI one last time to show Expired status
            [self updateGlympseTicketUi];
            [self refreshDurationAndWatchers];
            
        }
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_REMOVED))
    {
        // If the removed ticket is our Demo's ticket: stop refresh timer and update UI one last time.
        if (_glympseTicket != NULL && _glympseTicket->equals(param1))
        {
            // Release ticket
            _glympseTicket = NULL;
            
            // Manually update UI one last time to remove
            [self updateGlympseTicketUi];
            [self refreshDurationAndWatchers];
        }
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
        [GLYGlympseLite subscribe:self onPlatform:[GlympseLiteWrapper instance].glympse];
    }
    else
    {
        [GLYGlympseLite unsubscribe:self onPlatform:[GlympseLiteWrapper instance].glympse];
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
        _actionsCtrl.hidden = NO;
        
        _watchStatusCtrl.hidden = NO;
        _durationStatusCtrl.hidden = NO;
        
        _watchStatusCtrl.backgroundColor = [UIColor whiteColor];
        _durationStatusCtrl.backgroundColor = [UIColor whiteColor];
        _recipientsCtrl.backgroundColor = [UIColor whiteColor];
//        self.contentView.backgroundColor = [UIColor whiteColor];
    }
    else
    {
        _actionsCtrl.hidden = YES;
        
        // Only hide "watched" and "duration" controls if we don't have a ticket object
        //  otherwise they will display the "expired" state and total, past "watched" count
        if (_glympseTicket == NULL)
        {
            _watchStatusCtrl.hidden = YES;
            _durationStatusCtrl.hidden = YES;
        }
        else
        {
            _watchStatusCtrl.backgroundColor = [UIColor lightGrayColor];
            _durationStatusCtrl.backgroundColor = [UIColor lightGrayColor];
            _recipientsCtrl.backgroundColor = [UIColor lightGrayColor];
        }
//        self.contentView.backgroundColor = [UIColor grayColor];
    }
    
    _recipientsCtrl.text = [self getRecipientsAsString];
}

- (void)refreshDurationAndWatchers
{
    _watchStatusCtrl.text = [self getNumberWatchingAsString];
    _durationStatusCtrl.text = [self getTimeRemainingAsString];
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
            return [self formatDuration:llabs(durationMs) withPrefix:@"Expired " withPostfix:@" ago"];
        }
        else
        {
            return [self formatDuration:durationMs withPrefix:@"" withPostfix:@" remaining"];
        }
    }
    else
    {
        return @"--";
    }
}

#pragma mark -- Misc. helper methods

- (NSString *)formatDuration:(Glympse::int64)durationMs withPrefix:(NSString *)prefix withPostfix:(NSString *)postfix
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
        return [NSString stringWithFormat:@"%@%d days%@", prefix, days, postfix];
    }
    // "1 day, 2:33"
    else if (days > 0)
    {
        return [NSString stringWithFormat:@"%@%d day(s), %d hr(s), %d min%@", prefix, days, hours, minutes, postfix];
    }
    // "2:33:44"
    else if (hours > 0)
    {
        return [NSString stringWithFormat:@"%@%d hr(s), %d min, %d sec%@", prefix, hours, minutes, seconds, postfix];
    }
    // "33:44"
    return [NSString stringWithFormat:@"%@%d min, %d sec%@", prefix, minutes, seconds, postfix];
}

#pragma mark - View Lifecycle

- (void)prepareForReuse
{
    /**
     * Do not stop listening to (Observing) Glympse platform handler here... For performance reasons, we simply 
     *  ignore Glympse Platform events (Notifications) if cell has no _glympseTicket.
     */
}

- (void)dealloc
{
    [self enableObservingGlympsePlatformEvents:NO];
    
    _glympseTicket = NULL;
    
    [_recipientsCtrl release];
    [_watchStatusCtrl release];
    [_durationStatusCtrl release];
    [_actionsCtrl release];
    [super dealloc];
}


@end
