#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Shapes.h"
#include "Viewbox.h"
#include "rapidxml.hpp"

using std::string;
using std::unordered_map;
using std::vector;


class group {
public:
	unordered_map<string, string> attributes;
	void traversal_group(rapidxml::xml_node<>* root, float& max_width, float& max_height, vector<shape*>& shapes);
};

vector<shape*> read_file(string file_name, float& max_width, float& max_height, viewBox& vb);



