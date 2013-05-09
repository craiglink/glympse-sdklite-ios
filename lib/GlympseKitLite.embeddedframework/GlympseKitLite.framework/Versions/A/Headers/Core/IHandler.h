//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IHANDLER_H__GLYMPSE__
#define IHANDLER_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * The IHandler interface provides the foundation for inter-thread communications
 * in non thread safe run loop based environment.
 */
/*O*public**/ struct IHandler : public ICommon
{
    public: virtual void post(const GRunnable& task) = 0;
    
    public: virtual void postDelayed(const GRunnable& task, int64 delayMillis) = 0;
    
    public: virtual void cancel(const GRunnable& task) = 0;
    
    public: virtual bool isMainThread() = 0;
};
    
/*C*/typedef O< IHandler > GHandler;/**/
    
}

#endif // !IHANDLER_H__GLYMPSE__
