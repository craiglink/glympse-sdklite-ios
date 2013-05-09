//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IRUNNABLE_H__GLYMPSE__
#define IRUNNABLE_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * Represents a command that can be executed.
 */
/*O*public**/ struct IRunnable : public ICommon
{
    /**
     * Starts executing the active part of the class' code.
     */
    public: virtual void run() = 0;
};  
    
/*C*/typedef O< IRunnable > GRunnable;/**/
    
}

#endif // !IRUNNABLE_H__GLYMPSE__
