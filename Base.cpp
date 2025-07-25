﻿#include"Base.h"

float clarifyFloat(string s) {
    if (s[0] == '.') {
        s.insert(0, "0");
    }
    if (s[0] == '-' && s[1] == '.') {
        s.insert(1, "0");
    }
    if (s[s.length() - 1] == '%') {
        string str = s.substr(0, s.length() - 1);
        return stof(str) / 100;
    }
    return stof(s);
}

//read color funtion
color read_RGB(string value) {
    color colour;
    //read rgb
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {
        stringstream ss(value);
        string temp = "";
        getline(ss, temp, '(');
        getline(ss, temp, ',');
        if (stof(temp) > 255)
            temp = "255";
        colour.red = stoi(temp);
        getline(ss, temp, ',');
        if (stof(temp) > 255)
            temp = "255";
        colour.green = stoi(temp);
        getline(ss, temp, ')');
        if (stof(temp) > 255)
            temp = "255";
        colour.blue = stoi(temp);
    }
    //read hex
    else if (value[0] == '#') {
        unsigned int hexValue;
        if (value.length() == 4) {
            char a1 = value[1], a2 = value[2], a3 = value[3];
            value = "#" + string(1, a1) + string(1, a1) + string(1, a2) + string(1, a2) + string(1, a3) + string(1, a3);
        }
        istringstream(value.substr(1)) >> hex >> hexValue;
        colour.red = (hexValue >> 16) & 0xFF;
        colour.green = (hexValue >> 8) & 0xFF;
        colour.blue = hexValue & 0xFF;
    }
    //read color name and convert to rgb
    else {
        //convert to lower case using string library
        transform(value.begin(), value.end(), value.begin(), ::tolower);

        //read rgb.txt file and find the color name then return rgb value
        ifstream file("rgb.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string buffer, name, rgb;
                getline(ss, buffer, '"');
                getline(ss, name, '"');
                if (name == value) {
                    getline(ss, buffer, '(');
                    ss >> colour.red;
                    ss >> buffer;
                    ss >> colour.green;
                    ss >> buffer;
                    ss >> colour.blue;
                    break;
                }
                else {
                    getline(ss, buffer, '}');
                }
            }
        }
        file.close();
    }
    return colour;
}

//read points and convert to vector of points
vector<point> read_points(string value) {
    vector<point> points;

    //erase all space in string
    value = std::regex_replace(value, std::regex("^\\s+|\\s+$"), "");

    stringstream ss(value);
    string temp = "";
    string pointStr;
    //read all points
    while (getline(ss, pointStr, ' ')) {
        point p;
        if (pointStr.find(',') == string::npos) {
            p.x = stof(pointStr);
            getline(ss, pointStr, ' ');
            p.y = stof(pointStr);
            points.push_back(p);
        }
        else {
            stringstream pointStream(pointStr);
            getline(pointStream, pointStr, ',');
            p.x = stof(pointStr);
            getline(pointStream, pointStr, ',');
            p.y = stof(pointStr);
            points.push_back(p);
        }
    }
    return points;
}