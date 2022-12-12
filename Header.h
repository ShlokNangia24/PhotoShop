#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#define RGB 3
using std::cout;
using std::vector;
void del(unsigned char** pointer, int dataSize);
struct Header
{
    Header(std::string name);
    std::string name;
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    void write(std::string output,unsigned char** imageData);
    unsigned char** getData();
    void remove();
    bool operator==(Header output);
};
