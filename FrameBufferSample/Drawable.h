//
//  Drawable.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/18/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__Drawable__
#define __FrameBufferSample__Drawable__

#include "Cache.h"
#include "Vector.h"
#include "Matrix.h"
#include "FileLoader.h"
#include <vector>

class ShaderProgram;
class Geometry;
class Buffer;

class Drawable : public Cache
{
public:
    Drawable(const Math::Vec2f& size);
    ~Drawable();
    
    void setTransform(const Math::Mat4& transform);
    void setTextureData(const FileLoader::ImageData& textureData);
    
    void draw(const Math::Mat4& viewProj);
protected:
    void validate();
private:
    void loadTexture(const FileLoader::ImageData& imgData);
    ShaderProgram* mProgram;
    Geometry* mGeometry;
    Buffer* mBuffer;
    unsigned int mProgId;
    unsigned int mTexId;
    Math::Vec2f mSize;
    Math::Mat4 mTransform;
    FileLoader::ImageData mTextureData;
};

#endif /* defined(__FrameBufferSample__Drawable__) */
