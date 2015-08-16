//
//  Scene.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "Scene.h"
#include <string>


const std::string vertShader =
"precision mediump float; \n"
"attribute vec4 a_vertex; \n"
"attribute vec2 a_texture; \n"
"varying vec2 tex_coords; \n"
"void main (void) \n"
"{ \n"
"tex_coords = a_texture; \n"
"gl_Position = a_vertex; \n"
"} \n";

const std::string fragShader =
"precision mediump float; \n"
"uniform sampler2D tex; \n"
"varying vec2 tex_coords; \n"
"void main (void)  \n"
"{ \n"
"vec4 color = texture2D(tex, tex_coords.st); \n"
"gl_FragColor = color; \n"
"} \n";

Scene::Scene()
{
    
}

Scene::~Scene()
{
    
}

void Scene::draw()
{
    
}