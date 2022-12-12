#include "tester.h"
using std::endl;
using std::string;

void tests()
{
    int numCorrect = 0;
    Header task1 = firstTask();
    Header test1("examples\\EXAMPLE_part1.tga");
    if(compare(task1, test1))
    {
        cout<<"Task One......Success" << endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task One......Failed" << endl;
    }
    Header task2 = secondTask();
    Header test2("examples\\EXAMPLE_part2.tga");
    if(compare(task2, test2))
    {
        cout<<"Task Two......Success" << endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Two......Failed"<< endl;
    }
    Header task3 = thirdTask();
    Header test3("examples\\EXAMPLE_part3.tga");
    if(compare(task3, test3))
    {
        cout<<"Task Three....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Three....Failed"<< endl;
    }
    Header task4 = fourthTask();
    Header test4("examples\\EXAMPLE_part4.tga");
    if(compare(task4, test4))
    {
        cout<<"Task Four.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Four.....Failed"<< endl;
    }
    Header task5 = fifthTask();
    Header test5("examples\\EXAMPLE_part5.tga");
    if(compare(task5, test5))
    {
        cout<<"Task Five.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Five.....Failed"<< endl;
    }
    Header task6 = sixthTask();
    Header test6("examples\\EXAMPLE_part6.tga");
    if(compare(task6, test6))
    {
        cout<<"Task Six.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Six.....Failed"<< endl;
    }
    Header task7 = seventhTask();
    Header test7("examples\\EXAMPLE_part7.tga");
    if(compare(task7, test7))
    {
        cout<<"Task Seven.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task seven.....Failed"<< endl;
    }
    eighthTask();
    Header redA("output\\part8_r.tga");
    Header greenA("output\\part8_g.tga");
    Header blueA("output\\part8_b.tga");
    Header redB("examples\\EXAMPLE_part8_r.tga");
    Header greenB("examples\\EXAMPLE_part8_g.tga");
    Header blueB("examples\\EXAMPLE_part8_b.tga");
    if(compare(redA,redB))
    {
        cout<<"Task EightA.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task EightA.....Failed"<< endl;
    }
    if(compare(greenA,greenB))
    {
        cout<<"Task EightB.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task EightB.....Failed"<< endl;
    }
    if(compare(blueA,blueB))
    {
        cout<<"Task EightC.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task EightC.....Failed"<< endl;
    }
    Header task9 = ninthTask();
    Header test9("examples\\EXAMPLE_part9.tga");
    if(compare(task9,test9))
    {
        cout<<"Task Nine.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Nine.....Failed"<< endl;
    }
    Header task10 = tenthTask();
    Header test10("examples\\EXAMPLE_part10.tga");
    if(compare(task10,test10))
    {
        cout<<"Task Ten.....Success"<< endl;
        numCorrect++;
    }
    else
    {
        cout<<"Task Ten.....Failed"<< endl;
    }
    cout << "You got " << numCorrect << " out of 12 correct" << endl;
}

//Multiples the color values of layer1 and patter1
Header firstTask()
{
    Header layer("input\\layer1.tga");
    Header pattern("input\\pattern1.tga");
    unsigned char** mul = mutiply(layer,pattern);
    pattern.write("output\\part1.tga", mul);
    del(mul, layer.height * layer.width);
    Header part1("output\\part1.tga");
    return part1;
}

Header secondTask()
{
    Header top("input\\layer2.tga");
    Header bottom("input\\car.tga");
    unsigned char** sub = subtract(top, bottom);
    top.write("output\\part2.tga", sub);
    del(sub, top.width* top.height);
    Header part2("output\\part2.tga");
    return part2;
}
Header thirdTask()
{
    Header top("input\\layer1.tga");
    Header bottom("input\\pattern2.tga");
    Header text("input\\text.tga");
    unsigned char** mul = mutiply(top, bottom);
    top.write("output\\temp.tga", mul);
    Header temp("output\\temp.tga");
    unsigned char** result = screen(text, temp);
    text.write("output\\part3.tga", result);
    temp.remove();
    Header part3("output\\part3.tga");
    del(result, part3.width* part3.height);
    return part3;
}

Header fourthTask()
{
    Header top("input\\layer2.tga");
    Header bottom("input\\circles.tga");
    unsigned char** mul = mutiply(top, bottom);
    Header top2("input\\pattern2.tga");
    top.write("output\\temp.tga", mul);
    Header bottom2("output\\temp.tga");
    unsigned char** result = subtract(top2, bottom2);
    top2.write("output\\part4.tga", result);
    del(result, top2.width* top2.height);
    Header part4("output\\part4.tga");
    bottom2.remove();
    return part4;
}
Header fifthTask()
{
    Header top("input\\layer1.tga");
    Header bottom("input\\pattern1.tga");
    unsigned char** result = overlay(top, bottom);
    top.write("output\\part5.tga", result);
    Header part5("output\\part5.tga");
    del(result, top.height*top.width);
    return part5;
}
Header sixthTask()
{
    Header image("input\\car.tga");
    int dataSize = image.width *image.height;
    unsigned char** imageData = image.getData();
    for(int i =0; i< dataSize; i++)
    {
        int temp = imageData[i][1];
        if(temp + 200 > 255)
        {
            imageData[i][1] = 255; //have to clamp the value to prevent buffer overflow
        }
        else
        {
            imageData[i][1] =(unsigned char)temp+200;
        }
    }
    image.write("output\\part6.tga", imageData);
    Header result("output\\part6.tga");
    del(imageData, dataSize);
    return result;
}
Header seventhTask()
{
    Header image("input\\car.tga");
    unsigned char** imageData = image.getData();
    int dataSize = image.height * image.width;
    for(int i = 0; i< dataSize; i++)
    {
       imageData[i][0] = 0; //since it is being scaled to 0 i can just set the red channel to 0 since 0*x =0
       int temp = (float)imageData[i][2] * 4;
       if(temp > 255) //clamping at 255 to prevent buffer overflow
       {
           imageData[i][2] = 255;
       }
       else
       {
           imageData[i][2] = (unsigned char) temp;
       }

    }
    image.write("output\\part7.tga", imageData);
    Header result("output\\part7.tga");
    del(imageData, dataSize);
    return result;
}
void eighthTask()
{
    string r = "red";
    string g = "green";
    string b = "blue";
    Header image("input\\car.tga");
    int dataSize = image.width *image.height;
    auto red = toChannel(r, image);
    auto green = toChannel(g, image);
    auto blue = toChannel(b, image);
    image.write("output\\part8_r.tga", red);
    image.write("output\\part8_g.tga", green);
    image.write("output\\part8_b.tga", blue);
    del(red, dataSize);
    del(green, dataSize);
    del(blue,dataSize);
}
Header ninthTask()
{
    Header red("input\\layer_red.tga");
    Header green("input\\layer_green.tga");
    Header blue("input\\layer_blue.tga");
    unsigned char** imageData = combine(red, green, blue);
    blue.write("output\\part9.tga", imageData);
    Header image("output\\part9.tga");
    del(imageData, red.width * red.height);
    return image;
}
Header tenthTask()
{
    Header image("input\\text2.tga");
    auto imageData = rotate180(image); //need to create this varible so I can delete the data afterwards
    image.write("output\\part10.tga", imageData);
    Header rotate("output\\part10.tga");
    del(imageData, image.height*image.width);
    return rotate;
}
//compares to tell if two .tga files have the same data value
bool compare(Header output, Header example)
{
    if(output == example)
    {

    }
    else
    {
        cout<<"HERE";
        return false;
    }
    unsigned char** out = output.getData();
    unsigned char** exam = example.getData();
    int dataSize = output.height *output.width;
    for(int i = 0; i< dataSize; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(out[i][j] != exam[i][j])
            {
                cout << i <<" " << j << " "<< (int)out[i][j] << " " << (int)exam[i][j];
                del(out, dataSize);
                del(exam,dataSize);
                return false;
            }
        }
    }
    del(out, dataSize);
    del(exam,dataSize);
    return true;
}