//
//  RenderFrameBufferCache.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__RenderFrameBufferCache__
#define __FrameBufferSample__RenderFrameBufferCache__

#include "Cache.h"

class FrameBufferObject : public Cache
{
public:
    FrameBufferObject(int width, int height);
    ~FrameBufferObject();
    
    virtual void validate();
    void bind();
    void unbind();
    unsigned int getTexId() const;
private:
    bool checkFramebufferStatus();
    void printFramebufferInfo();
    unsigned int mFboId;
    unsigned int mRboId;
    unsigned int mTexId;
    int mWidth;
    int mHeight;
};

#endif /* defined(__FrameBufferSample__RenderFrameBufferCache__) */
