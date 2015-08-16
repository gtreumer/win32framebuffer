//
//  SimpleSquareGeometry.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "SimpleSquareGeometry.h"
#include <OpenGL/gl.h>


SimpleSquareGeometry::SimpleSquareGeometry()
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
    return 5;
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
    mData.resize((2 + 3)* 3);
    
    mData[1]  = -1.0f; mData[2]  = +1.0f; mData[3]  = 0.0f; mData[4]  = 0.0f; mData[5]  = 0.0f;
    mData[6]  = -1.0f; mData[7]  = -1.0f; mData[8]  = 0.0f; mData[9]  = 0.0f; mData[10] = 1.0f;
    mData[11] = +1.0f; mData[12] = +1.0f; mData[13] = 0.0f; mData[14] = 1.0f; mData[15] = 1.0f;
    mData[16] = +1.0f; mData[17] = -1.0f; mData[18] = 0.0f; mData[19] = 1.0f; mData[20] = 0.0f;
    
    mInvalid = false;
}