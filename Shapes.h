#ifndef SHAPES_H
#define SHAPES_H

#include <string>
#include <vector>
#include "Trans.h"


using std::string;
using std::vector;

// abstract class
class shape {
public:
    point start;
    color stroke_color, fill_color;
    float stroke_width;
    float stroke_opacity, fill_opacity;
    string stroke_id, fill_id;
    multi_transform trans;

    shape() {
        stroke_id = fill_id = "";
        stroke_width = 0;
        stroke_opacity = fill_opacity = 1;
    }

    virtual void draw(Graphics& graphics) = 0;
};

// derived classes
class line : public shape {
public:
    point end;
    void draw(Graphics& graphics) override;
};

class rectangle : public shape {
public:
    float width, height;
    void draw(Graphics& graphics) override;
};

class ellipse : public shape {
public:
    float rx, ry;
    ellipse() {
        rx = ry = 0;
    }
    void draw(Graphics& graphics) override;
};

class circle : public shape {
public:
    point center;
    float r;
    circle() {
        r = 0;
    }
    void draw(Graphics& graphics) override;
};

class polygon : public shape {
public:
    vector<point> p;
    void draw(Graphics& graphics) override;
};

class polyline : public shape {
public:
    vector<point> p;
    void draw(Graphics& graphics) override;
};

class text : public shape {
public:
    float font_size;
    string text_;
    string font_family;
    string text_anchor;
    bool italic;
    float dx, dy;

    text() {
        text_ = "";
        text_anchor = "start";
        font_family = "Times New Roman";
        italic = false;
        dx = dy = 0;
    }

    void draw(Graphics& graphics) override;
};

class Path : public shape {
public:
    string data;
    string linecap, linejoin;

    Path() {
        linecap = "butt";
        linejoin = "miter";
    }

    void read_single_point(string data, int& index, point& p);
    float read_single_point(string data, int& index);
    void draw(Graphics& graphics) override;
};

// read shape attributes
void read_line(string name, string value, line* line);
void read_rectangle(string name, string value, rectangle* rect);
void read_ellipse(string name, string value, ellipse* elli);
void read_circle(string name, string value, circle* cir);
void read_polygon(string name, string value, polygon* polygon);
void read_polyline(string name, string value, polyline* polyline);
void read_text(string name, string value, text* text);
void read_path(string name, string value, Path* path);

#endif // !SHAPES_H
