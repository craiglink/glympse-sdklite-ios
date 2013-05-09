//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "CreateMainViewController.h"

#import "GlympseLiteWrapper.h"

@interface CreateMainViewController () <GLYListenerLite>

@end


@implementation CreateMainViewController

#pragma mark - Object Lifecycle

- (void)dealloc
{
    [self enableObservingGlympsePlatformEvents:NO];
    
    [_btnCreateGlympse release];
    [_tvGlympseUrl release];
    [super dealloc];
}

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self enableObservingGlympsePlatformEvents:YES];
    
}


#pragma mark - View Event Handlers

- (IBAction)btnCreateGlympse_TouchUpInside:(id)sender
{
    [self createGlympse];
}

#pragma mark - View Helper Methods

- (void)showGlympseUrl:(NSString *)url
{
    self.tvGlympseUrl.text = url;
}

#pragma mark - Glympse Helper Methods

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

- (void)createGlympse
{
    [self showGlympseUrl:@"Creating Glympse..."];
    
    Glympse::GTicketLite ticketLite =
        Glympse::LiteFactory::createTicket(0, Glympse::CoreFactory::createString("Hello, world!"), NULL);
    
    bool succeeded = ticketLite->addInvite(Glympse::LC::INVITE_TYPE_LINK, NULL, NULL);
    if (!succeeded)
    {
        [self showGlympseUrl:@"Invite creation failed."];
    }
    
    int wizardFlags = (Glympse::LC::SEND_WIZARD_MESSAGE_HIDDEN |
                       Glympse::LC::SEND_WIZARD_DESTINATION_HIDDEN |
                       Glympse::LC::SEND_WIZARD_INVITES_READONLY);
    
    succeeded = [GlympseLiteWrapper instance].glympse->sendTicket(ticketLite, wizardFlags);
    if (!succeeded)
    {
        [self showGlympseUrl:@"Ticket send failed."];
    }
}

- (void)glympseEvent:(const Glympse::GGlympseLite &)glympse
                code:(int)code
              param1:(const Glympse::GCommon &)param1
              param2:(const Glympse::GCommon &)param2
{
    if (0 != (code & Glympse::LC::EVENT_INVITE_URL_CREATED))
    {
        Glympse::GInviteLite invite = (Glympse::GInviteLite)param2;
        NSString *inviteUrl = [NSString stringWithUTF8String:invite->getUrl()->toCharArray()];
        [self showGlympseUrl:inviteUrl];
    }
}

@end











