//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IINVITELITE_H__GLYMPSE__
#define IINVITELITE_H__GLYMPSE__

namespace Glympse
{
    
/**
 * Provides interface to observe changes on the outgoing invite.
 */
/*O*public**/ struct IInviteLite : public ICommon
{
    /**
     * Gets the type of this recipient.
     */
    public: virtual int32 getType() = 0;
    
    /**
     * Gets the display name of this recipient.
     */
    public: virtual GString getName() = 0;
    
    /**
     * Gets the email address or phone number of this recipient.
     */
    public: virtual GString getAddress() = 0;
    
    /**
     * Gets the URL that was sent to this recipient.
     */
    public: virtual GString getUrl() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of when this invite was created.
     */
    public: virtual int64 getCreatedTime() = 0;
    
    /**
     * Gets the epoch time (milliseconds since 1/1/1970) of when this invite was last viewed.
     */
    public: virtual int64 getLastViewTime() = 0;
    
    /**
     * Gets total amount of unique Glympse viewers.
     *
     * The following objects could act as unique Glympse viewers:
     * - Browser instance (or set of browsers sharing the same cookies space);
     * - Glympse application (or any other application build on top of Glympse Client API).
     * This means that page refresh or even browser restart does not lead to increasing views count.
     *
     * This count is forever increasing. It does not represent current amount of viewers.
     * It is possible that nobody views Glympse at the moment, but the value returned by this method
     * remains high. getLastViewTime() should be used to get adequate information on how long ago
     * the invite was viewed last time.
     */
    public: virtual int32 getViewers() = 0;
};
    
/*C*/typedef O< IInviteLite > GInviteLite;/**/
    
}

#endif // !IINVITELITE_H__GLYMPSE__
