//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef ILIST_H__GLYMPSE__
#define ILIST_H__GLYMPSE__

namespace Glympse
{
    
/*C*/
template< class T > struct IList;
/// Smart pointer wrapper over IList.
template< class T > class GList
{
    private: GList();
    public: typedef O< IList< T > > ptr;
};
/**/
    
/**
 * Provides immutable access to list container with support for range-based enumeration.
 */
/*C*/template< class T > struct IList : public ICommon/**/
/*J*public interface GList<T> extends GCommon, Iterable<T>**/
/*S*public interface GList<T> : GCommon, IEnumerable<T>**/
{
    /**
     * Gets a number of elements in the underlying list.
     */
    public: virtual int32 length() = 0;
    
    /**
     * Gets the first element.
     */
    public: virtual T getFirst() = 0;

    /**
     * Gets the last element.
     */
    public: virtual T getLast() = 0;
    
    /**
     * Provides forward enumeration interface.
     */
    public: virtual typename GEnumeration<T>::ptr elements() = 0;

    /**
     * Provides backward enumeration interface.
     */
    public: virtual typename GEnumeration<T>::ptr elementsReversed() = 0;
    
    /**
     * Produces shallow copy of the underlying collection.
     */
    public: virtual typename GList<T>::ptr clone() = 0;
    
    /**
     * Defines type of elements stored in the collection.
     */
    /*C*/public: typedef T Element;/**/    
};
    
}

#endif // !ILIST_H__GLYMPSE__
