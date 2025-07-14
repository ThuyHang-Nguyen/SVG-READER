#ifndef SHAPE_H
#define SHAPE_H
#include "Base.h"

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
	virtual void draw(Graphics& graphics) = 0;
	virtual ~shape() {}
};

//derived classes
class line : public shape {
public:
	// line include start point and end point so we add end point 
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
	float rx, ry; //radius on x and y
	ellipse() {
		rx = ry = 0;
	}
	void draw(Graphics& graphics) override;
};

class circle : public shape {
public:
	point center;
	float r; // radius
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
	bool closed = false;  // <-- Thêm thuộc tính mới

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
		font_size = 1;
		text_ = "";
		text_anchor = "start";
		font_family = "Arial";
		italic = false;
		dx = dy = 0;
	}
	void draw(Graphics& graphics) override;
};

//read shapes functions
void read_line(string name, string value, line* line);
void read_rectangle(string name, string value, rectangle* rect);
void read_ellipse(string name, string value, ellipse* elli);
void read_circle(string name, string value, circle* cir);
void read_polygon(string name, string value, polygon* polygon);
void read_polyline(string name, string value, polyline* polyline, bool& hasFillAttr);
void read_text(string name, string value, text* text);

#endif