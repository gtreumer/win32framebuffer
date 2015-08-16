//
//  Cache.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef FrameBufferSample_Cache_h
#define FrameBufferSample_Cache_h

class Cache
{
public:
    Cache() : mInvalid(true) {}
    virtual ~Cache() {}

protected:
    virtual void validate() = 0;
    virtual bool invalid() const { return mInvalid; }
    bool mInvalid;
};

#endif
