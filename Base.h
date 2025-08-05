#pragma once
//This include the classes about view of screen, point and color to support for 
#include <iostream>
#include "rapidxml.hpp" // RapidXML library for read XML file
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h> //for GDI+ library
#include <locale>  // for std::wstring_convert and codecvt_utf8
#include <codecvt> // for codecvt_utf8
#include <algorithm>
#include <regex>
#include <unordered_map>
using namespace std;
using namespace Gdiplus;
using namespace rapidxml;
#pragma comment (lib,"Gdiplus.lib")
class Viewbox {
public:
	float width, height, min_x, min_y;
	float width_viewbox, height_viewbox;
	Viewbox()
	{
		width = 800;
		height = 600;
		min_x = 0;
		min_y = 0;
	}
	void setViewBoxAttribute(const string& viewBoxStr) {
		istringstream iss(viewBoxStr);
		iss >> min_x >> min_y >> width_viewbox >> height_viewbox;
	}
};
class color {
public:
	int red, green, blue;
	color() {
		red = green = blue = 0;
	}
};

class point {
public:
	float x, y;
	point() {
		x = 0, y = 0;
	}
};

//read functions
//support functions
string trim(string str);
bool check(char a);
void remove_space(string& s);
float clarifyFloat(string s);

//read color funtion
color read_RGB(string value);

//read point function
vector<point> read_points(string value);
