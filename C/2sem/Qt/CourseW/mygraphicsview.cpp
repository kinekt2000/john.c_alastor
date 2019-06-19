#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent):QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 256, 256);
    this->setScene(scene);

    rect = new QGraphicsItemGroup(); //Создаем пустую группу rect
    scene->addItem(rect); //Добавляем группу на сцену

    setMouseTracking(true); //Добавляем отслеживание мыши
}

MyGraphicsView::~MyGraphicsView(){
}


void MyGraphicsView::update(QPixmap pixmap){
    // Цикл проходит по всем объектам в сцене и удаляет объекты типа QGraphicsPixmapItem
    foreach(QGraphicsItem *item, scene->items())
        if(typeid(*item) == typeid(QGraphicsPixmapItem))
            scene->removeItem(item);
    scene->addPixmap(pixmap); //в сцену добавляется измененный рисунок
}


void MyGraphicsView::freeGroup(QGraphicsItemGroup *object){
    // Цикл проходит по всем объектам сцены и если они принадлежат группе object, то удаляет их со сцены
    foreach(QGraphicsItem *item, scene->items())
        if(item->group() == object)
            delete item;
}


void MyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    QPoint point = mapToScene(event->pos()).toPoint();
    emit mouse_track_signal(point.x(), point.y());

    if(mouse_p && (func == ROTATE90 || func == ROTATE180 || func == ROTATE270 || func == RECT || func == CIRC)){
        finish = {point.x(), point.y()};

        this->freeGroup(rect);
        delete rect;
        rect = new QGraphicsItemGroup;
        QPen pen(Qt::black);

        if(finish.x < 0) finish.x = 0;
        if(finish.y < 0) finish.y = 0;

        rect->addToGroup(scene->addLine(start.x, start.y, finish.x, start.y, pen));
        rect->addToGroup(scene->addLine(finish.x, start.y, finish.x, finish.y, pen));
        rect->addToGroup(scene->addLine(finish.x, finish.y, start.x, finish.y, pen));
        rect->addToGroup(scene->addLine(start.x, finish.y, start.x, start.y, pen));

        scene->addItem(rect);
    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event){
    mouse_p = 1;
    QPoint point = mapToScene(event->pos()).toPoint();
    //emit mouse_track_signal(point.x(), point.y());
    start = {point.x(), point.y()};
    finish = {point.x(), point.y()};
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent *event){
    mouse_p = 0;
    QPoint point = mapToScene(event->pos()).toPoint();
    finish = {point.x(), point.y()};
    this->freeGroup(rect);

    if(func == ROTATE90) emit rotate_signal_90(start.x, start.y, finish.x, finish.y);
    if(func == ROTATE180) emit rotate_signal_180(start.x, start.y, finish.x, finish.y);
    if(func == ROTATE270) emit rotate_signal_270(start.x, start.y, finish.x, finish.y);
    if(func == RECT) emit rect_signal(start.x, start.y, finish.x, finish.y);
    if(func == CIRC) emit circ_signal(start.x, start.y, finish.x, finish.y);
}











