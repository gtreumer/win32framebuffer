//
//  SimpleSquareGeometry.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "SimpleSquareGeometry.h"
#include <OpenGL/gl.h>


SimpleSquareGeometry::SimpleSquareGeometry(float w, float h) :
mWidth(w), mHeight(h)
{
    if (invalid())
        validate();
}

SimpleSquareGeometry::~SimpleSquareGeometry()
{
    
}

std::size_t SimpleSquareGeometry::getVertexOffet() const
{
    return 0;
}

std::size_t SimpleSquareGeometry::getTextureOffet() const
{
    return 3;
}

std::size_t SimpleSquareGeometry::getNormalOffet() const
{
    return 0;
}

std::size_t SimpleSquareGeometry::getStride() const
{
    return 5 * sizeof(float);
}

void* SimpleSquareGeometry::getData() const
{
    return static_cast<void*>(&mData.at(0));
}

std::size_t SimpleSquareGeometry::getSize() const
{
    return static_cast<std::size_t>(mData.size());
}

void SimpleSquareGeometry::validate()
{
    mData.resize((2 + 3) * 4);
    
    float w = 0.5f * mWidth;
    float h = 0.5f * mHeight;
    
    mData[0]  = -1.0f * w; mData[1]  = +1.0f * h; mData[2]  = 0.0f; mData[3]  = 0.0f; mData[4]  = 1.0f;
    mData[5]  = -1.0f * w; mData[6]  = -1.0f * h; mData[7]  = 0.0f; mData[8]  = 0.0f; mData[9]  = 0.0f;
    mData[10] = +1.0f * w; mData[11] = +1.0f * h; mData[12] = 0.0f; mData[13] = 1.0f; mData[14] = 1.0f;
    mData[15] = +1.0f * w; mData[16] = -1.0f * h; mData[17] = 0.0f; mData[18] = 1.0f; mData[19] = 0.0f;
    
    mInvalid = false;
}