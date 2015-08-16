//
//  Buffer.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "Buffer.h"
#include "Geometry.h"
#include <OpenGL/gl.h>

Buffer::Buffer(const Geometry* geom) :
mBufferId(0),
mGeometry(geom)
{
}

Buffer::~Buffer()
{
    
}

void Buffer::bind()
{
    if (invalid())
        validate();
    
    glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
}

void Buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Buffer::validate()
{
    glGenBuffers(1, &mBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, mBufferId);
    glBufferData(GL_ARRAY_BUFFER, mGeometry->getSize() * sizeof(float), mGeometry->getData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mInvalid = false;
}