//Gradient.h declares hierarchy of classes for storing gradient information and related functions.
#pragma once
#include "Viewbox.h"
class stop {
public:
	color stop_color;
	float offset;
	float stop_opacity;
	stop() {
		offset = 0;
		stop_opacity = 1;
	}
};
