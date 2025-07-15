

#include "Shape.h"
#include "Base.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

void read_line(string name, string value, line* line) {
    if (name == "stroke-opacity") {
        line->stroke_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            line->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            line->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            line->stroke_color = read_RGB(value);
            if (line->stroke_width == 0)
                line->stroke_width = 1;
        }
    }
    else if (name == "x1") {
        line->start.x = stof(value);
    }
    else if (name == "y1") {
        line->start.y = stof(value);
    }
    else if (name == "x2") {
        line->end.x = stof(value);
    }
    else if (name == "y2") {
        line->end.y = stof(value);
    }
    else if (name == "stroke-width") {
        line->stroke_width = stof(value);
    }
    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_line(str1, str2, line);
        }
    }
}

void read_rectangle(string name, string value, rectangle* rect) {
    if (name == "fill-opacity") {
        rect->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        rect->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            rect->fill_opacity = 0;
        }
        else if (value.find("url") != string::npos) {
            size_t start = value.find("#");
            size_t end = value.find(")");
            rect->fill_id = value.substr(start + 1, end - start - 1);
        }
        else
            rect->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            rect->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            rect->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            rect->stroke_color = read_RGB(value);
            if (rect->stroke_width == 0)
                rect->stroke_width = 1;
        }
    }
    else if (name == "x") {
        rect->start.x = stof(value);
    }
    else if (name == "y") {
        rect->start.y = stof(value);
    }
    else if (name == "width") {
        if (value[value.length() - 1] == 't')
            value = value.substr(0, value.length() - 2);
        rect->width = stof(value);
    }
    else if (name == "height") {
        if (value[value.length() - 1] == 't')
            value = value.substr(0, value.length() - 2);
        rect->height = stof(value);
    }
    else if (name == "stroke-width") {
        rect->stroke_width = stof(value);
    }
    //style
    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_rectangle(str1, str2, rect);
        }
    }
}

void read_ellipse(string name, string value, ellipse* elli) {
    if (name == "fill-opacity") {
        elli->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        elli->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            elli->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            elli->fill_id = value.substr(5, value.length() - 6);
        }
        else
            elli->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            elli->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            elli->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            elli->stroke_color = read_RGB(value);
            if (elli->stroke_width == 0)
                elli->stroke_width = 1;
        }
    }
    else if (name == "cx") {
        elli->start.x = stof(value);
    }
    else if (name == "cy") {
        elli->start.y = stof(value);
    }
    else if (name == "rx") {
        elli->rx = stof(value);
    }
    else if (name == "ry") {
        elli->ry = stof(value);
    }
    else if (name == "stroke-width") {
        elli->stroke_width = stof(value);
    }


    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_ellipse(str1, str2, elli);
        }
    }
}

void read_circle(string name, string value, circle* cir) {
    if (name == "fill-opacity") {
        cir->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        cir->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            cir->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            cir->fill_id = value.substr(5, value.length() - 6);
        }
        else
            cir->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            cir->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            cir->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            cir->stroke_color = read_RGB(value);
            if (cir->stroke_width == 0)
                cir->stroke_width = 1;
        }
    }
    else if (name == "cx") {
        cir->center.x = stof(value);
    }
    else if (name == "cy") {
        cir->center.y = stof(value);
    }
    else if (name == "r") {
        cir->r = stof(value);
    }
    else if (name == "stroke-width") {
        cir->stroke_width = stof(value);
    }


    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_circle(str1, str2, cir);
        }
    }
}

void read_polygon(string name, string value, polygon* polygon) {
    if (name == "fill-opacity") {
        polygon->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polygon->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            polygon->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polygon->fill_id = value.substr(5, value.length() - 6);
        }
        else
            polygon->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polygon->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polygon->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            polygon->stroke_color = read_RGB(value);
            if (polygon->stroke_width == 0)
                polygon->stroke_width = 1;
        }
    }
    else if (name == "stroke-width") {
        polygon->stroke_width = stof(value);
    }
    else if (name == "points") {
        polygon->p = read_points(value);
    }
    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_polygon(str1, str2, polygon);
        }
    }
}

void read_polyline(string name, string value, polyline* polyline) {
    if (name == "fill-opacity") {
        polyline->fill_opacity = stof(value);
    }
    else if (name == "stroke-opacity") {
        polyline->stroke_opacity = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            polyline->fill_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polyline->fill_id = value.substr(5, value.length() - 6);
        }
        else
            polyline->fill_color = read_RGB(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            polyline->stroke_opacity = 0;
        }
        else if (value[0] == 'u' && value[1] == 'r' && value[2] == 'l') {
            polyline->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            polyline->stroke_color = read_RGB(value);
            if (polyline->stroke_width == 0)
                polyline->stroke_width = 1;
        }
    }
    else if (name == "stroke-width") {
        polyline->stroke_width = stof(value);
    }
    else if (name == "points") {
        polyline->p = read_points(value);
    }
    else if (name == "style") {
        istringstream iss(trim(value));
        string tmp;
        while (getline(iss, tmp, ';')) {
            string str1, str2;
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                str1 = tmp.substr(0, colonPos);
                str2 = tmp.substr(colonPos + 1);
            }
            read_polyline(str1, str2, polyline);
        }
    }
}

void read_text(string name, string value, text* text) {
    name = trim(name);
    value = trim(value);

    if (name == "x") {
        text->start.x = stof(value);
    }
    else if (name == "y") {
        text->start.y = stof(value);
    }
    else if (name == "font-size") {
        text->font_size = stof(value);
    }
    else if (name == "fill") {
        if (value == "none" || value == "transparent") {
            text->fill_opacity = 0;
        }
        else if (value.find("url") == 0) {
            text->fill_id = value.substr(5, value.length() - 6);
        }
        else {
            text->fill_color = read_RGB(value);
        }
    }
    else if (name == "fill-opacity") {
        text->fill_opacity = stof(value);
    }
    else if (name == "stroke") {
        if (value == "none" || value == "transparent") {
            text->stroke_opacity = 0;
        }
        else if (value.find("url") == 0) {
            text->stroke_id = value.substr(5, value.length() - 6);
        }
        else {
            text->stroke_color = read_RGB(value);
            if (text->stroke_width == 0)
                text->stroke_width = 1;
        }
    }
    else if (name == "stroke-opacity") {
        text->stroke_opacity = stof(value);
    }
    else if (name == "font-family") {
        text->font_family = value;
    }
    else if (name == "text-anchor") {
        text->text_anchor = value;
    }
    else if (name == "style") {
        istringstream iss(value);
        string tmp;
        while (getline(iss, tmp, ';')) {
            size_t colonPos = tmp.find(':');
            if (colonPos != string::npos) {
                string key = trim(tmp.substr(0, colonPos));
                string val = trim(tmp.substr(colonPos + 1));
                read_text(key, val, text);
            }
        }
    }
}

void rectangle::draw(Graphics& graphics) {
    Pen pen(Color(stroke_opacity * 255, stroke_color.red, stroke_color.green, stroke_color.blue), stroke_width);
    SolidBrush brush(Color(fill_opacity * 255, fill_color.red, fill_color.green, fill_color.blue));
    graphics.FillRectangle(&brush, start.x, start.y, width, height);
    graphics.DrawRectangle(&pen, start.x, start.y, width, height);
};

void circle::draw(Graphics& graphics) {
    Pen pen(Color(stroke_opacity * 255, stroke_color.red, stroke_color.green, stroke_color.blue), stroke_width);
    SolidBrush brush(Color(fill_opacity * 255, fill_color.red, fill_color.green, fill_color.blue));
    graphics.FillEllipse(&brush, center.x - r, center.y - r, 2 * r, 2 * r);
    graphics.DrawEllipse(&pen, center.x - r, center.y - r, 2 * r, 2 * r);
}

void line::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
}

void ellipse::draw(Graphics& graphics) {
    Pen pen(Color(stroke_opacity * 255, stroke_color.red, stroke_color.green, stroke_color.blue), stroke_width);
    SolidBrush brush(Color(fill_opacity * 255, fill_color.red, fill_color.green, fill_color.blue));
    graphics.FillEllipse(&brush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
    graphics.DrawEllipse(&pen, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
}

void polygon::draw(Graphics& graphics) {
    if (p.empty()) return;

    Pen pen(Color(stroke_opacity * 255, stroke_color.red, stroke_color.green, stroke_color.blue), stroke_width);
    SolidBrush brush(Color(fill_opacity * 255, fill_color.red, fill_color.green, fill_color.blue));

    vector<PointF> points;
    for (auto& pt : p)
        points.push_back(PointF(pt.x, pt.y));

    graphics.FillPolygon(&brush, points.data(), points.size());
    graphics.DrawPolygon(&pen, points.data(), points.size());
}

void polyline::draw(Graphics& graphics) {
  
    if (p.empty()) return;

    // Cá» tÃ´ mÃ u xanh nÆ°á»›c biá»ƒn
    SolidBrush fillBrush(Color(255, 0, 255, 255)); // Alpha 255 = khÃ´ng má»

    // Chuyá»ƒn cÃ¡c Ä‘iá»ƒm tá»« p sang PointF
    std::vector<PointF> points;
    for (auto& pt : p)
        points.push_back(PointF(pt.x, pt.y));

    // TÃ´ bÃªn trong polygon báº±ng mÃ u xanh nÆ°á»›c biá»ƒn
    graphics.FillPolygon(&fillBrush, points.data(), points.size());

}





void text::draw(Graphics& graphics) {
    if (text_.empty()) return;

    FontFamily fontFam(L"Arial"); // báº¡n cÃ³ thá»ƒ custom font_family náº¿u cáº§n
    FontStyle style = italic ? FontStyleItalic : FontStyleRegular;
    Font font(&fontFam, font_size, style, UnitPixel);

    SolidBrush brush(Color(fill_opacity * 255, fill_color.red, fill_color.green, fill_color.blue));

    // Chuyá»ƒn string -> wstring Ä‘á»ƒ GDI+ dÃ¹ng
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring wtext = converter.from_bytes(text_);

    PointF point(start.x + dx, start.y + dy);
    graphics.DrawString(wtext.c_str(), -1, &font, point, &brush);
}
