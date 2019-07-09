#include "particle.h"
#include <QDebug>


Particle::Particle(std::vector<int> pos_)
{
    pos = pos_;
    rays = new std::vector<Ray>;
    //double d = 360.0/RCNT; // angle changing
    //double i;
    for(int i = -30; i < 30; i++){
        if (i > 360) i = 360;
        rays->push_back(Ray(pos[0], pos[1], i));
    }
}


Particle::~Particle(){
    delete rays;
}


void Particle::rotate(double angle){
    this->angle += angle;
    if (this->angle > 360 || this->angle < -360) this->angle = 0;
    //double d = 360.0/RCNT;
    //double i;
    rays->clear();
    for(int i = -30; i < 30; i++){
        rays->push_back(Ray(pos[0], pos[1], i + this->angle));
    }
    //qDebug() << (*rays)[30].dir[0] << (*rays)[30].dir[1];
}


void Particle::move(double len){
    std::vector<double> vec = {len*cos(TWO_PI*angle/360), len*sin(TWO_PI*angle/360)};
    pos[0] += vec[0];
    pos[1] += vec[1];

    qDebug() << vec[0] << vec[1];
    qDebug() << (*rays)[30].dir[0] << (*rays)[30].dir[1];

    update(pos[0], pos[1]);
}


void Particle::show(QPainter *painter){
    painter->drawEllipse(QPoint(pos[0], pos[1]), 1, 1);
    for(auto ray: *rays){
        ray.show(painter);
    }
}


void Particle::update(int x, int y){
    rays->cbegin();
    for(size_t i = 0; i < rays->size(); i++){
        (*rays)[i].pos = {x, y};
    }
    pos = {x, y};
}


std::vector<double> Particle::look(QPainter *painter, std::vector<Boundary> *walls){
    std::vector<double> screen;
    for(auto ray: *rays){
        std::vector<int> closest = {};
        double record = std::numeric_limits<double>::infinity();
        for(auto wall: *walls){
            auto pt = ray.cast(painter, wall);

            if (!pt.empty()){
                double d = sqrt((pos[0] - pt[0])*(pos[0] - pt[0]) + (pos[1] - pt[1])*(pos[1] - pt[1]));
                double a = acos(ray.dir[0]) - angle;
                d *= cos(a);
                if(d < record){
                    record = d;
                    closest = pt;
                }
            }
        }
        if(!closest.empty())
            painter->drawLine(pos[0], pos[1], closest[0], closest[1]);

        screen.push_back(record);
    }
    return screen;
}
