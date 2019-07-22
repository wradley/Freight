#import "AppDelegate.h"
#import "GameViewController.h"
#import <AppKit/AppKit.h>

@interface AppDelegate ()

@end

@implementation AppDelegate {
    NSWindowController *_wc;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    NSRect frame = NSMakeRect(100, 100, 200, 200);
    NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
                                styleMask:NSWindowStyleMaskResizable|NSWindowStyleMaskClosable|NSWindowStyleMaskTitled
                                  backing:NSBackingStoreBuffered
                                    defer:NO];
    [window setBackgroundColor:[NSColor blueColor]];
    [window makeKeyAndOrderFront:NSApp];
    
    _wc = [[NSWindowController alloc] initWithWindow:window];
    [_wc showWindow:self];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

@end
