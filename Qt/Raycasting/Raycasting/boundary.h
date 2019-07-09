#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <QPainter>
#include <vector>

class Boundary
{
public:
    std::vector<int> a;
    std::vector<int> b;

    Boundary(int, int, int, int);
    void show(QPainter *painter);
};

#endif // BOUNDARY_H
