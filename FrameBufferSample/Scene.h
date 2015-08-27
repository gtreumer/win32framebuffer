//
//  Scene.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__Scene__
#define __FrameBufferSample__Scene__

#include "Cache.h"
#include "Matrix.h"
#include "FileLoader.h"

class Drawable;

class Scene : public Cache
{
public:
    Scene(int width, int height);
    ~Scene();

    void draw();
protected:
    void validate();
    const Math::Mat4& getViewProjMatrix();
private:
    Drawable* mDrawable;
    int mWidth;
    int mHeight;
    Math::Mat4 mViewProjMatrix;
    FileLoader::ImageData mTextureData;
    
};

#endif /* defined(__FrameBufferSample__Scene__) */
