//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ITICKETLITE_H__GLYMPSE__
#define ITICKETLITE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Provides interface to configure and observe ticket object. 
 */
/*O*public**/ struct ITicketLite : public virtual ICommon
{
    /**
     * @name Ticket State
     *
     * Provides access to various properties of a ticket.
     */
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) that the ticket was created.
     * This is a Glympse server time. If you need to compare it to the current system time,
     * you should use the IGlympseLite#getTime method to obtain an accurate system time.
     *
     * @return The epoch time (milliseconds since 1/1/1970) that the ticket was created.
     */
    public: virtual int64 getStartTime() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) that the ticket will expire.
     * This is a Glympse server time. If you need to compare it to the current system time,
     * you should use the IGlympseLite#getTime method to obtain an accurate system time.
     *
     * @return The epoch time (milliseconds since 1/1/1970) that the ticket was created.
     */
    public: virtual int64 getExpireTime() = 0;
    
    /**
     * Gets the optional message text associated with this ticket.
     *
     * @return The optional message text associated with this ticket.
     * Will be NULL for no message.
     */
    public: virtual GString getMessage() = 0;
    
    /**
     * Gets the optional destination that is associated with this ticket.
     *
     * @return The optional destination that is associated with this ticket.
     * Will be NULL for no destination.
     */
    public: virtual GPlace getDestination() = 0;
    
    /**
     * @name Modification Section
     *
     * All possible ticket modifications are available in this section.
     */

    /**
     * Adds 15 minutes to ticket remaining time.
     * Maximum duration of a ticket is 4 hours. 
     *
     * It is not possible to modify tickets that are not yet sent. 
     * It is not possible to modify expired tickets.
     */
    public: virtual void add15Minutes() = 0;    
    
    /**
     * Presents fully functional Modify wizard.
     * @param flags A combination of modify wizard flags. See LC::SEND_WIZARD_* for details.
     * @return Returns true, if modify wizard is presented successfully.
     */
    public: virtual bool modify(int32 flags) = 0;
    
    /**
     * Expire ticket right away.
     */
    public: virtual void expire() = 0;
        
    /**
     * @name Invites Section
     *
     * All actions related to ticket invites.
     */
    
    /**
     * Adds invite to the ticket. 
     *
     * See LC::INVITE_TYPE_* for the list of all suported invite types.
     */
    public: virtual bool addInvite(int32 type, const GString& name, const GString& address) = 0;
    
    /**
     * Gets the list of invites. 
     */
    public: virtual GArray<GInviteLite>::ptr getInvites() = 0;
};
    
/*C*/typedef O< ITicketLite > GTicketLite;/**/
    
}

#endif // !ITICKETLITE_H__GLYMPSE__
