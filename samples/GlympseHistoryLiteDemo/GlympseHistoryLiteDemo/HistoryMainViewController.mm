//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "HistoryMainViewController.h"

#import "GlympseTicketTableCell.h"
#import "GlympseLiteWrapper.h"

@implementation HistoryMainViewController

#pragma mark - Object Lifecycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        _wrappedTickets = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)dealloc
{
    [self enableObservingGlympsePlatformEvents:NO];
    
    if (self.refreshTimer != nil)
    {
        [self.refreshTimer invalidate];
        self.refreshTimer = nil;
    }
    
    [_sendGlympseBtn release];
    [_glympseTableView release];
    [super dealloc];
}

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self updateMainGlympseUi];
    
    [self enableObservingGlympsePlatformEvents:YES];
    
}


#pragma mark - View/Control Event Handlers

- (IBAction)sendGlympseBtn_TouchUpInside:(id)sender
{
    [self sendGlympse];
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
        // Synced means the list of active tickets, and potentially history, is now available.
        [self rebuildGlympseTable];
        
        [self updateMainGlympseUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_CREATED))
    {
        // If a ticket is added, rebuild the table to use Glympse platform's internal re-ordering of tickets
        [self rebuildGlympseTable];
        
        [self updateMainGlympseUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_EXPIRED))
    {
        // If a ticket is expired, rebuild the table to use Glympse platform's internal re-ordering of tickets
        [self rebuildGlympseTable];
        
        [self updateMainGlympseUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_TICKET_REMOVED))
    {
        Glympse::GTicketLite glympseTicket = (Glympse::GTicketLite)param1;
        
        [self removeTicketFromTable:glympseTicket];
        
        [self updateMainGlympseUi];
    }
    else if (0 != (code & Glympse::LC::EVENT_WIZARD_CANCELLED))
    {
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
            [self rebuildGlympseTable];
            
            [self updateMainGlympseUi];
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
    self.sendGlympseBtn.enabled = NO;
    
    Glympse::GTicketLite glympseTicket =
        Glympse::LiteFactory::createTicket(0, Glympse::CoreFactory::createString("Hello, from History Demo!"), NULL);

    bool succeeded = [GlympseLiteWrapper instance].glympse->sendTicket(glympseTicket, 0);
    if (!succeeded)
    {
        self.sendGlympseBtn.titleLabel.text = @"Ticket send failed.";
        self.sendGlympseBtn.enabled = YES;
    }
}

#pragma mark -- Active Glympse actions

- (void)expireGlympse:(Glympse::GTicketLite)glympseTicket
{
    if ([self isActiveTicket:glympseTicket])
    {
        glympseTicket->expire();
    }
}
- (void)plusFifteenMins:(Glympse::GTicketLite)glympseTicket
{
    if ([self isActiveTicket:glympseTicket])
    {
        glympseTicket->add15Minutes();
    }
}
- (void)modifyGlympse:(Glympse::GTicketLite)glympseTicket
{
    if ([self isActiveTicket:glympseTicket])
    {
        glympseTicket->modify(0);
    }
}


#pragma mark - GlympseLite: View Helper Methods

- (BOOL)isActiveTicket:(Glympse::GTicketLite)glympseTicket
{
    // Check for valid ticket object AND whether it has expired
    return glympseTicket != NULL && glympseTicket->getExpireTime() > [GlympseLiteWrapper instance].glympse->getTime();
}

#pragma mark -- Update UI in response to platform events

- (void)updateMainGlympseUi
{
    self.sendGlympseBtn.enabled = [GlympseLiteWrapper instance].glympse->isSynced();
    
    // Launch a UI refresh timer: only if one isn't already started, and only if we have a valid ticket.
    if (self.refreshTimer == nil && _wrappedTickets.count > 0)
    {
        self.refreshTimer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                             target:self
                                                           selector:@selector(refreshAllDurationsAndWatchers)
                                                           userInfo:nil
                                                            repeats:YES];
    }
    // else: stop timer if it exists and we have NO tickets
    else if(self.refreshTimer != nil && _wrappedTickets.count == 0)
    {
        [self.refreshTimer invalidate];
        self.refreshTimer = nil;
    }
}


- (void)refreshAllDurationsAndWatchers
{
    [self.glympseTableView reloadData];
}


- (void)rebuildGlympseTable
{
    [_wrappedTickets removeAllObjects];
    
    Glympse::GArray<Glympse::GTicketLite>::ptr tickets = [GlympseLiteWrapper instance].glympse->getTickets();
    
    for (int i = 0; i < tickets->length(); i++)
    {
        Glympse::GTicketLite glympseTicket = tickets->at(i);
        id<GCommonWrapper> wrappedTicket = [GLYGlympseLite wrapGCommon:glympseTicket];
        [_wrappedTickets addObject:wrappedTicket];
    }
    [self.glympseTableView reloadData];
}

- (void)removeTicketFromTable:(Glympse::GTicketLite)glympseTicket
{
    for (int i = 0; i < _wrappedTickets.count; i++)
    {
        if ([_wrappedTickets[i] unwrap] == glympseTicket)
        {
            [_wrappedTickets removeObjectAtIndex:i];
            [self.glympseTableView reloadData];
            break;
        }
    }
}

#pragma mark -- UITableViewDataSource protocol impl.

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return _wrappedTickets.count == 0 ? 1 : _wrappedTickets.count;
}

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row >= _wrappedTickets.count)
    {
        if (_wrappedTickets.count == 0)
        {
            UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"NoTicketsCell"];   
            if (cell == nil)
            {
                cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"NoTicketsCell"] autorelease];
            }
            if ([GlympseLiteWrapper instance].glympse->isSynced())
            {
                cell.textLabel.text = @"No History - Tap Send!";
            }
            else
            {
                cell.textLabel.text = @"Syncing with Glympse Server...";
            }
            
            return cell;
        }
        return nil;
    }
    
    GlympseTicketTableCell *cell = [tableView dequeueReusableCellWithIdentifier:@"TicketCell"];
    if (cell == nil)
    {
        NSArray * nibViews = [[NSBundle mainBundle] loadNibNamed:@"GlympseTicketTableCell" owner:self options:nil];
        for (id currentObject in nibViews)
        {
            if ([currentObject isKindOfClass:[GlympseTicketTableCell class]])
            {
                cell = (GlympseTicketTableCell *)currentObject;
                cell.delegate = self;
                break;
            }
        }
    }
    cell.glympseTicket = [_wrappedTickets[indexPath.row] unwrap];
    return cell;
}

#pragma mark - UITableViewDelegate Implementation
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row < _wrappedTickets.count)
    {
        if ([self isActiveTicket:[_wrappedTickets[indexPath.row] unwrap]])
        {
            return 170.0f;
        }
        else
        {
            return 135.0f;
        }
    }
    else
    {
        return 60.0f;
    }
}
@end











