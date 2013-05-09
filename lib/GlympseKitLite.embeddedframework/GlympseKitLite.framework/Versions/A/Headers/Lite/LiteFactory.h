//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef LITEFACTORY_H__GLYMPSE__
#define LITEFACTORY_H__GLYMPSE__

namespace Glympse
{
    
/**
 * The LiteFactory class provides factory methods for constructing all API primitives.
 */
class LiteFactory
{
    private: LiteFactory();
    
    /**
     * Creates new Glympse platform object. 
     *
     * It is only allowed to create single instance of the platform per process at the given time. 
     *
     * @param server Base server URL.
     * @param apiKey Partner specific API key.
     */
    public: static GGlympseLite createGlympse(const GString& server, const GString& key);

    /**
     * Creates new ticket object, which is intended to be sent.
     *
     * @param duration Ticket duration in milliseconds.
     * @param message Ticket message (optional).
     * @param destination Ticket destination (optional).
     * @return Returns ticket object, which is ready to be sent.
     */
    public: static GTicketLite createTicket(int32 duration, const GString& message, const GPlace& destination);
    
    /**
     * Creates place object.
     */
    public: static GPlace createPlace(double latitude, double longitude, const GString& name);

    /**
     * Constructs string object.
     */
    public: static GString createString(const char* value);
    
    /**
     * Constructs GDrawable from platform specific image.
     */
    public: static GDrawable createDrawable(void* image);
};

}

#endif // !LITEFACTORY_H__GLYMPSE__
