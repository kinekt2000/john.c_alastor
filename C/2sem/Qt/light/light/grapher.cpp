#include <QDebug>
#include "grapher.h"

Grapher::Grapher(QWidget *parent):QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene = new QGraphicsScene();
    this->setScene(scene);

    object = new QGraphicsItemGroup();
    hexagon = new QGraphicsItemGroup();
    scene->addItem(object);
    scene->addItem(hexagon);

    setMouseTracking(true);
}
Grapher::~Grapher(){}


void Grapher::update(QPixmap pixmap){
    foreach(QGraphicsItem *item, scene->items())
        if(typeid(*item) == typeid(QGraphicsPixmapItem))
            scene->removeItem(item);

    scene->addPixmap(pixmap);
}


void Grapher::freeGroup(QGraphicsItemGroup* object){
    foreach(QGraphicsItem *item, scene->items())
        if (item->group() == object)
            delete item;
}


void Grapher::mousePressEvent(QMouseEvent *event){
    radius = 0;
    angle = 0;
    QPoint point = mapToScene(event->pos()).toPoint();
    emit mouse_track_signal(point.x(), point.y());
    drawer = true;

    if (copy){
        copy = 0;
        emit copy_signal(start.x, start.y, finish.x, finish.y, point.x(), point.y());
        drawer = false;
    }

    start.x = point.x();
    start.y = point.y();
    finish.x = point.x();
    finish.y = point.y();
}


void Grapher::mouseMoveEvent(QMouseEvent *event){
    QPoint point = mapToScene(event->pos()).toPoint();
    emit mouse_track_signal(point.x(), point.y());

    if (drawer == true && func == PEN){
        finish.y = point.y();
        finish.x = point.x();
        emit pen_signal();
        start.x = finish.x;
        start.y = finish.y;
    }
    else if (drawer == true && (func == COPY || func == RECOLOR)){
        finish.y = point.y();
        finish.x = point.x();

        this->freeGroup(object);
        delete object;
        object = new QGraphicsItemGroup;

        QPen pen(Qt::black);
        if(finish.x < 0) finish.x = 0;
        if(finish.y < 0) finish.y = 0;

        object->addToGroup(scene->addLine(start.x, start.y, finish.x, start.y, pen));
        object->addToGroup(scene->addLine(finish.x, start.y, finish.x, finish.y, pen));
        object->addToGroup(scene->addLine(finish.x, finish.y, start.x, finish.y, pen));
        object->addToGroup(scene->addLine(start.x, finish.y, start.x, start.y, pen));

        scene->addItem(object);
    }
    else if (drawer == true && func == HEXAGON){
        finish.x = point.x();
        finish.y = point.y();

        this->freeGroup(hexagon);
        delete hexagon;
        hexagon = new QGraphicsItemGroup;

        QPen pen(Qt::black);
        radius = sqrt((finish.x - start.x)*(finish.x - start.x) + (finish.y - start.y)*(finish.y - start.y));
        angle = acos((finish.x - start.x)/radius);
        if (finish.y < start.y) angle *= -1;

        int s_node_x = finish.x;
        int s_node_y = finish.y;
        int f_node_x;
        int f_node_y;
        for(int i = 1; i <= 6; i++){
            f_node_x = static_cast<int>(start.x + round(radius*cos(PI/3*i + angle)));
            f_node_y = static_cast<int>(start.y + round(radius*sin(PI/3*i + angle)));
            hexagon->addToGroup(scene->addLine(s_node_x, s_node_y, f_node_x, f_node_y, pen));
            s_node_x = f_node_x;
            s_node_y = f_node_y;
        }
        scene->addItem(hexagon);
    }
}


void Grapher::mouseReleaseEvent(QMouseEvent *event){
    if(func == COPY && finish.x - start.x && finish.y - start.y) copy = 1;

    QPoint point = mapToScene(event->pos()).toPoint();
    finish.x = point.x();
    finish.y = point.y();

    this->freeGroup(object);
    this->freeGroup(hexagon);
    drawer = false;

    if(func == PEN) emit pen_signal();
    if(func == RECOLOR) emit square_signal(start.x, start.y, finish.x, finish.y);
    if(func == HEXAGON) emit hexagon_signal(start.x, start.y, radius, angle);
}



















