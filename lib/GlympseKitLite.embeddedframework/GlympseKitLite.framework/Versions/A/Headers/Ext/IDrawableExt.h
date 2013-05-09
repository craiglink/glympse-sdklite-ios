//------------------------------------------------------------------------------
//
// Copyright (c) 2013 Glympse Inc.  All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef IDRAWABLEEXT_H__GLYMPSE__
#define IDRAWABLEEXT_H__GLYMPSE__

namespace Glympse 
{

#if defined(__APPLE__) && defined(__MACH__)
typedef UIImage* ImageType;
#elif defined(__QNXNTO__)
typedef QImage ImageType;
#endif

/**
 * Extends IDrawable with the set of platform specific methods.
 */
/*O*public**/ struct IDrawableExt : public IDrawable
{
    public: virtual ImageType getImage() = 0;
};
    
/*C*/typedef O< IDrawableExt > GDrawableExt;/**/
    
}

#endif // !IDRAWABLEEXT_H__GLYMPSE__
