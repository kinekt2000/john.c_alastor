#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <random>


#define RSIZE 300

typedef struct Cell{
    double a = 0;
    double b = 0;
}Cell;

void swap(Cell **dest, Cell **source);


class RenderArea : public QWidget
{
    Q_OBJECT

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

public:
    int radius = 10;
    Cell **grid = nullptr;
    Cell **next = nullptr;
    double laplaceA(int x, int y);
    double laplaceB(int x, int y);
    void update();
    void imageToGrid(QImage img);
    explicit RenderArea(QWidget *parent = nullptr);

private:
    bool m_pressed = 0;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QImage *image;
    QPainter *painter;
};

#endif // RENDERAREA_H
