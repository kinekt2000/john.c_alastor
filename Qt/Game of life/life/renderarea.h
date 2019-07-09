#ifndef RENDERAREA_H
#define RENDERAREA_H


#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <random>


//#define RSIZE 600

#define WIDTH 50
#define HEIGHT 50
#define CSIZE 15

#define WSIZE ( (WIDTH + 1) + CSIZE * WIDTH )
#define HSIZE ( (HEIGHT + 1) + CSIZE * HEIGHT )

class RenderArea : public QGraphicsView
{

    Q_OBJECT

private slots:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void draw();

public:
    void clean();
    explicit RenderArea(QWidget *parent = nullptr);
    ~RenderArea();

private:
    bool m_pressed = 0;

    bool **grid;
    bool **next;
    void swap();

    QGraphicsScene *scene;
    QImage *image;
    QPainter *painter;
    void setup();
    void update();
};

#endif // RENDERAREA_H
