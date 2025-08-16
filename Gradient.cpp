//Gradient.cpp contains functions for reading and rendering gradients in detail.
#include"Gradient.h"
//read function
void readStop(const std::string& name, const std::string& value, stop& stop) {
    if (name == "stop-color") {
        stop.stop_color = read_RGB(value);
    }
    else if (name == "stop-opacity") {
        stop.stop_opacity = clarifyFloat(value);
    }
    else if (name == "offset") {
        stop.offset = clarifyFloat(value);
    }
}

void readLinearGradient(const std::string& name, const std::string& value, linearGradient& lg) {
    if (name == "id") {
        lg.id = value;
    }
    else if (name == "x1") {
        if (!value.empty() && value.back() == '%') {
            lg.percentage = true;
            lg.start.x = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else {
            lg.start.x = clarifyFloat(value);
        }
    }
    else if (name == "x2") {
        if (!value.empty() && value.back() == '%') {
            lg.end.x = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else {
            lg.end.x = clarifyFloat(value);
        }
    }
    else if (name == "y1") {
        if (!value.empty() && value.back() == '%') {
            lg.start.y = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else {
            lg.start.y = clarifyFloat(value);
        }
    }
    else if (name == "y2") {
        if (!value.empty() && value.back() == '%') {
            lg.end.y = clarifyFloat(value.substr(0, value.length() - 1));
        }
        else {
            lg.end.y = clarifyFloat(value);
        }
    }
    else if (name == "gradientTransform") {
        read_transform(value, lg.trans);
    }
    else if (name == "gradientUnits") {
        lg.units = value;
    }
}

void readRadialGradient(const std::string& name, const std::string& value, radialGradient& rg) {
    if (name == "id") {
        rg.id = value;
    }
    else if (name == "cx") {
        rg.center.x = clarifyFloat(value);
    }
    else if (name == "cy") {
        rg.center.y = clarifyFloat(value);
    }
    else if (name == "r") {
        rg.r = clarifyFloat(value);
    }
    else if (name == "xlink:href") {
        rg.xlink_href = value;
    }
    else if (name == "gradientTransform") {
        read_transform(value, rg.trans);
    }
    else if (name == "gradientUnits") {
        rg.units = value;
    }
    else if (name == "fx") {
        rg.fx = clarifyFloat(value);
    }
    else if (name == "fy") {
        rg.fy = clarifyFloat(value);
    }
}
//render gradient functions
float* Gradient::get_point_list() {
    if (stop_list.empty()) return nullptr;

    int size = stop_list.size();
    if (stop_list[0].offset != 0) {
        size++;
    }
    if (stop_list.back().offset != 1) {
        size++;
    }

    float* points = new float[size];
    int idx = 0;

    if (stop_list[0].offset != 0) {
        points[idx++] = 0;
    }

    for (int j = 0; j < stop_list.size(); j++) {
        points[idx++] = stop_list[j].offset;
    }

    if (stop_list.back().offset != 1) {
        points[idx++] = 1.0f;
    }

    return points;
}

//cast color list to Color* for render
Color* Gradient::get_color_list() {
    if (stop_list.empty()) return nullptr;

    Color* colors = new Color[stop_list.size()];
    for (int j = 0; j < stop_list.size(); j++) {
        colors[j] = Color(
            static_cast<float>(stop_list[j].stop_opacity * 255),
            stop_list[j].stop_color.red,
            stop_list[j].stop_color.green,
            stop_list[j].stop_color.blue
        );
    }
    return colors;
}
