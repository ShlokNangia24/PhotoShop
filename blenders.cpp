#pragma once
#include "blenders.h"
unsigned char** mutiply(Header topHeader, Header bottomHeader )
{
    int dataSize =  bottomHeader.height*bottomHeader.width;
    unsigned char** top = topHeader.getData();
    unsigned char** bottom = bottomHeader.getData();
    float temp = 0.0f;
    unsigned char** imageData = newPointers(dataSize);
    for(int i =0; i< dataSize;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float tempTop = (float)top[i][j]/255; //need to divide by 255 to prevent buffer overflow
            float tempBottom = (float)bottom[i][j]/255;
            temp = (tempTop * tempBottom)*255 + 0.5f; //0.5 is added for rounding purposes
            imageData[i][j] = (unsigned char) temp;
        }
    }

    del(top, dataSize);
    del(bottom, dataSize);
    return imageData;

}

//subtract deletes the top layer from the bottom layer
unsigned char** subtract(Header topLayer, Header bottomLayer)
{
    int dataSize =  bottomLayer.height*bottomLayer.width;
    unsigned char** top = topLayer.getData();
    unsigned char** bottom = bottomLayer.getData();
    int temp = 0;
    unsigned char** imageData = newPointers(dataSize);
    for(int i =0; i< dataSize;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int tempBottom = bottom[i][j];
            int tempTop = top[i][j];
            int value = tempBottom - tempTop;
            if(value<= 0) // clamping the value at 0 prevents buffer overflow
            {
                imageData[i][j] = 0;
            }
            else
            {
                imageData[i][j] = value;
            }
        }
    }
    del(top, dataSize);
    del(bottom, dataSize);
    return imageData;
}

//screen inverts both layers multiplys them together and then inverts the result
unsigned char** screen(Header topLayer, Header bottomLayer)
{
    int dataSize =  bottomLayer.height*bottomLayer.width;
    unsigned char** top = topLayer.getData();
    unsigned char** bottom = bottomLayer.getData();
    for(int i =0; i< dataSize;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            top[i][j] = 255 - top[i][j];
            bottom[i][j] = 255 - bottom[i][j];
        }
    }
    topLayer.write("output\\topTemp.tga", top);
    bottomLayer.write("output\\bottomTemp.tga", bottom);            //i had to make temp files since I had problem implenting the multiply function with unsinged char** as parameters
    Header tempTop("output\\topTemp.tga");
    Header bottomTemp("output\\bottomTemp.tga");
    unsigned char** mul = mutiply(tempTop, bottomTemp);
    tempTop.remove();
    bottomTemp.remove();
    unsigned char** imageData = newPointers(dataSize);
    for(int i =0; i< dataSize;i++)
    {
        for (int j = 0; j < 3; j++)
        {
            imageData[i][j] = 255 - mul[i][j];
        }
    }

    del(mul, dataSize);
    return imageData;
}

unsigned char** overlay(Header topLayer, Header bottomLayer)
{
    int dataSize =  bottomLayer.height*bottomLayer.width;
    unsigned char** top = topLayer.getData();
    unsigned char** bottom = bottomLayer.getData();
    unsigned char** imageData = newPointers(dataSize);
    for(int i = 0; i < dataSize; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            float tempTop =(float)top[i][j]/255;
            float tempBottom = (float)bottom[i][j]/255;
            if(tempBottom > 0.5f)
            {
                double temp = (1-2*(1-tempBottom)*(1-tempTop));
                temp = temp*255 +0.5;
                imageData[i][j] = (unsigned char)temp;
            }
            else
            {
                float temp = 2*tempTop*tempBottom;
                temp*=255;
                temp+=0.5;
                imageData[i][j] = (unsigned char)temp;
            }

        }
    }
    del(top, dataSize);
    del(bottom,dataSize);
    return imageData;
}

//sets all RGB at the specified channel to the value at the channel which is specified;
unsigned char** toChannel(string color, Header image)
{
    int dataSize = image.height * image.width;
    unsigned char** imageData = image.getData();
    unsigned char** chanel = newPointers(dataSize);
    if(color == "red")
    {
        for(int i =0; i<dataSize; i++)
        {
            chanel[i][0] = imageData[i][2];
            chanel[i][1] = imageData[i][2];
            chanel[i][2] = imageData[i][2];
        }
    }
    else if(color == "green")
    {
        for(int i =0; i<dataSize; i++)
        {
            chanel[i][0] = imageData[i][1];
            chanel[i][1] = imageData[i][1];
            chanel[i][2] = imageData[i][1];
        }
    }
    else if(color == "blue")
    {
        for(int i =0; i<dataSize; i++)
        {
            chanel[i][0] = imageData[i][0];
            chanel[i][1] = imageData[i][0];
            chanel[i][2] = imageData[i][0];
        }
    }
    else
    {
        throw std::runtime_error("That isn't a color");
    }
    del(imageData,dataSize);
    return chanel;
}
//Combines RGB values of channels of different header files
unsigned char** combine(Header redLayer, Header greenLayer, Header blueLayer)
{
    int dataSize = redLayer.height * redLayer.width;
    auto red = redLayer.getData(); //too lazy to write unsigned char** for all these functions so ill abuse the auto function
    auto green = greenLayer.getData();
    auto blue = blueLayer.getData();
    unsigned char** imageData = newPointers(dataSize);
    for(int i = 0; i<dataSize; i++)
    {
        imageData[i][0] = blue[i][0];
        imageData[i][1] = green[i][1];
        imageData[i][2] = red[i][2];
    }
    del(red, dataSize);
    del(green, dataSize);
    del(blue, dataSize);
    return imageData;
}
//rotates the image 180 degrees
unsigned char** rotate180(Header image)
{
    int count = 0;
    int dataSize = image.height * image.width;
    unsigned char** imageData = newPointers(dataSize);
    unsigned char** rotate = image.getData();
    for(int i = dataSize-1; i >= 0; i--)
    {
        for(int j = 0; j < 3; j++)
        {
            imageData[count][j] = rotate[i][j];
        }
        count++;
    }
    del(rotate, dataSize);
    return imageData;
}

unsigned char** newPointers(int dataSize)
{
    unsigned char** imageData = new unsigned char* [dataSize];
    for(int i = 0; i < dataSize;i++)
    {
        imageData[i] = new unsigned char[3];
    }
    return imageData;
}