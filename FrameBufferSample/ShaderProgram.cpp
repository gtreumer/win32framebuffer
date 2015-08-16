//
//  ShaderProgram.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "ShaderProgram.h"
#include <OpenGL/gl.h>

#define GL_CHECK(x) \
x; \
{ \
GLenum glError = glGetError(); \
if(glError != GL_NO_ERROR) { \
fprintf(stderr, "glGetError() = %i (0x%.8x) at line %i\n", glError, glError, __LINE__); \
exit(1); \
} \
}

#define EGL_CHECK(x) \
x; \
{ \
EGLint eglError = eglGetError(); \
if(eglError != EGL_SUCCESS) { \
fprintf(stderr, "eglGetError() = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
exit(1); \
} \
}

ShaderProgram::ShaderProgram(const std::string& vs, const std::string& fs) :
mVertexShaderSrc(vs),
mFragmentShaderSrc(fs),
mId(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

unsigned int ShaderProgram::getId()
{
    if (!mId)
    {
        unsigned int vertShaderId = mValidateShader(GL_VERTEX_SHADER, mVertexShaderSrc);
        unsigned int fragShaderId = mValidateShader(GL_FRAGMENT_SHADER, mFragmentShaderSrc);
        mId = GL_CHECK(glCreateProgram());
        
        GL_CHECK(glAttachShader(mId, vertShaderId));
        GL_CHECK(glAttachShader(mId, fragShaderId));
        GL_CHECK(glLinkProgram(mId));
    }
    
    return mId;
}


unsigned int ShaderProgram::mValidateShader(int shaderType, const std::string& shaderSrc)
{
    int iStatus = -1;
    
    unsigned int shaderID = GL_CHECK(glCreateShader(shaderType));
    
    const char *c_str = shaderSrc.c_str();
    GL_CHECK(glShaderSource(shaderID, 1, &c_str, NULL));
    GL_CHECK(glCompileShader(shaderID));
    GL_CHECK(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &iStatus));
    
    if(iStatus != GL_TRUE) {
        GLint iLen;
        char *sDebugSource = NULL;
        char *sErrorLog = NULL;
        
        GL_CHECK(glGetShaderiv(shaderID, GL_SHADER_SOURCE_LENGTH, &iLen));
        
        sDebugSource = (char*)malloc(iLen);
        
        GL_CHECK(glGetShaderSource(shaderID, iLen, NULL, sDebugSource));
        
        printf("Debug source START:\n%s\nDebug source END\n\n", sDebugSource);
        free(sDebugSource);
        
        GL_CHECK(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &iLen));
        
        sErrorLog = (char*)malloc(iLen);
        
        GL_CHECK(glGetShaderInfoLog(shaderID, iLen, NULL, sErrorLog));
        
        printf("Log START:\n%s\nLog END\n\n", sErrorLog);
        free(sErrorLog);
    }
    
    return shaderID;
}