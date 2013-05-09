//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "GlympseLiteWrapper.h"

@interface GlympseLiteWrapper () <GLYListenerLite>

@end


@implementation GlympseLiteWrapper

@dynamic glympse;

#pragma mark - Public Methods

- (void) startWithHistory:(BOOL)restoreHistory
{
    if (_glympse == NULL)
    {
        // Create GlympseLite platform and pass in server URL and API key.
        _glympse = Glympse::LiteFactory::createGlympse(_serverAddress, _apiKey);
        
        [GLYGlympseLite subscribe:self onPlatform:_glympse];
        
        _glympse->setRestoreHistory(true);
        
        // Start the Glympse platform.
        _glympse->start();
    }
}

- (void) stop
{
    if (_glympse != NULL)
    {
        [GLYGlympseLite unsubscribe:self onPlatform:_glympse];
        
        // Shutdown the Glympse platform.
        _glympse->stop();
        _glympse = NULL;
    }
}

- (void)createGlympse
{
    Glympse::GTicketLite ticketLite =
    Glympse::LiteFactory::createTicket(0, Glympse::CoreFactory::createString("Hello, world!"), NULL);
    
    [GlympseLiteWrapper instance].glympse->sendTicket(ticketLite, 0);
    
}

/**
 * Respond to GlympseLite platform events
 */
- (void)glympseEvent:(const Glympse::GGlympseLite &)glympse
                code:(int)code
              param1:(const Glympse::GCommon &)param1
              param2:(const Glympse::GCommon &)param2
{
    
    if (0 != (code & Glympse::LC::EVENT_SYNCED))
    {
        // A user will typically want to set their own nickname & avatar, but we set them here for Demo purposes
        if (_glympse->getNickname() == NULL)
        {
            _glympse->setNickname(Glympse::CoreFactory::createString("Lite-Demo user"));
        }
        if (_glympse->getAvatar() == NULL)
        {
            //Largest avatar size is 320x320 @ 72 PPI -- anything larger is resized prior to upload.
            NSString *avatarUri = [[[NSBundle mainBundle] URLForResource:@"icon@2x"
                                                           withExtension:@"png"] absoluteString];
            
            _glympse->setAvatar(Glympse::CoreFactory::createString([avatarUri UTF8String]), 0);
        }
    }
    else if (0 != (code & Glympse::LC::EVENT_AUTH_ERROR))
    {
        Glympse::GLong code = param1;
        switch (code->longValue())
        {
            case Glympse::LC::AUTH_ERROR_API_KEY:
            {
                NSLog(@"UNABLE TO RUN DEMO: You must pass the Glympse platform a valid API key.");
                assert(false);
                break;
            }
            case Glympse::LC::AUTH_ERROR_CREDENTIALS:
            {
                NSLog(@"UNABLE TO RUN DEMO: Invalid credentials sent to Glympse server. \
                      Try deleting and reinstalling the app.");
                assert(false);
                break;
            }
            default:
                break;
        }
    }
}

#pragma mark - Dynamic Property Implementation

- (Glympse::GGlympseLite)glympse
{
    return (Glympse::GGlympseLite) _glympse;
}

#pragma mark - Initialization

- (void)singletonInit
{
    _apiKey = Glympse::CoreFactory::createString("<< Your API key >>");
    _serverAddress = Glympse::CoreFactory::createString("sandbox.glympse.com");
    
    if (_apiKey->equals("<< Your API key >>"))
    {
        NSLog(@"UNABLE TO RUN DEMO: You must pass the Glympse platform a valid API key.");
        assert(false);
    }
}

#pragma mark - Singleton methods -- unrelated to Glympse platform

static GlympseLiteWrapper* s_globalWrapperInstance = nil;
+ (id)instance
{                                                                      
    static dispatch_once_t dispatchOncePredicate = 0;                  
    dispatch_once(&dispatchOncePredicate, ^{                           
        s_globalWrapperInstance = [[super allocWithZone:NULL] init];          
        [s_globalWrapperInstance singletonInit];                              
    });                                                                
    return s_globalWrapperInstance;                                           
}                                                                      
+ (id)allocWithZone:(NSZone*)zone                                      
{                                                                      
    return [[self instance] retain];
}

- (id)copyWithZone:(NSZone *)zone
{
    return self;
}

- (id)retain
{
    return self;
}

- (unsigned)retainCount
{
    return UINT_MAX;  //denotes an object that cannot be released
}

- (oneway void)release
{
    //do nothing
}

- (id)autorelease
{
    return self;
}

- (void)dealloc
{
    [super dealloc];
}


@end
