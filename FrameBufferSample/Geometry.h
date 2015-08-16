//
//  Geometry.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef FrameBufferSample_Geometry_h
#define FrameBufferSample_Geometry_h

#include <vector>

class Geometry
{
public:
    Geometry() {}
    virtual ~Geometry() {}
    
    virtual std::size_t getVertexOffet() const = 0;
    virtual std::size_t getTextureOffet() const = 0;
    virtual std::size_t getNormalOffet() const = 0;
    virtual std::size_t getStride() const = 0;
    virtual void* getData() const = 0;
    virtual std::size_t getSize() const = 0;
};

#endif
