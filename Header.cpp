#pragma once
#include "Header.h"

//Header Constructer which sets the values in the .tga file to the varibles in the header
Header::Header(std::string name)
{
    this->name = name;
    std::ifstream file(name, std::ios::binary);
    if(file.is_open())
    {
        file.read(&idLength, sizeof(idLength));
        file.read(&colorMapType, sizeof(colorMapType));
        file.read(&dataTypeCode, sizeof(dataTypeCode));
        file.read((char *)&colorMapOrigin, sizeof(colorMapOrigin));
        file.read((char *)&colorMapLength, sizeof(colorMapLength));
        file.read((char *)&colorMapDepth, sizeof(colorMapDepth));
        file.read((char *)&xOrigin, sizeof(xOrigin));
        file.read((char *)&yOrigin, sizeof(yOrigin));
        file.read((char *)&width, sizeof(width));
        file.read((char *)&height, sizeof(height));
        file.read((char *)&bitsPerPixel, sizeof(bitsPerPixel));
        file.read((char *)&imageDescriptor, sizeof(imageDescriptor));
    }else
    {
        cout << name;
        throw std::runtime_error("File doesn't exist"); //makes sure the file exists so I don't go crazy
    }

}

//get data method returns the Image data from the .tga file is useful for writing new files
unsigned char** Header::getData()
{
    int dataSize = height * width;
    unsigned char** imageData = new unsigned char* [dataSize]; //I have to dynamically allocate an array, because i can't return 2d arrays
    for(int i = 0; i<dataSize;i++)
    {
        imageData[i] = new unsigned char[3];  //have to use a for loop to generate the RGB values of each pixel
    }
    unsigned char temp[dataSize][3];
    std::ifstream file(name, std::ios::binary);
    file.seekg(18); //seek 18 bits because that's how long the header is
    file.read((char*)&temp, sizeof(temp));
    for(int i =0; i< height*width;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            imageData[i][j] = temp[i][j];

        }
    }

    return imageData;
}

//writes a new file in a designated spot with the name provided with the same header data from the object used to perform the function
void Header::write(std::string output, unsigned char** imageData )
{
    unsigned char temp[height * width][RGB]; //temp varible is needed because .write has problems sending data with a 2d pointer
    for(int i =0; i< height*width;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            temp[i][j] = imageData[i][j];   //nested loop needed since both variables are 2c

        }
    }
    std::ofstream outStream(output, std::ios::binary);
    outStream.write(&idLength, sizeof(idLength));
    outStream.write(&colorMapType, sizeof(colorMapType));
    outStream.write(&dataTypeCode, sizeof(dataTypeCode));
    outStream.write((char *)&colorMapOrigin, sizeof(colorMapOrigin));
    outStream.write((char *)&colorMapLength, sizeof(colorMapLength));
    outStream.write((char *)&colorMapDepth, sizeof(colorMapDepth));
    outStream.write((char *)&xOrigin, sizeof(xOrigin));
    outStream.write((char *)&yOrigin, sizeof(yOrigin));
    outStream.write((char *)&width, sizeof(width));
    outStream.write((char *)&height, sizeof(height));
    outStream.write((char *)&bitsPerPixel, sizeof(bitsPerPixel));
    outStream.write((char *)&imageDescriptor, sizeof(imageDescriptor));
    outStream.write((char *)&temp, sizeof(temp));
}

void Header::remove()
{
    std::remove(name.c_str());
}

//Checks if the header files are equal to each other useful in reducing fluff when comparing equivelncy for the tested data to example
bool Header::operator==(Header output)
{
    if(idLength != output.idLength)
    {
        return false;
    }
    if(colorMapType != output.colorMapType)
    {
        return false;
    }
    if(dataTypeCode != output.dataTypeCode)
    {
        return false;
    }
    if(colorMapType != output.colorMapType)
    {
        return false;
    }
    if(dataTypeCode != output.dataTypeCode)
    {
        return false;
    }
    if(colorMapType != output.colorMapType)
    {
        return false;
    }
    if(colorMapDepth != output.colorMapDepth)
    {
        return false;
    }
    if(xOrigin != output.xOrigin)
    {
        return false;
    }
    if(yOrigin != output.yOrigin)
    {
        return false;
    }
    if(width != output.width)
    {
        return false;
    }
    if(height != output.height)
    {
        return false;
    }
    if(bitsPerPixel != output.bitsPerPixel)
    {
        return false;
    }
    if(imageDescriptor != output.imageDescriptor)
    {
        return false;
    }
    return true;
}
void del(unsigned char** pointer, int size)
{
    for(int i =0; i< size ; i++)
    {
        delete[] pointer[i];
    }
    delete[] pointer;
}





