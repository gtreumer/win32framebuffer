//
//  FileLoader.cpp
//  FrameBufferSample
//
//  Created by Taras Lavriv on 8/26/15.
//  Copyright (c) 2015 Taras Lavriv. All rights reserved.
//

#include "FileLoader.h"
#include <fstream>
#include "stdio.h"

FileLoader::ImageData FileLoader::mImageData;

FileLoader::ImageData FileLoader::loadBmp(const char* FilePath)
{
    std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
    if (!hFile.is_open()) throw std::invalid_argument("Error: File Not Found.");
    
    hFile.seekg(0, std::ios::end);
    int length = hFile.tellg();
    hFile.seekg(0, std::ios::beg);
    std::vector<std::uint8_t> FileInfo(length);
    hFile.read(reinterpret_cast<char*>(FileInfo.data()), 54);
    
    if(FileInfo[0] != 'B' && FileInfo[1] != 'M')
    {
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. Bitmap Required.");
    }
    
    if (FileInfo[28] != 24 && FileInfo[28] != 32)
    {
        hFile.close();
        throw std::invalid_argument("Error: Invalid File Format. 24 or 32 bit Image Required.");
    }
    
    short BitsPerPixel = FileInfo[28];
    int width = FileInfo[18] + (FileInfo[19] << 8);
    int height = FileInfo[22] + (FileInfo[23] << 8);
    std::uint32_t PixelsOffset = FileInfo[10] + (FileInfo[11] << 8);
    std::uint32_t size = ((width * BitsPerPixel + 31) / 32) * 4 * height;
    mImageData.pixels.resize(size);
    
    hFile.seekg (PixelsOffset, std::ios::beg);
    hFile.read(reinterpret_cast<char*>(mImageData.pixels.data()), size);
    hFile.close();
//    // Data read from the header of the BMP file
//    unsigned char header[54];
//    unsigned int dataPos;
//    unsigned int imageSize;
//    unsigned int width, height;
//    // Actual RGB data
////    unsigned char * data;
//    
//    // Open the file
//    FILE * file = fopen(FilePath,"rb");
//    if (!file)
//    {
//        printf("File could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n");
//        return FileLoader::ImageData();
//    }
//    
//    // Read the header, i.e. the 54 first bytes
//    
//    // If less than 54 bytes are read, problem
//    if ( fread(header, 1, 54, file)!=54 ){
//        printf("Not a correct BMP file\n");
//        return FileLoader::ImageData();
//    }
//    // A BMP files always begins with "BM"
//    if ( header[0]!='B' || header[1]!='M' ){
//        printf("Not a correct BMP file\n");
//        return FileLoader::ImageData();
//    }
//    // Make sure this is a 24bpp file
//    if ( *(int*)&(header[0x1E])!=0  )
//    {
//        printf("Not a correct BMP file\n");
//        return FileLoader::ImageData();
//    }
//    if ( *(int*)&(header[0x1C])!=24 )
//    {
//        printf("Not a correct BMP file\n");
//        return FileLoader::ImageData();
//    }
//    
//    // Read the information about the image
//    dataPos    = *(int*)&(header[0x0A]);
//    imageSize  = *(int*)&(header[0x22]);
//    width      = *(int*)&(header[0x12]);
//    height     = *(int*)&(header[0x16]);
//    
//    // Some BMP files are misformatted, guess missing information
//    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
//    if (dataPos==0)      dataPos=54; // The BMP header is done that way
//    
//    // Create a buffer
//    //data = new unsigned char [imageSize];
//    mImageData.pixels.resize(imageSize);
//    // Read the actual data from the file into the buffer
//    fread(&mImageData.pixels[0],1,imageSize,file);
//    
//    // Everything is in memory now, the file wan be closed
//    fclose (file);
//    
    mImageData.width = width;
    mImageData.height = height;
    mImageData.hasAlpha = BitsPerPixel == 32 ? true : false;
    return mImageData;
}
