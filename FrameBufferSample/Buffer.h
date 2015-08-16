//
//  Buffer.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__Buffer__
#define __FrameBufferSample__Buffer__

#include "Cache.h"

class Geometry;

class Buffer : public Cache
{
public:
    Buffer(const Geometry* geom);
    ~Buffer();
    
    void bind();
    void unbind();
protected:
    virtual void validate();
private:
    unsigned int mBufferId;
    const Geometry* mGeometry;
};

#endif /* defined(__FrameBufferSample__Buffer__) */
