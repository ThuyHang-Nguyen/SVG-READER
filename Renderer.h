#ifndef RENDERER_H
#define RENDERER_H

#include "Shape.h"
vector<shape*> parseSVG(const string& filename);

class Renderer {
public:
	vector<shape*> shapes;

	Renderer() {
		for (auto e : shapes)
			delete e;
		shapes.clear();
	}

	void loadSVG(const string& filename) {
		// Xóa các shape cũ nếu có
		for (auto e : shapes)
			delete e;
		shapes.clear();
		shapes = parseSVG(filename);
	}

	void render(Graphics& graphics) {
		for (shape* s : shapes)
			s->draw(graphics);
	}

	~Renderer() {
		for (auto e : shapes)
			delete e;
		shapes.clear();
	}
};


#endif

