//Shapes_Render.cpp contains the definitions of the methods of Shape class hierarchy to render the shapes on the graphics object.
#include"Shapes.h"
//in terms of holding Gradient, all the information of radial gradient is passed as linear gradient to process
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void rectangle::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    int index = 0;
    //apply transformations
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }

    graphics.FillRectangle(&fillBrush, start.x, start.y, width, height);

    if (stroke_width != 0)
        graphics.DrawRectangle(&pen, start.x, start.y, width, height);
    graphics.Restore(save);
}

void circle::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }

    graphics.FillEllipse(&fillBrush, start.x - r, start.y - r, 2 * r, 2 * r);

    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - r, start.y - r, 2 * r, 2 * r);
    graphics.Restore(save);
}

void line::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }
    graphics.DrawLine(&pen, start.x, start.y, end.x, end.y);
    graphics.Restore(save);
}

void ellipse::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }

    graphics.FillEllipse(&fillBrush, start.x - rx, start.y - ry, 2 * rx, 2 * ry);

    if (stroke_width != 0)
        graphics.DrawEllipse(&pen, start.x - rx, start.y - ry, 2 * rx, 2 * ry);
    graphics.Restore(save);
}


void polygon::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }

    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);

    if (stroke_width != 0)
        graphics.DrawPolygon(&pen, point, static_cast<int>(p.size()));
    delete[] point;
    graphics.Restore(save);
}

void polyline::draw(Graphics& graphics) {

    GraphicsState save = graphics.Save();
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }
    Point* point = new Point[p.size()];
    for (int i = 0; i < p.size(); i++) {
        point[i] = Point(p[i].x, p[i].y);
    }
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));

    graphics.FillPolygon(&fillBrush, point, static_cast<int>(p.size()), FillModeWinding);

    if (stroke_width != 0)
        graphics.DrawLines(&pen, point, static_cast<int>(p.size()));
    delete[] point;
    graphics.Restore(save);
}


void text::draw(Graphics& graphics) {
    for (int i = 0; i < text_.length(); i++) {
        if (text_[i] == '\n') {
            text_[i] = ' ';
        }
        if (text_[i] == ' ' && text_[i + 1] == ' ') {
            text_.erase(i, 1);
            i--;
        }
    }
    float rate = 0;
    GraphicsState save = graphics.Save();
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    wstring wFontFamily = converter.from_bytes(font_family);

    FontFamily fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, static_cast<REAL>(font_size), italic ? FontStyleItalic : FontStyleRegular, UnitPixel);

    StringFormat stringFormat; // Create a StringFormat object with the each line of text, and the block
    if (text_anchor == "middle") {
        stringFormat.SetAlignment(StringAlignmentCenter); // Center alignment
    }
    else if (text_anchor == "end") {
        stringFormat.SetAlignment(StringAlignmentFar); // Right and center alignment
        rate = 0.15;
    }
    else
    {
        stringFormat.SetAlignment(StringAlignmentNear); // Left and center alignment
        rate = -0.15;
    }
    PointF pointF(static_cast<REAL>(start.x + dx + rate * font_size), static_cast<REAL>(start.y + dy - 0.9 * font_size));
    // Create a GraphicsPath
    GraphicsPath path;

    // Add the string to the path
    const wstring wstr = wstring(text_.begin(), text_.end());
    path.AddString(wstr.c_str(), -1, &fontFamily, italic ? FontStyleItalic : FontStyleRegular, static_cast<REAL>(font_size), pointF, &stringFormat);

    // Create a solid brush for filling
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    // Fill the path with the solid brush
    graphics.FillPath(&fillBrush, &path);
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}
VOID  Path::draw(Graphics& graphics) {
    GraphicsState save = graphics.Save();
    SolidBrush fillBrush(Color(static_cast<int>(fill_opacity * 255), fill_color.red, fill_color.green, fill_color.blue));
    Pen pen(Color(static_cast<int>(stroke_opacity * 255), stroke_color.red, stroke_color.green, stroke_color.blue), static_cast<REAL>(stroke_width));
    int index = 0;
    for (int i = 0; i < trans.types.size(); i++) {
        if (trans.types[i] == "translate")
            graphics.TranslateTransform(trans.values[index], trans.values[index + 1]);
        if (trans.types[i] == "rotate")
            graphics.RotateTransform(trans.values[index]);
        if (trans.types[i] == "scale")
            graphics.ScaleTransform(trans.values[index], trans.values[index + 1]);
        index += 2;
        if (trans.types[i] == "rotate")
            index--;
    }
    GraphicsPath path;
    point current_point;
    point start_point;
    point d1, d2, d, d3, r;
    bool first_point = true;
    index = 0;
    float single_type;
    char last_command = ' ';
    while (index < data.length()) {
        if (data[index] == 'z' || data[index] == 'Z') {
            index++;
            path.CloseFigure();
            current_point = start_point;  // Need to return to the starting point to close the shape
            last_command = 'z';
            continue;
        }

        else if (data[index] == 'a') {
        command_a:
            read_single_point(data, index, r);
            float rotation = read_single_point(data, ++index);
            float large_arc = read_single_point(data, ++index);
            float sweep = read_single_point(data, ++index);
            read_single_point(data, ++index, d);
            d.x += current_point.x;
            d.y += current_point.y;

            float angle = rotation * M_PI / 180.0f;
            float cos_angle = cos(angle);
            float sin_angle = sin(angle);

            float dx2 = (current_point.x - d.x) / 2.0f;
            float dy2 = (current_point.y - d.y) / 2.0f;

            float x1p = cos_angle * dx2 + sin_angle * dy2;
            float y1p = -sin_angle * dx2 + cos_angle * dy2;

            float rx_sq = r.x * r.x;
            float ry_sq = r.y * r.y;
            float x1p_sq = x1p * x1p;
            float y1p_sq = y1p * y1p;

            float radicant = (rx_sq * ry_sq - rx_sq * y1p_sq - ry_sq * x1p_sq) / (rx_sq * y1p_sq + ry_sq * x1p_sq);
            if (radicant < 0) radicant = 0;
            float coef = ((large_arc != sweep) ? 1 : -1) * sqrt(radicant);

            float cxp = coef * ((r.x * y1p) / r.y);
            float cyp = coef * ((-r.y * x1p) / r.x);

            float cx = cos_angle * cxp - sin_angle * cyp + (current_point.x + d.x) / 2.0f;
            float cy = sin_angle * cxp + cos_angle * cyp + (current_point.y + d.y) / 2.0f;

            float start_angle = atan2((y1p - cyp) / r.y, (x1p - cxp) / r.x);
            float end_angle = atan2((-y1p - cyp) / r.y, (-x1p - cxp) / r.x);
            float delta_angle = end_angle - start_angle;

            if (!sweep && delta_angle > 0) delta_angle -= 2 * M_PI;
            else if (sweep && delta_angle < 0) delta_angle += 2 * M_PI;

            float start_deg = start_angle * 180.0f / M_PI;
            float delta_deg = delta_angle * 180.0f / M_PI;

            if (isnan(cx) || isnan(cy) || isnan(start_deg) || isnan(delta_deg)) {
                path.AddLine(current_point.x, current_point.y, d.x, d.y);
            }
            else {
                path.AddArc(cx - r.x, cy - r.y, 2 * r.x, 2 * r.y, start_deg, delta_deg);
            }

            current_point = d;
            last_command = 'a';
        }

        // command A – absolute arc
        else if (data[index] == 'A') {
        command_A:
            read_single_point(data, index, r);
            float rotation = read_single_point(data, ++index);
            float large_arc = read_single_point(data, ++index);
            float sweep = read_single_point(data, ++index);
            read_single_point(data, ++index, d);

            float angle = rotation * M_PI / 180.0f;
            float cos_angle = cos(angle);
            float sin_angle = sin(angle);

            float dx2 = (current_point.x - d.x) / 2.0f;
            float dy2 = (current_point.y - d.y) / 2.0f;

            float x1p = cos_angle * dx2 + sin_angle * dy2;
            float y1p = -sin_angle * dx2 + cos_angle * dy2;

            float rx_sq = r.x * r.x;
            float ry_sq = r.y * r.y;
            float x1p_sq = x1p * x1p;
            float y1p_sq = y1p * y1p;

            float radicant = (rx_sq * ry_sq - rx_sq * y1p_sq - ry_sq * x1p_sq) / (rx_sq * y1p_sq + ry_sq * x1p_sq);
            if (radicant < 0) radicant = 0;
            float coef = ((large_arc != sweep) ? 1 : -1) * sqrt(radicant);

            float cxp = coef * ((r.x * y1p) / r.y);
            float cyp = coef * ((-r.y * x1p) / r.x);

            float cx = cos_angle * cxp - sin_angle * cyp + (current_point.x + d.x) / 2.0f;
            float cy = sin_angle * cxp + cos_angle * cyp + (current_point.y + d.y) / 2.0f;

            float start_angle = atan2((y1p - cyp) / r.y, (x1p - cxp) / r.x);
            float end_angle = atan2((-y1p - cyp) / r.y, (-x1p - cxp) / r.x);
            float delta_angle = end_angle - start_angle;

            if (!sweep && delta_angle > 0) delta_angle -= 2 * M_PI;
            else if (sweep && delta_angle < 0) delta_angle += 2 * M_PI;

            float start_deg = start_angle * 180.0f / M_PI;
            float delta_deg = delta_angle * 180.0f / M_PI;

            if (isnan(cx) || isnan(cy) || isnan(start_deg) || isnan(delta_deg)) {
                path.AddLine(current_point.x, current_point.y, d.x, d.y);
            }
            else {
                path.AddArc(cx - r.x, cy - r.y, 2 * r.x, 2 * r.y, start_deg, delta_deg);
            }

            current_point = d;
            last_command = 'A';
        }

        else if (data[index] == 'q') {
        command_q:
            read_single_point(data, index, d1);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'q';
        }
        else if (data[index] == 'Q') {
        command_Q:
            read_single_point(data, index, d1);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d1.x, d1.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'Q';
        }
        else if (data[index] == 's') {
        command_s:
            read_single_point(data, index, d3);
            read_single_point(data, index, d);
            if (last_command == 'c' || last_command == 'C') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else if (last_command == 's' || last_command == 'S') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else {
                d1.x = current_point.x;
                d1.y = current_point.y;
            }
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, current_point.x + d3.x, current_point.y + d3.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            d2.x = d3.x + current_point.x;
            d2.y = d3.y + current_point.y;
            last_command = 's';
        }
        else if (data[index] == 'S') {
        command_S:
            read_single_point(data, index, d3);
            read_single_point(data, index, d);
            if (last_command == 'c' || last_command == 'C') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else if (last_command == 's' || last_command == 'S') {
                d1.x = 2 * current_point.x - d2.x;
                d1.y = 2 * current_point.y - d2.y;
            }
            else {
                d1.x = current_point.x;
                d1.y = current_point.y;
            }
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d3.x, d3.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            d2.x = d3.x;
            d2.y = d3.y;
            last_command = 'S';
        }
        else if (data[index] == 'm') {
            read_single_point(data, index, d);
            if (first_point) {
                first_point = false;
                start_point.x = d.x, start_point.y = d.y;
                current_point.x = d.x, current_point.y = d.y;
                path.StartFigure();

                last_command = 'm';
            }
            else {
                current_point.x += d.x;
                current_point.y += d.y;

                last_command = 'm';
            }
        }
        else if (data[index] == 'M') {
            read_single_point(data, index, d);
            if (first_point) {
                first_point = false;
                start_point.x = d.x, start_point.y = d.y;
                current_point.x = d.x, current_point.y = d.y;
                path.StartFigure();
                last_command = 'M';
            }
            else {
                current_point.x = d.x;
                current_point.y = d.y;
                last_command = 'M';
            }
        }
        else if (data[index] == 'l') {
        command_l:
            read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'l';
        }
        else if (data[index] == 'L') {
        command_L:
            read_single_point(data, index, d);
            path.AddLine(current_point.x, current_point.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'L';
        }
        else if (data[index] == 'h') {
        command_h:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x + single_type, current_point.y);
            current_point.x += single_type;
            last_command = 'h';
        }
        else if (data[index] == 'H') {
        command_H:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, single_type, current_point.y);
            current_point.x = single_type;
            last_command = 'H';
        }
        else if (data[index] == 'v') {
        command_v:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, current_point.y + single_type);
            current_point.y += single_type;
            last_command = 'v';
        }
        else if (data[index] == 'V') {
        command_V:
            single_type = read_single_point(data, index);
            path.AddLine(current_point.x, current_point.y, current_point.x, single_type);
            current_point.y = single_type;
            last_command = 'V';
        }
        else if (data[index] == 'c') {
        command_c:
            read_single_point(data, index, d1);
            read_single_point(data, index, d2);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, current_point.x + d1.x, current_point.y + d1.y, current_point.x + d2.x, current_point.y + d2.y, current_point.x + d.x, current_point.y + d.y);
            d2.x += current_point.x;
            d2.y += current_point.y;
            current_point.x += d.x;
            current_point.y += d.y;
            last_command = 'c';
        }
        else if (data[index] == 'C') {
        command_C:
            read_single_point(data, index, d1);
            read_single_point(data, index, d2);
            read_single_point(data, index, d);
            path.AddBezier(current_point.x, current_point.y, d1.x, d1.y, d2.x, d2.y, d.x, d.y);
            current_point.x = d.x;
            current_point.y = d.y;
            last_command = 'C';
        }
        else if (data[index] <= '9' && data[index] >= '0' || data[index] == '.') {
            switch (last_command) {
            case 'm':
                read_single_point(data, index, d);
                path.AddLine(current_point.x, current_point.y, current_point.x + d.x, current_point.y + d.y);
                current_point.x += d.x;
                current_point.y += d.y;
                break;

            case 'M':
                read_single_point(data, index, d);
                path.AddLine(current_point.x, current_point.y, d.x, d.y);
                current_point.x = d.x;
                current_point.y = d.y;
                break;
            case 'c':
                goto command_c;
                break;
            case 'C':
                goto command_C;
                break;
            case 'L':
                goto command_L;
            case 'l':
                goto command_l;
                break;
            case 'h':
                goto command_h;
                break;
            case 'H':
                goto command_H;
                break;
            case 'v':
                goto command_v;
                break;
            case 'V':
                goto command_V;
                break;
            case 's':
                goto command_s;
                break;
            case 'S':
                goto command_S;
                break;
            case 'q':
                goto command_q;
                break;
            case 'Q':
                goto command_Q;
                break;
            case 'a':
                goto command_a;
                break;
            case 'A':
                goto command_A;
                break;
            }
        }
        else {
            index++;
        }
    }

    if (linecap == "round") {
        pen.SetStartCap(LineCapRound);
        pen.SetEndCap(LineCapRound);
    }
    else if (linecap == "square") {
        pen.SetStartCap(LineCapSquare);
        pen.SetEndCap(LineCapSquare);
    }
    else {
        pen.SetStartCap(LineCapFlat);
        pen.SetEndCap(LineCapFlat);
    }
    if (linejoin == "round") {
        pen.SetLineJoin(LineJoinRound);
    }
    else if (linejoin == "bevel") {
        pen.SetLineJoin(LineJoinBevel);
    }
    else {
        pen.SetLineJoin(LineJoinMiter);
    }

Draw:
    if (stroke_width != 0)
        graphics.DrawPath(&pen, &path);
    graphics.Restore(save);
}




