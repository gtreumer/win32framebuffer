//
//  FrameBufferObject.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/16/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "FrameBufferObject.h"
#include <OpenGL/gl.h>
#include <exception>
#include <iostream>
#include "glInfo.h"


FrameBufferObject::FrameBufferObject(int width, int height) :
mFboId(0),
mRboId(0),
mTexId(0),
mWidth(width),
mHeight(height)
{
    
}

FrameBufferObject::~FrameBufferObject()
{
    
}

void FrameBufferObject::validate()
{
    if (!invalid())
        return;
    
    // generate texture id
    glGenTextures(1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap generation included in OpenGL v1.4
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);


    bool fboSupported = false;
    bool fboUsed = false;
    glInfo glInfo;
    glInfo.getInfo();
    glInfo.printSelf();
#ifdef _WIN32
    // check if FBO is supported by your video card
    if(glInfo.isExtensionSupported("GL_ARB_framebuffer_object"))
    {
        // get pointers to GL functions
        glGenFramebuffers                     = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
        glDeleteFramebuffers                  = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
        glBindFramebuffer                     = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
        glCheckFramebufferStatus              = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
        glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
        glGenerateMipmap                      = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
        glFramebufferTexture2D                = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
        glFramebufferRenderbuffer             = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
        glGenRenderbuffers                    = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
        glDeleteRenderbuffers                 = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
        glBindRenderbuffer                    = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
        glRenderbufferStorage                 = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
        glGetRenderbufferParameteriv          = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
        glIsRenderbuffer                      = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
        
        // check once again FBO extension
        if(glGenFramebuffers && glDeleteFramebuffers && glBindFramebuffer && glCheckFramebufferStatus &&
           glGetFramebufferAttachmentParameteriv && glGenerateMipmap && glFramebufferTexture2D && glFramebufferRenderbuffer &&
           glGenRenderbuffers && glDeleteRenderbuffers && glBindRenderbuffer && glRenderbufferStorage &&
           glGetRenderbufferParameteriv && glIsRenderbuffer)
        {
            fboSupported = fboUsed = true;
//            std::cout << "Video card supports GL_ARB_framebuffer_object." << std::endl;
        }
        else
        {
            fboSupported = fboUsed = false;
            throw std::exception(Video card does NOT support GL_ARB_framebuffer_object.");
//            std::cout << "Video card does NOT support GL_ARB_framebuffer_object." << std::endl;
        }
    }
    
    // check EXT_swap_control is supported
    if(glInfo.isExtensionSupported("WGL_EXT_swap_control"))
    {
        // get pointers to WGL functions
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");
        if(wglSwapIntervalEXT && wglGetSwapIntervalEXT)
        {
            // disable v-sync
            wglSwapIntervalEXT(0);
            std::cout << "Video card supports WGL_EXT_swap_control." << std::endl;
        }
    }
    
#else // for linux, do not need to get function pointers, it is up-to-date
    if(glInfo.isExtensionSupported("GL_ARB_framebuffer_object"))
    {
        fboSupported = fboUsed = true;
        std::cout << "Video card supports GL_ARB_framebuffer_object." << std::endl;
    }
    else
    {
        fboSupported = fboUsed = false;
//        throw std::exception("Video card does NOT support GL_ARB_framebuffer_object.");
        std::cout << "Video card does NOT support GL_ARB_framebuffer_object." << std::endl;
    }
#endif
    
    if(fboSupported)
    {
        // create a framebuffer object, you need to delete them when program exits.
        glGenFramebuffers(1, &mFboId);
        glBindFramebuffer(GL_FRAMEBUFFER, mFboId);
        
        // create a renderbuffer object to store depth & stencil info with GL_DEPTH_STENCIL
        // Check "GL_EXT_packed_depth_stencil" extension spec for more details.
        // NOTE: A depth renderable image should be attached the FBO for depth test.
        // If we don't attach a depth renderable image to the FBO, then
        // the rendering output will be corrupted because of missing depth test.
        // If you also need stencil test for your rendering, then you must
        // attach additional image to the stencil attachement point, too.
        glGenRenderbuffers(1, &mRboId);
        glBindRenderbuffer(GL_RENDERBUFFER, mRboId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, mWidth, mHeight);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        
        // attach a texture to FBO color attachement point
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0);
        
        // attach a renderbuffer to depth attachment point
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRboId);
        
        // attach a renderbuffer to stencil attachment point
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRboId);
        
        //@@ disable color buffer if you don't attach any color buffer image,
        //@@ for example, rendering depth buffer only to a texture.
        //@@ Otherwise, glCheckFramebufferStatusEXT will not be complete.
        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);
        
        // check FBO status
        printFramebufferInfo();
        bool status = checkFramebufferStatus();
        if(!status)
            fboUsed = false;
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    mInvalid = false;
}

void FrameBufferObject::bind()
{
    if (invalid())
        validate();
    
    glBindFramebuffer(GL_FRAMEBUFFER, mFboId);
}

void FrameBufferObject::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
                                 
unsigned int FrameBufferObject::getTexId() const
{
    return mTexId;
}
                                 
bool FrameBufferObject::checkFramebufferStatus()
{
 // check FBO status
 GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
 switch(status)
 {
     case GL_FRAMEBUFFER_COMPLETE:
         std::cout << "Framebuffer complete." << std::endl;
         return true;
         
     case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
         std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
         return false;
         
     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
         std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
         return false;
     case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
         std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
         return false;
         
     case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
         std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
         return false;
         
     case GL_FRAMEBUFFER_UNSUPPORTED:
         std::cout << "[ERROR] Framebuffer incomplete: Unsupported by FBO implementation." << std::endl;
         return false;
         
     default:
         std::cout << "[ERROR] Framebuffer incomplete: Unknown error." << std::endl;
         return false;
 }
 
}

void FrameBufferObject::printFramebufferInfo()
{
//    std::cout << "\n===== FBO STATUS =====\n";
//    
//    // print max # of colorbuffers supported by FBO
//    int colorBufferCount = 0;
//    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &colorBufferCount);
//    std::cout << "Max Number of Color Buffer Attachment Points: " << colorBufferCount << std::endl;
//    
//    int objectType;
//    int objectId;
//    
//    // print info of the colorbuffer attachable image
//    for(int i = 0; i < colorBufferCount; ++i)
//    {
//        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                              GL_COLOR_ATTACHMENT0+i,
//                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
//                                              &objectType);
//        if(objectType != GL_NONE)
//        {
//            glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                                  GL_COLOR_ATTACHMENT0+i,
//                                                  GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
//                                                  &objectId);
//            
//            std::string formatName;
//            
//            std::cout << "Color Attachment " << i << ": ";
//            if(objectType == GL_TEXTURE)
//            {
//                std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
//            }
//            else if(objectType == GL_RENDERBUFFER)
//            {
//                std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
//            }
//        }
//    }
//    
//    // print info of the depthbuffer attachable image
//    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                          GL_DEPTH_ATTACHMENT,
//                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
//                                          &objectType);
//    if(objectType != GL_NONE)
//    {
//        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                              GL_DEPTH_ATTACHMENT,
//                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
//                                              &objectId);
//        
//        std::cout << "Depth Attachment: ";
//        switch(objectType)
//        {
//            case GL_TEXTURE:
//                std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
//                break;
//            case GL_RENDERBUFFER:
//                std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
//                break;
//        }
//    }
//    
//    // print info of the stencilbuffer attachable image
//    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                          GL_STENCIL_ATTACHMENT,
//                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
//                                          &objectType);
//    if(objectType != GL_NONE)
//    {
//        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
//                                              GL_STENCIL_ATTACHMENT,
//                                              GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
//                                              &objectId);
//        
//        std::cout << "Stencil Attachment: ";
//        switch(objectType)
//        {
//            case GL_TEXTURE:
//                std::cout << "GL_TEXTURE, " << getTextureParameters(objectId) << std::endl;
//                break;
//            case GL_RENDERBUFFER:
//                std::cout << "GL_RENDERBUFFER, " << getRenderbufferParameters(objectId) << std::endl;
//                break;
//        }
//    }
    
    std::cout << std::endl;
}
