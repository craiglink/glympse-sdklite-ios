//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef LC_H__GLYMPSE__
#define LC_H__GLYMPSE__

namespace Glympse
{

/**
 * Constanst and flags are declared by the LC class.
 */
/*O*public**/ class LC
{
    /**
     * @name Invite Types
     *
     * The list of all invite types supported by the library. Invite types
     * are differentiated based on delivery mechanism and the party responsible
     * for the delivery.
     */
    
    /**
     * Indicates that invite will be sent by email.
     * Glympse server handles email delivery on behalf of a client.
     */
    public: static const int32 INVITE_TYPE_EMAIL       = 2;
    
    /**
     * Indicates that invite will be sent by SMS.
     * Client API attempts to send SMS from a device, if it can.
     * It falls back to server side delivery in opposite case.
     */
    public: static const int32 INVITE_TYPE_SMS         = 3;
    
    /**
     * Indicates that invite will be sent by host application.
     * Client API does not perform delivery of such invites. 
     * Host application is responsible for providing delivery mechanism.
     */
    public: static const int32 INVITE_TYPE_LINK        = 6;
    
    /**
     * @name Library Events
     *
     * The list of all event codes supported by the library. 
     * Single point of subscription for all events is provided by IGlympseLite.
     * IListenerLite interface should be implemented by subscribers to be notified on events.
     */
    
    /**
     * This event is sent in case of critical error. 
     * Platform is stopped if such error takes place.
     *
     * @param param1 Error code. The following codes are supported:
     * - LC::AUTH_ERROR_API_KEY       - Specified api key is invalid.
     * - LC::AUTH_ERROR_CREDENTIALS   - Specified username/passward are invalid.
     */
    public: static const int32 EVENT_AUTH_ERROR                 = 0x00000001;

    /**
     * Authentication error is caused by using invalid API key.
     */
    public: static const int32 AUTH_ERROR_API_KEY               = 1;
    
    /**
     * Authentication error is caused by using invalid user credentials (username and password).
     */
    public: static const int32 AUTH_ERROR_CREDENTIALS           = 2;
    
    /**
     * The event is spread, when platform completes synchronization with server
     * This event is only sent once per SDK lifecycle.
     */
    public: static const int32 EVENT_SYNCED                     = 0x00000002;
    
    /**
     * Ticket is successfully added to local history and created on server. 
     * This phase preceeds invites creation and delivery. See LC::EVENT_INVITE_*
     * events for more details. 
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_TICKET_CREATED             = 0x00000004;

    /**
     * One of outgoing tickets has expired.
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_TICKET_EXPIRED             = 0x00000008;
    
    /**
     * One of outgoing tickets was removed from the system. In most cases this means 
     * that ticket ownership was transfered to another application sharing the same 
     * Glympse account.
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_TICKET_REMOVED             = 0x00000010;
    
    /**
     * Invite is successfully sent to recipient. 
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_INVITE_SENT                = 0x00000020;

    /**
     * Invite of LC::INVITE_TYPE_LINK type is created. URL can be accessed using 
     * IInviteLite::getUrl().
     *
     * @param param1 GTicketLite object.
     * @param param2 GInviteLite object.
     */
    public: static const int32 EVENT_INVITE_URL_CREATED         = 0x00000040;
    
    /**
     * Failed to create or deliver invite.
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_INVITE_FAILED              = 0x00000080;
    
    /**
     * This invite is continuously fired, when someone is viewing one of outgoing tickets.
     * In other words it is fired, when invite last view time and/or viewers count is changed. 
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_INVITE_UPDATED             = 0x00000100;    
    
    /**
     * The event is fired, when user cancelles Send or Modify wizard. 
     *
     * @param param1 GTicketLite object.
     */
    public: static const int32 EVENT_WIZARD_CANCELLED           = 0x00000200;
    
    /**
     * @name Send Wizard Properties
     *
     * The flags for adjusting send wizard appearance and behavior are presented in this section.
     * The following components of the wizard are configurable:
     * - invites list;
     * - message picker;
     * - destination picker;
     * - time picker;
     * - profile configurator (nickname, avatar);
     */
    
    /** The list of invites is presented in fully editable mode. */
    public: static const int32 SEND_WIZARD_INVITES_EDITABLE         = 0x00000000;
    /** User is only allowed to view the list on invites. */
    public: static const int32 SEND_WIZARD_INVITES_READONLY         = 0x00000001;
    /** User is only allowed to remove some of prepopulated invites. */
    public: static const int32 SEND_WIZARD_INVITES_DELETEONLY       = 0x00000002;
    
    /** Message picker is presented in fully editable mode. */
    public: static const int32 SEND_WIZARD_MESSAGE_EDITABLE         = 0x00000000;
    /** User is only allowed to view suggested message. */
    public: static const int32 SEND_WIZARD_MESSAGE_READONLY         = 0x00000010;
    /** User is only allowed to delete suggested message. */
    public: static const int32 SEND_WIZARD_MESSAGE_DELETEONLY       = 0x00000020;
    /** 
     * Message picker is not presented at all.
     * This will result in ticket being sent without message. 
     */
    public: static const int32 SEND_WIZARD_MESSAGE_HIDDEN           = 0x00000040;

    /** Destination picker is presented in fully editable mode. */
    public: static const int32 SEND_WIZARD_DESTINATION_EDITABLE     = 0x00000000;
    /** User is only allowed to view suggested destination. */
    public: static const int32 SEND_WIZARD_DESTINATION_READONLY     = 0x00000100;
    /** User is only allowed to delete suggedted destination. */
    public: static const int32 SEND_WIZARD_DESTINATION_DELETEONLY   = 0x00000200;
    /** 
     * Destination picker is not presented at all.
     * This will result in ticket being sent without destination. 
     */
    public: static const int32 SEND_WIZARD_DESTINATION_HIDDEN       = 0x00000400;
    
    /** User is allowed to modify ticket duration. */
    public: static const int32 SEND_WIZARD_TIME_EDITABLE            = 0x00000000;
    /** User is not allowed to modify ticket duration. */
    public: static const int32 SEND_WIZARD_TIME_READONLY            = 0x00001000;
    
    /** User is allowed to modify profile properties (nickname and avatar). */
    public: static const int32 SEND_WIZARD_PROFILE_EDITABLE         = 0x00000000;
    /** User is only allowed to see profile properties but not modify. */
    public: static const int32 SEND_WIZARD_PROFILE_READONLY         = 0x00010000;
};
    
}

#endif // !LC_H__GLYMPSE__
