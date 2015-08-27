//
//  Scene.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "Scene.h"
#include "Drawable.h"
#include "FileLoader.h"
#include <string>
#include <OpenGL/gl.h>
#include "unistd.h"

Scene::Scene(int width, int height) :
mWidth(width),
mHeight(height)
{
    
}

Scene::~Scene()
{
    if (mDrawable)
    {
        delete mDrawable;
        mDrawable = 0;
    }
}

void Scene::draw()
{
    if (invalid())
        validate();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glViewport(0, 0, mWidth, mHeight);
    
    
    mDrawable->draw(getViewProjMatrix());
}

void Scene::validate()
{
    char * dir = getcwd(NULL, 0);
    mDrawable = new Drawable(Math::Vec2f(300.0f, 300.0f));
    if (mTextureData.pixels.empty())
        mTextureData = FileLoader::loadBmp("/Users/TarasLavriv/Documents/FrameBufferSample/test2.bmp");
    mDrawable->setTextureData(mTextureData);
    mInvalid = false;
}

const Math::Mat4& Scene::getViewProjMatrix()
{
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
    
    mViewProjMatrix = view * proj;

    return mViewProjMatrix;
}