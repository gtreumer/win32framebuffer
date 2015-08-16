//
//  RenderPass.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef FrameBufferSample_RenderPass_h
#define FrameBufferSample_RenderPass_h

class RenderPassVisitor;
class RenderPass
{
public:
    RenderPass() {}
    virtual ~RenderPass() {}
    
    virtual void visit(RenderPassVisitor& v) = 0;
};

#endif
