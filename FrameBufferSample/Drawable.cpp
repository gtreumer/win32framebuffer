//
//  Drawable.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/18/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "Drawable.h"
#include "ShaderProgram.h"
#include "SimpleSquareGeometry.h"
#include "Buffer.h"
#include <OpenGL/gl.h>
#include <string>
#include "Vector.h"
#include "Matrix.h"
#include <cmath>

template <typename T>
void SafeDeletePtr(T* ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = 0;
    }
}

const std::string vertShader =
"attribute vec3 a_vertex; \n"
"attribute vec2 a_texture; \n"
"uniform mat4 a_mvp;\n"
"varying vec2 tex_coords; \n"
"void main (void) \n"
"{ \n"
"tex_coords = a_texture; \n"
"gl_Position = a_mvp * vec4(a_vertex, 1.0); \n"
"} \n";

const std::string fragShader =
"uniform sampler2D tex; \n"
"varying vec2 tex_coords; \n"
"void main (void)  \n"
"{ \n"
"vec4 color = texture2D(tex, tex_coords.st); \n"
//"gl_FragColor = color; \n"
"gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
"} \n";

Drawable::Drawable(const Math::Vec2f& size) :
    mProgram(0),
    mGeometry(0),
    mBuffer(0),
    mProgId(0),
    mTexId(0),
    mSize(size)
{
    
}

Drawable::~Drawable()
{
    SafeDeletePtr(mProgram);
    SafeDeletePtr(mGeometry);
    SafeDeletePtr(mBuffer);
}

void Drawable::draw()
{
    if (invalid())
        validate();
    
    glUseProgram(mProgId);
    
    const float distance = 500.0f;
    const float fovY = (float) (2 * std::atan(480.0f / (2 * distance)));
    const float near = 0.1f;
    const float far = 100.0f;
    const float aspect = 640.0f / 480.0f;
    float tan = std::tan(fovY / 2.0f);
    float h = near * tan;
    float w = h * aspect;
    Math::Mat4 proj = Math::Mat4::Frustum(-w, w, -h, h, near, far);
    Math::Mat4 view = Math::Mat4::LookAt(Math::Vec3f(0.0f, 0.0f, distance), Math::Vec3f(0.0f, 0.0f, 0.0f), Math::Vec3f(0.0f, 1.0f, 0.0f));

    Math::Mat4 viewProj = view * proj;
    Math::Mat4 world = Math::Mat4::Identity();
    Math::Mat4 mvp = world * viewProj;
    
    GLuint worldLoc = glGetUniformLocation(mProgId, "a_mvp");
    glUniformMatrix4fv(worldLoc, 1, false, mvp.Pointer());
    
    // load texture
    GLuint samplerLoc = glGetUniformLocation(mProgId, "tex");
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(samplerLoc, 0);
    unsigned char* imgBuffer = new unsigned char [3];
    imgBuffer[0] = 255;
    imgBuffer[1] = 255;
    imgBuffer[2] = 255;
    loadTexture(3, 1, imgBuffer);
    delete [] imgBuffer;
    
    
    // load vertices
    mBuffer->bind();
    unsigned int vertexLoc  = glGetAttribLocation(mProgId, "a_vertex");
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, false, mBuffer->getStride(), (void*)mBuffer->getVertexOffset());

    // load texture coordinates
    unsigned int texCoordsLoc  = glGetAttribLocation(mProgId, "a_texture");
    if (texCoordsLoc != -1)
    {
        glEnableVertexAttribArray(texCoordsLoc);
        glVertexAttribPointer(texCoordsLoc, 2, GL_FLOAT, false, mBuffer->getStride(), (void*) mBuffer->getTextureOffset());
    }

    unsigned short indicies[4] = {0, 1, 2, 3};
    glDrawElements(GL_TRIANGLE_STRIP, mBuffer->getSize(), GL_UNSIGNED_SHORT, indicies);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(vertexLoc);
    glDisableVertexAttribArray(texCoordsLoc);
    
    glUseProgram(0);
}

void Drawable::setTransform(const Math::Mat4& transform)
{
    mTransform = transform;
}

void Drawable::loadTexture(int width, int height, unsigned char* imgBuffer)
{
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (mTexId)
    {
        glGenTextures(1, &mTexId);
        glBindTexture(GL_TEXTURE_2D, mTexId);
        
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte*)imgBuffer);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, mTexId);
    }
}

void Drawable::validate()
{
    mProgram = new ShaderProgram(vertShader, fragShader);
    mProgId = mProgram->getId();
    
    mGeometry = new SimpleSquareGeometry(mSize.x, mSize.y);
    mBuffer = new Buffer(mGeometry);
    
    mInvalid = false;
}
