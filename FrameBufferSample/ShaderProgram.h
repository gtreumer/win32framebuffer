//
//  ShaderProgram.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef FrameBufferSample_ShaderProgram_h
#define FrameBufferSample_ShaderProgram_h

#include <string>
#include "stdlib.h"

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vs, const std::string& fs);
    ~ShaderProgram();
    
    unsigned int getId();
private:
    unsigned int mValidateShader(int shaderType, const std::string& shaderSrc);
    std::string mVertexShaderSrc;
    std::string mFragmentShaderSrc;
    unsigned int mId;
};


#endif
