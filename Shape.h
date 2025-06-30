#pragma once
#include"Gradient.h"
// Include all class of shapes rendered on screen and functions to read them
// user-defined constructors are added to make it easy to read 
//abstract class
class shape {
public:
	point start;
	color stroke_color, fill_color;
	float stroke_width;
	float stroke_opacity, fill_opacity;
	string stroke_id, fill_id;
	shape() {
		stroke_id = fill_id = "";
		stroke_width = 0;
		stroke_opacity = fill_opacity = 1;
	}
	/*virtual void draw(Graphics& graphics, defs def) = 0;*/
};

//derived classes
class line : public shape {
public:
	// line include start point and end point so we add end point 
	point end;
	//void draw(Graphics& graphics, defs def) override;
};

class rectangle : public shape {
public:
	float width, height;
	//void draw(Graphics& graphics, defs def) override;
};

class ellipse : public shape {
public:
	float rx, ry; //radius on x and y
	ellipse() { 
		rx = ry = 0;
	}
	//void draw(Graphics& graphics, defs def) override;
};

class circle : public shape {
public:
	point center;
	float r; // radius
	circle() {
		r = 0;
	}
	//void draw(Graphics& graphics, defs def) override;
	// Trong class circle
	//void draw()  {
	//	cout << "Vẽ hình tròn tại " << endl;
	//}

};

class polygon : public shape {
public:
	vector<point> p;
	//void draw(Graphics& graphics, defs def) override;
};

class polyline : public shape {
public:
	vector<point> p;
	//void draw(Graphics& graphics, defs def) override;
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
	// dang test de in ra man hinh ??
	void print() {
		cout << text_ << endl;
	}
	//void draw(Graphics& graphics, defs def) override;
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
	//void print() {
	//	cout << "path" << endl;
	//}
};

//read shapes functions
void read_line(string name, string value, line* line);
void read_rectangle(string name, string value, rectangle* rect);
void read_ellipse(string name, string value, ellipse* elli);
void read_circle(string name, string value, circle* cir);
void read_polygon(string name, string value, polygon* polygon);
void read_polyline(string name, string value, polyline* polyline);
void read_text(string name, string value, text* text);
void read_path(string name, string value, Path* path);