#include "renderarea.h"
#include <QDebug>

void swap(Cell **first, Cell **second){
    Cell **tmp = new Cell*[RSIZE];
    for(int x = 0; x < RSIZE; x++){
        tmp[x] = new Cell[RSIZE];
        for(int y = 0; y < RSIZE; y++){
            tmp[x][y].a = first[x][y].a;
            tmp[x][y].b = first[x][y].b;
        }
    }

    for(int x = 0; x < RSIZE; x++)
        for(int y = 0; y < RSIZE; y++){
            first[x][y].a = second[x][y].a;
            first[x][y].b = second[x][y].b;
        }

    for(int x = 0; x < RSIZE; x++)
        for(int y = 0; y < RSIZE; y++){
            second[x][y].a = tmp[x][y].a;
            second[x][y].b = tmp[x][y].b;
        }

    for(int i = 0; i < RSIZE; i++)
        delete [] tmp[i];
    delete [] tmp;
}

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene, this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    image = new QImage(RSIZE, RSIZE, QImage::Format_RGB666);

    grid = new Cell*[RSIZE];
    next = new Cell*[RSIZE];
    for(int x = 0; x < RSIZE; x++){
        grid[x] = new Cell[RSIZE];
        next[x] = new Cell[RSIZE];
        for(int y = 0; y < RSIZE; y++){
            grid[x][y].a = 1;
            grid[x][y].b = 0;

            next[x][y].a = 1;
            next[x][y].b = 0;
        }
    }

//    for(int x = RSIZE/2 - 10; x <= RSIZE/2+10; x++)
//        for(int y = RSIZE/2 - 10; y <= RSIZE/2 + 10; y++)
//            grid[x][y].b = 1;

    view->resize(RSIZE+2, RSIZE+2);
    this->setMouseTracking(true);
    view->setMouseTracking(true);
}

void RenderArea::update(){
    for(int i = 0; i < RSIZE; i++)
        for(int j = 0; j < RSIZE; j++){
            double a = grid[i][j].a;
            double b = grid[i][j].b;
            int c = int(floor((a-b)*255));

            if (c < 0) c = 0;
            if (c > 255) c = 255;

            image->setPixel(i, j, QColor(c, c, c).rgb());
        }

    foreach(QGraphicsItem *item, scene->items()){
        if(typeid(*item) == typeid(QGraphicsPixmapItem))
            scene->removeItem(item);
        delete item;
    }

    scene->addPixmap(QPixmap::fromImage(*image));
}


double RenderArea::laplaceA(int x, int y){
    double sum = 0;
    sum += grid[x][y].a*(-1);
    sum += grid[x-1][y].a*(0.2);
    sum += grid[x+1][y].a*(0.2);
    sum += grid[x][y-1].a*(0.2);
    sum += grid[x][y+1].a*(0.2);
    sum += grid[x-1][y-1].a*(0.05);
    sum += grid[x-1][y+1].a*(0.05);
    sum += grid[x+1][y-1].a*(0.05);
    sum += grid[x+1][y+1].a*(0.05);

    return sum;
}


double RenderArea::laplaceB(int x, int y){
    double sum = 0;
    sum += grid[x][y].b*(-1);
    sum += grid[x-1][y].b*(0.2);
    sum += grid[x+1][y].b*(0.2);
    sum += grid[x][y-1].b*(0.2);
    sum += grid[x][y+1].b*(0.2);
    sum += grid[x-1][y-1].b*(0.05);
    sum += grid[x-1][y+1].b*(0.05);
    sum += grid[x+1][y-1].b*(0.05);
    sum += grid[x+1][y+1].b*(0.05);

    return sum;
}


void RenderArea::imageToGrid(QImage img){
    for(int x = 0; x < RSIZE; x++)
        for(int y = 0; y < RSIZE; y++){
            grid[x][y].b = (255 - qRed(img.pixel(x,y)) + 255 - qGreen(img.pixel(x, y)) + 255 - qBlue(img.pixel(x, y)))/3.0/255.0;
            next[x][y].b = (255 - qRed(img.pixel(x,y)) + 255 - qGreen(img.pixel(x, y)) + 255 - qBlue(img.pixel(x, y)))/3.0/255.0;
        }
    update();
}


void RenderArea::mouseMoveEvent(QMouseEvent *e){
    qDebug() << e->x() << e->y();
}

void RenderArea::mousePressEvent(QMouseEvent *e){
    int Rpow2 = radius*radius;
    for(int x = -radius; x < radius; x++)
        for(int y = -radius; y < radius; y++)
            if(x*x + y*y < Rpow2    &&
               e->x()-x > 0         && e->y()-y > 0         &&
               e->x()-x < RSIZE - 1 && e->y()-y < RSIZE - 1)
                grid[e->x()-x][e->y()-y].b = 1;
    update();
}

//void QGraphicsView::mouseMoveEvent(QMouseEvent *event){
//    qDebug() << "move";
//}




