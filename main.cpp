#pragma once
#include <iostream>
#include <fstream>
#include "Header.h"
#include "blenders.h"
#include"tester.h"

using std::cout;
using std::string;


int main(int argc, const char** argv)
{
    if (argc == 1)
    {
        cout << "No arguments were given" << std::endl;
    }
    if(argv[1] == string("test"))
    {
        tests();
    }
    else if(argv[1] == "program")
    {
    firstTask();
    secondTask();
    thirdTask();
    fourthTask();
    fifthTask();
    sixthTask();
    seventhTask();
    eighthTask();
    ninthTask();
    tenthTask();
    }
    else
    {
        cout << "Invalid argument" << std::endl;
    }
    return 0;
}

