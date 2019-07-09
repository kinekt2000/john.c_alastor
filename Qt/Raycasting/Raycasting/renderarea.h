#ifndef RENDERAREA_H
#define RENDERAREA_H


#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <random>

#include "particle.h"
#include "boundary.h"
#include "ray.h"


#define RSIZE 600
#define VWALL 20
#define WCOUNT 5

class RenderArea : public QGraphicsView
{

    Q_OBJECT

private slots:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void draw();

public:
    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

private:
    std::vector<int> start{0, 0};
    std::vector<int> finish{0, 0};
    bool m_pressed;

    std::vector<double> *screen;
    std::vector<Boundary> *walls;
    Particle *particle;

    QGraphicsScene *scene;
    QImage *image;
    QPainter *painter;
    void setup();
    void update();
};

#endif // RENDERAREA_H
