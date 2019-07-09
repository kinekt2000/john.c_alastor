#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    image = new QImage(QSize(RSIZE, RSIZE), QImage::Format_RGB666);
    scene->addPixmap(QPixmap::fromImage(*image));
    painter = new QPainter();
    painter->begin(image);
    setScene(scene);

    setup();

    setMouseTracking(true);
}


RenderArea::~RenderArea(){
    painter->end();
    delete scene;
    delete image;
    delete painter;
}


void RenderArea::update(){
    foreach(QGraphicsItem *item, scene->items()){
        scene->removeItem(item);
        delete item;
    }

    scene->addPixmap(QPixmap::fromImage(*image));
}


void RenderArea::mouseMoveEvent(QMouseEvent *event){
//    qDebug() << event->x() << event->y();
}


void RenderArea::setup(){
}


void RenderArea::draw(){
    painter->fillRect(image->rect(), QBrush(Qt::white));
    painter->setPen(Qt::red);
    painter->drawLine(100, 100, 100, 300);
    update();
}
