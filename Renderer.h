#ifndef RENDERER_H
#define RENDERER_H

#include "Shape.h"
vector<shape*> parseSVG(const string& filename);

class Renderer {
	Bitmap* buffer = nullptr;
	bool dirty = true; // cờ để biết có cần vẽ lại không
public:
	vector<shape*> shapes;

	Renderer() {
		for (auto e : shapes)
			delete e;
		shapes.clear();
	}

	void loadSVG(const string& filename) {
		for (auto e : shapes) delete e;
		shapes.clear();
		shapes = parseSVG(filename);
		dirty = true;
	}

	void render(Graphics& graphics, int width, int height) {
		if (dirty || !buffer) {
			if (buffer) delete buffer;
			buffer = new Bitmap(width, height);
			Graphics g(buffer);
			g.Clear(Color::White);
			for (shape* s : shapes)
				s->draw(g);
			dirty = false;
		}
		graphics.DrawImage(buffer, 0, 0);
	}

	~Renderer() {
		for (auto e : shapes) delete e;
		if (buffer) delete buffer;
	}
};


#endif

