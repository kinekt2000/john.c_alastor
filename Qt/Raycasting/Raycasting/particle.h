#ifndef PARTICLE_H
#define PARTICLE_H

#include "ray.h"
#include <QPainter>

#define RCNT 360;

class Particle
{

private:
    std::vector<int> pos;
    std::vector<Ray> *rays;
    int angle = 0;


public:
    void show(QPainter *painter);
    void update(int x, int y);
    std::vector<double> look(QPainter *painter, std::vector<Boundary>* walls);
    void rotate(double angle);
    void move(double len);

    Particle(std::vector<int> pos_);
    ~Particle();
};

#endif // PARTICLE_H
