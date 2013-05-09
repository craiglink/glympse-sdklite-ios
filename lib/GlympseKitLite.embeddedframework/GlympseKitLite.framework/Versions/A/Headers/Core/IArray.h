//------------------------------------------------------------------------------
//
// Copyright (c) 2012 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IARRAY_H__GLYMPSE__
#define IARRAY_H__GLYMPSE__

namespace Glympse 
{
    
/*C*/
template< class T > struct IArray;
/// Smart pointer wrapper over IArray.
template< class T > class GArray
{
    private: GArray();
    public: typedef O< IArray< T > > ptr;
};
/**/

/**
 * Provides immutable access to vector (array) container with support for range-based enumeration.
 */
/*C*/template< class T > struct IArray : public ICommon/**/
/*J*public interface GArray<T> extends GCommon, Iterable<T>**/
/*S*public interface GArray<T> : GCommon, IEnumerable<T>**/
{
    /**
     * Gets a number of elements in the underlying array.
     */
    public: virtual int32 length() = 0;
    
    /**
     * Extracts element at given index.
     */
    public: virtual T at(int32 index) = 0;  
    
    /**
     * Provides standard enumeration interface.
     */
    public: virtual typename GEnumeration<T>::ptr elements() = 0;
    
    /**
     * Produces shallow copy of the underlying collection.
     */
    public: virtual typename GArray<T>::ptr clone() = 0;
    
    /**
     * Defines type of elements stored in the collection.
     */
    /*C*/public: typedef T Element;/**/
};

/**
 * @name Range-based for loops. 
 *
 * Support for range-based for-loops (C++11 feature).
 */
/*C*/

/// Wraps IEnumeration into forward iterator.
template< typename T > struct RangeIterator
{
    private: typename GEnumeration<T>::ptr _elements;
    private: int32 _position;
    private: T _current;
    
    public: RangeIterator(const typename GEnumeration<T>::ptr& elements, int32 position)
        : _elements(elements)
        , _position(position)
        , _current(_elements->nextElement())
    {
    }
    
    public: const RangeIterator<T>& operator++()
    {
        ++_position;
        if ( _elements->hasMoreElements() )
        {
            _current = _elements->nextElement();
        }
        return *this;
    }
    
    public: T operator*() const
    {
        return _current;
    }
    
    public: bool operator!=(const RangeIterator& other) const
    {
        return _position != other._position;
    }
};
    
// Provides standalone begin() function for ADL.
template< typename T > RangeIterator< typename T::Element > begin(const O<T>& container)
{
    return RangeIterator< typename T::Element >(container->elements(), 0);
}
   
// Provides standalone end() function for ADL.
template< typename T > RangeIterator< typename T::Element > end(const O<T>& container)
{
    return RangeIterator< typename T::Element >(container->elements(), container->length());
}
/**/
    
}

#endif // !IARRAY_H__GLYMPSE__
