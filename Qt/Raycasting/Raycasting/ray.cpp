#include "ray.h"
#include <QDebug>

Ray::Ray(int x, int y, double angle)
{
    pos = {x, y};
    dir = {cos(TWO_PI*angle/360), sin(TWO_PI*angle/360)};
}


void Ray::lookAt(int x, int y){
    dir[0] = x - pos[0];
    dir[1] = y - pos[1];

    double r = sqrt(dir[0]*dir[0] + dir[1]*dir[1]);
    dir[0] /= r;
    dir[1] /= r;
}


void Ray::show(QPainter *painter){
    painter->translate(pos[0], pos[1]);
    painter->drawLine(0, 0, int(dir[0]*10), int(dir[1]*10));
    painter->resetTransform();
}


std::vector<int> Ray::cast(QPainter *painter, Boundary wall){
    int x1 = wall.a[0];
    int y1 = wall.a[1];
    int x2 = wall.b[0];
    int y2 = wall.b[1];

    int x3 = pos[0];
    int y3 = pos[1];
    double x4 = x3 + dir[0];
    double y4 = y3 + dir[1];

    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    //qDebug() << den;

    if (abs(den - 1e-10) < 0) return {};

    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

//    qDebug() << t << u;

    if(t > 0 && t < 1 && u > 0){
        std::vector<int> pt;
        pt.push_back(x1 + int(t*(x2 - x1)));
        pt.push_back(y1 + int(t*(y2 - y1)));
        return pt;
    }
    else
        return {};
}
