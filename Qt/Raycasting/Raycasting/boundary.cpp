#include "boundary.h"

Boundary::Boundary(int x1, int x2, int y1, int y2)
{
    a = {x1, x2};
    b = {y1, y2};
}

void Boundary::show(QPainter *painter){
    painter->drawLine(a[0], a[1], b[0], b[1]);
}
