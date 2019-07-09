#ifndef RENDERAREA_H
#define RENDERAREA_H


#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>


#define RSIZE 600

class RenderArea : public QGraphicsView
{

    Q_OBJECT

private slots:
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void draw();

public:
    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

private:
    QGraphicsScene *scene;
    QImage *image;
    QPainter *painter;
    void setup();
    void update();
};

#endif // RENDERAREA_H
