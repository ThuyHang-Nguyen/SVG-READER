#include "Shape.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "rapidxml.hpp"
#include "Base.h"

using namespace std;
using namespace rapidxml;

vector<shape*> parseSVG(const string& filename) {
    vector<shape*> elements;

    ifstream file(filename);
    if (!file) return elements;

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    vector<char> xml_copy(content.begin(), content.end());
    xml_copy.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&xml_copy[0]);

    xml_node<>* svg = doc.first_node("svg");
    if (!svg) return elements;

    // Tìm node <g> bên trong <svg>
    xml_node<>* g = svg->first_node("g");
    if (!g) return elements;

    // Duyệt qua từng node con của <g>
    for (xml_node<>* node = g->first_node(); node; node = node->next_sibling()) {
        string tag = node->name();

        if (tag == "circle") {
            circle* cir = new circle();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_circle(attr->name(), attr->value(), cir);
            }
            elements.push_back(cir);
        }
        else if (tag == "rect") {
            rectangle* rect = new rectangle();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_rectangle(attr->name(), attr->value(), rect);
            }
            elements.push_back(rect);
        }
        else if (tag == "ellipse") {
            ellipse* elli = new ellipse();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_ellipse(attr->name(), attr->value(), elli);
            }
            elements.push_back(elli);
        }
        else if (tag == "line") {
            line* ln = new line();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_line(attr->name(), attr->value(), ln);
            }
            elements.push_back(ln);
        }
        else if (tag == "polygon") {
            polygon* poly = new polygon();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_polygon(attr->name(), attr->value(), poly);
            }
            elements.push_back(poly);
        }
        else if (tag == "polyline") {
            polyline* pl = new polyline();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_polyline(attr->name(), attr->value(), pl);
            }
            elements.push_back(pl);
        }
        else if (tag == "text") {
            text* txt = new text();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_text(attr->name(), attr->value(), txt);
            }
            if (node->value())
                txt->text_ = node->value();
            elements.push_back(txt);
        }
        else if (tag == "path") {
            Path* p = new Path();
            for (xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                read_path(attr->name(), attr->value(), p);
            }
            elements.push_back(p);
        }
        return elements;
    }
}
int main() {
    ifstream file("sample.svg"); // đổi tên file SVG cho đúng
    if (!file) {
        cout << "Không mở được file SVG!\n";
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();
    vector<char> xml_copy(content.begin(), content.end());
    xml_copy.push_back('\0');

    xml_document<> doc;
    try {
        doc.parse<0>(&xml_copy[0]);
    }
    catch (...) {
        cout << "Lỗi khi parse file SVG!\n";
        return 1;
    }

    xml_node<>* svg = doc.first_node("svg");
    if (!svg) {
        cout << "Không tìm thấy tag <svg>!\n";
        return 1;
    }

    xml_node<>* g = svg->first_node("g");
    if (!g) {
        cout << "Không tìm thấy tag <g> bên trong <svg>!\n";
        return 1;
    }

    cout << "Tìm thấy <svg> và <g>. Các phần tử con của <g> là:\n";
    for (xml_node<>* node = g->first_node(); node; node = node->next_sibling()) {
        cout << "- " << node->name() << "\n";
    }

    return 0;
}
