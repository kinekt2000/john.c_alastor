#ifndef RAY_H
#define RAY_H

#include <QPainter>
#include <vector>
#include <cmath>
#include "boundary.h"

#define TWO_PI 6.28318530718

class Ray
{
public:
    std::vector<int> pos;
    std::vector<double> dir;

    Ray(int x, int y, double angle);
    void lookAt(int x, int y);
    void show(QPainter *painter);
    std::vector<int> cast(QPainter *painter, Boundary wall);
};

#endif // RAY_H
