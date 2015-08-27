//
//  FileLoader.h
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/26/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#ifndef __FrameBufferSample__FileLoader__
#define __FrameBufferSample__FileLoader__

#include <vector>

class FileLoader
{
public:
    struct ImageData
    {
        std::vector<unsigned char> pixels;
        int width;
        int height;
        bool hasAlpha;
    };
    
    FileLoader() {}
    ~FileLoader() {}
    
    static ImageData loadBmp(const char* FilePath);
private:
    static ImageData mImageData;
};

#endif /* defined(__FrameBufferSample__FileLoader__) */
