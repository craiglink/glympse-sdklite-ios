//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILISTENERLITE_H__GLYMPSE__
#define ILISTENERLITE_H__GLYMPSE__

namespace Glympse
{
    
/*C*/
struct IGlympseLite;
typedef O< IGlympseLite > GGlympseLite;
/**/
 
/**
 * The listener interface for receiving Glympse Lite events. Any class that implements the IListenerLite interface
 * and registers it by calling the IGlympseLite#addListener method will be called back with various Glympse events
 * as they occur. When a listener is no longer needed, it should be unregistered by calling the
 * IGlympseLite#removeListener method.
 */
/*O*public**/ struct IListenerLite : public virtual ICommon
{
    /**
     * This method is invoked each time, when sink object notifies subscriber on an event.
     *
     * @param glympse Glympse Lite platform instance.
     * @param code Event code. See LC for more details.
     * @param param1 Argument associated with an event. See LC for more details.
     * @param param2 Argument associated with an event. See LC for more details.
     */
    public: virtual void eventsOccurred(const GGlympseLite& glympse, int32 code, const GCommonObj& param1, const GCommonObj& param2) = 0;
};
    
/*C*/typedef O< IListenerLite > GListenerLite;/**/
    
}

#endif // !ILISTENERLITE_H__GLYMPSE__
