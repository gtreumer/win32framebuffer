//
//  SimpleSquareGeometry.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__SimpleSquareGeometry__
#define __FrameBufferSample__SimpleSquareGeometry__

#include "Geometry.h"
#include "Cache.h"

typedef std::vector<float> DataList;

class SimpleSquareGeometry : public Geometry, public Cache
{
public:
    SimpleSquareGeometry(float width, float height);
    ~SimpleSquareGeometry();
    
    virtual std::size_t getVertexOffet() const;
    virtual std::size_t getTextureOffet() const;
    virtual std::size_t getNormalOffet() const;
    virtual std::size_t getStride() const;
    virtual void* getData() const;
    virtual std::size_t getSize() const;
protected:
    void validate();
private:
    unsigned int mBufferId;
    mutable DataList mData;
    float mWidth;
    float mHeight;
    
    
};

#endif /* defined(__FrameBufferSample__SimpleSquareGeometry__) */
