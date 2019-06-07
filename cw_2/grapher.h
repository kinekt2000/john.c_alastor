#ifndef GRAPHER_H
#define GRAPHER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QPoint>
#include <cmath>

#define PI 3.14159265359

#define OFF 0
#define PEN 1
#define COPY 2
#define RECOLOR 3
#define HEXAGON 4

typedef struct coordinate{
    int x;
    int y;
} coordinate;

class Grapher : public QGraphicsView
{

    Q_OBJECT

public:
    QGraphicsScene *scene;
    coordinate start;
    coordinate finish;
    int func = OFF;
    int copy = 0;
    void update(QPixmap);
    explicit Grapher(QWidget *Parent = nullptr);
    ~Grapher();

signals:
    void mouse_track_signal(int x, int y);
    void pen_signal();
    void square_signal(int sx, int sy, int fx, int fy);
    void copy_signal(int sx, int sy, int fx, int fy, int nx, int ny);
    void hexagon_signal(int sx, int sy, double radius, double angle);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QGraphicsItemGroup *object;

    QGraphicsItemGroup *hexagon;
    double radius;
    double angle;

    QPixmap pixmap;
    bool drawer = false;
    void freeGroup(QGraphicsItemGroup *object);
};

#endif // GRAPHER_H
