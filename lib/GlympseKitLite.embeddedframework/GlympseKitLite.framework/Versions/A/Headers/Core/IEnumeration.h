//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IENUMERATION_H__GLYMPSE__
#define IENUMERATION_H__GLYMPSE__

namespace Glympse 
{
    
/**
 * An object that implements the IEnumeration interface generates a series of elements, one at a time.
 * Successive calls to the nextElement() method return successive elements of the series.
 * Provides immutable access to the collection of objects without exposing details about underlying data structure. 
 */
template< class T > struct IEnumeration : public ICommon
{
    public: virtual bool hasMoreElements() = 0;
        
    public: virtual T nextElement() = 0;
};
    
/** Smart pointer wrapper over IArray. */    
template< class T > class GEnumeration
{       
    private: GEnumeration();
    public: typedef O< IEnumeration< T > > ptr;
};   
    
}

#endif // !IENUMERATION_H__GLYMPSE__
