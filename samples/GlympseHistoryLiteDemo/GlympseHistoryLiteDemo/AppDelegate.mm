//------------------------------------------------------------------------------
//
//  Copyright (c) 2013 Glympse. All rights reserved.
//
//------------------------------------------------------------------------------

#import "AppDelegate.h"

#import "HistoryMainViewController.h"
#import "GlympseLiteWrapper.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    
    // Initialize & start the Glympse platform object WITH history of expired glympses
    [[GlympseLiteWrapper instance] startWithHistory:YES];
    
    self.window.rootViewController = [[HistoryMainViewController alloc] initWithNibName:@"HistoryMainViewController"
                                                                              bundle:nil];
    
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [GlympseLiteWrapper instance].glympse->setActive(true);
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [GlympseLiteWrapper instance].glympse->setActive(false);
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [[GlympseLiteWrapper instance] stop];
}

- (void)dealloc
{
    [_window release];
    [super dealloc];
}

@end
