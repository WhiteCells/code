#include "color_pen.h"
#include "pen_type.h"

int main(int argc, char *argv[]) {
    PenType *pen_type = new SmallPen();
    ColorPen *red_pen = new RedPen(pen_type);
    red_pen->write("hello");

    delete pen_type;
    delete red_pen;
    return 0;
}