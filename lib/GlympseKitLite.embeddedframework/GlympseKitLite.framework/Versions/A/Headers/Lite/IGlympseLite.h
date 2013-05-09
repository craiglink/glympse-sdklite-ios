//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IGLYMPSELITE_H__GLYMPSE__
#define IGLYMPSELITE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The main Glympse API interface. 
 *
 * In the Glympse system, a "Glympse" is referred to as a "ticket".
 * The terms Ticket and Glympse should be considered equivalent in this documentation.
 */
/*O*public**/ struct IGlympseLite : public IListenerLite
{    
    /**
     * @name Lifecycle Section
     *
     * Tools to manipulate Glympse API lifecycle.
     */
    
    /**
     * This starts the entire Glympse system.
     * This includes starting the Glympse service (to support background location sharing), starting the location manager,
     * loading persisted settings, and initiating communication with the Glympse server.
     *
     * Note that certain properties can only be adjusted before platform is started.
     * The following methods can only be called before platform is started:
     * - setRestoreHistory()
     *
     * However, the majority of IGlympseLite methods should not be invoked before startup.
     * It is impossible to send tickets and get access to underlying collections (history, etc.).
     *
     * It is recommended you call the addListener() method before calling the start()
     * method in order to capture startup events.
     *
     * The counterpart to this method is the stop() method, which stops the Glympse system.
     */
    public: virtual void start() = 0;
    
    /**
     * This stops the entire Glympse system.
     * This includes stopping the Glympse service, stopping the location manager,
     * and closing down communication with the Glympse server.
     */
    public: virtual void stop() = 0;
    
    /**
     * Use this method to notify Glympse API, when the application is going to background or returns to foreground.
     *
     * @param active Should be true, if application goes to foreground.
     */
    public: virtual void setActive(bool active) = 0;
    
    /**
     * Determines whether history has already been synced with server.
     * It might be useful to differenciate "empty history" case from "not yet synched" case.
     * Platform sends LC::EVENT_SYNCED event, when this list is synced with server.
     *
     * @return Returns true, if local list has already been synced with server.
     */
    public: virtual bool isSynced() = 0;
    
    /**
     * @name User Profile and Configuration
     *
     * Modify user profile and library behavior.
     */
    
    /**
     * Modifies user nickname.
     *
     * @param nickname New user nickname.
     */
    public: virtual void setNickname(const GString& nickname) = 0;
    
    /**
     * Modifies user avatar. 
     *
     * GDrawable object can be constructed using LiteFactory#createDrawable();
     *
     * @param avatar New user avatar.
     */
    public: virtual void setAvatar(const GDrawable& avatar) = 0;
    
    /**
     * Modifies user avatar.
     *
     * The following URI schemas are supported:
     * - "file" Image will be loaded from local file. Full path should be specified in this case.
     *   Library will use it without any modifications.
     * - "http"/"https" In this case image will be downloaded from the web.
     *
     * @param uri Path to avatar image.
     * @param rotation The degrees of clockwise rotation that should be applied to the image.
     * This argument is taken into account only when image is loaded from a file.
     */
    public: virtual void setAvatar(const GString& uri, int32 rotation) = 0;
    
    /**
     * Gets user nickname.
     */ 
    public: virtual GString getNickname() = 0;
    
    /**
     * Gets user avatar.
     */
    public: virtual GDrawable getAvatar() = 0;
    
    /**
     * Enables or disables intoduction screen. Introduction screen shows some information 
     * about Glympse functionality to user. The screen is presented to user just once (if enabled)
     * right before Send Wizard.
     *
     * Introduction screen is enabled by default.
     */ 
    public: virtual void enableIntroScreen(bool enable) = 0;
    
    /**
     * Checks whether introduction screen is enabled. 
     */
    public: virtual bool isIntroScreenEnabled() = 0;
    
    /**
     * Enables speed sharing. This feature is enabled by default.
     * In practice, this option does not affect anything except speed property of outgoing locations.
     */
    public: virtual void allowSpeedSharing(bool allow) = 0;
    
    /**
     * Checks whether speed sharing is enabled.
     */
    public: virtual bool isSharingSpeed() = 0;
    
    /**
     * Specifies, whether expired tickets previously sent by the user should be
     * retrieved from server, when platform is started.
     *
     * Client API does not restores history by default. It only retrieves active tickets,
     * when platform is restarted.
     *
     * The method must be invoked before platform is started.
     * Property is not persisted across sessions.
     *
     * @param Returns current history operation mode.
     */
    public: virtual void setRestoreHistory(bool restore) = 0;
    
    /**
     * @return Indicates, whether history is restored from server, when platform is started.
     */
    public: virtual bool isHistoryRestored() = 0;
    
    /**
     * @name Tickets Section
     *
     * Exposes controls for manipulating outgoing (sent) tickets.
     */
    
    /**
     * This method presents modal Send a Glympse wizard that walks user through 
     * the entire configuration process. 
     *
     * @param ticketLite Prepopulated ticket object.
     * @param flags A combination of send wizard flags. See LC::SEND_WIZARD_* for details. 
     * @return Returns true, if send wizard is presented successfully.
     */
    public: virtual bool sendTicket(const GTicketLite& ticketLite, int32 flags) = 0;
    
    /**
     * Provides access to the list of previously sent tickets. Both active and expired 
     * tickets can be found on the list. Active tickets always go first. 
     */ 
    public: virtual GArray<GTicketLite>::ptr getTickets() = 0;
    
    /**
     * @name Events section
     *
     * Provides tools for registering and unregistering event listeners.
     */
    
    /**
     * Registeres event listener. It is not allowed to register
     * the same listener multiple times.
     */
    public: virtual bool addListener(const GListenerLite& listener) = 0;
    
    /**
     * Unsubscribes listener from all events.
     */
    public: virtual bool removeListener(const GListenerLite& listener) = 0;
    
    /**
     * Unsubscribes all listeners.
     */
    public: virtual bool removeAllListeners() = 0;
    
    /**
     * Gets the list of all listeners. 
     */
    public: virtual GArray<GListenerLite>::ptr getListeners() = 0;
    
    /**
     * @name Tools
     *
     * Miscellaneous helpers and tools. 
     */
    
    /**
     * Presents Glympse about page. 
     */
    public: virtual void showAbout() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of the corrected system time ("Glympse time").
     * All timestamps used throughout the Glympse system are server timestamps in UTC. These include ticket start and end times.
     * The Glympse client API periodically synchronizes itself to the Glympse server time in order to maintain an accurate
     * system time that is independent to the system time maintained by the operating system, which may be incorrect.
     * Any time you need an accurate system time to use with other Glympse times (such as when computing time remaining on a ticket),
     * you should call this method to obtain the current system time in UTC.
     *
     * @return The current system time, corrected to be in sync with the Glympse server time.
     */
    public: virtual int64 getTime() = 0;
    
    /**
     * Gets version of the library in the format: "{MAJOR}.{MINOR}.{BUGFIX}".
     */
    public: virtual GString getApiVersion() = 0;
};
    
/*C*/typedef O< IGlympseLite > GGlympseLite;/**/
    
}

#endif // !IGLYMPSELITE_H__GLYMPSE__
