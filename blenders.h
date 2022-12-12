#pragma once
#include "Header.h"
using std::string;

unsigned char** screen(Header topLayer, Header bottomLayer);
void del(unsigned char** pointer, int dataSize);
unsigned char** newPointers(int dataSize);
unsigned char** mutiply(Header topHeader, Header bottomHeader);
unsigned char** subtract(Header topLayer, Header bottomLayer);
unsigned char** overlay(Header topLayer, Header bottomLayer);
unsigned char** toChannel(string color, Header image);
unsigned char** combine(Header red, Header green, Header blue);
unsigned char** rotate180(Header image);