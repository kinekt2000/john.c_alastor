#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    image = new QImage(QSize(WSIZE, HSIZE), QImage::Format_RGB666);
    scene->addPixmap(QPixmap::fromImage(*image));
    painter = new QPainter();
    painter->begin(image);
    setScene(scene);

    setup();
    draw();

    setMouseTracking(true);
}


RenderArea::~RenderArea(){
    for(int x = 0; x < WIDTH; x++){
        delete [] next[x];
        delete [] grid[x];
    }
    delete [] next;
    delete [] grid;


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


void RenderArea::clean(){
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            grid[x][y] = 0;
            next[x][y] = 0;
        }
    }
    draw();
}


void RenderArea::swap(){
    bool **tmp = new bool*[WIDTH];
    for(int x = 0; x < WIDTH; x++){
        tmp[x] = new bool[HEIGHT];
        for(int y = 0; y < HEIGHT; y++){
            tmp[x][y] = grid[x][y];
            grid[x][y] = next[x][y];
            next[x][y] = tmp[x][y];
        }
    }

    for(int x = 0; x < WIDTH; x++)
        delete [] tmp[x];
    delete [] tmp;
}


void RenderArea::mouseMoveEvent(QMouseEvent *event){
    if (m_pressed){
        int x = event->x()/(CSIZE+1);
        int y = event->y()/(CSIZE+1);

        x = ((event->x()/(CSIZE+1)) < 0)? 0 : (((event->x()/(CSIZE+1)) >= WIDTH)?WIDTH-1:x);
        y = ((event->y()/(CSIZE+1)) < 0)? 0 : (((event->y()/(CSIZE+1)) >= HEIGHT)?HEIGHT-1:y);
        grid[x][y] = 1;

        painter->translate(1, 1);
        int chan = 255 - grid[x][y]*200;
        QColor c(chan, chan, chan);
        painter->fillRect(x*(CSIZE+1), y*(CSIZE+1), CSIZE, CSIZE, c);
        painter->resetTransform();

        update();
    }
}


void RenderArea::mousePressEvent(QMouseEvent *event){
    m_pressed = 1;

    int x = event->x()/(CSIZE+1);
    int y = event->y()/(CSIZE+1);

    x = ((event->x()/(CSIZE+1)) < 0)? 0 : (((event->x()/(CSIZE+1)) >= WIDTH)?WIDTH-1:x);
    y = ((event->y()/(CSIZE+1)) < 0)? 0 : (((event->y()/(CSIZE+1)) >= HEIGHT)?HEIGHT-1:y);
    grid[x][y] = 1;

    painter->translate(1, 1);
    int chan = 255 - grid[x][y]*200;
    QColor c(chan, chan, chan);
    painter->fillRect(x*(CSIZE+1), y*(CSIZE+1), CSIZE, CSIZE, c);
    painter->resetTransform();

    update();
}


void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    m_pressed = 0;

    int x = event->x()/(CSIZE+1);
    int y = event->y()/(CSIZE+1);

    x = ((event->x()/(CSIZE+1)) < 0)? 0 : (((event->x()/(CSIZE+1)) >= WIDTH)?WIDTH-1:x);
    y = ((event->y()/(CSIZE+1)) < 0)? 0 : (((event->y()/(CSIZE+1)) >= HEIGHT)?HEIGHT-1:y);
    grid[x][y] = 1;

    painter->translate(1, 1);
    int chan = 255 - grid[x][y]*200;
    QColor c(chan, chan, chan);
    painter->fillRect(x*(CSIZE+1), y*(CSIZE+1), CSIZE, CSIZE, c);
    painter->resetTransform();

    update();
}


void RenderArea::setup(){
    grid = new bool*[WIDTH];
    next = new bool*[WIDTH];
    for(int x = 0; x < WIDTH; x++){
        grid[x] = new bool[HEIGHT];
        next[x] = new bool[HEIGHT];
        for(int y = 0; y < HEIGHT; y++){
            grid[x][y] = 0;
            next[x][y] = 0;
        }
    }

//    for(int x = WIDTH/2 - 5; x <= WIDTH/2 + 5; x++){
//        for(int y = HEIGHT/2 - 5; y <= HEIGHT/2 + 5; y++){
//            grid[x][y] = 1;
//        }
//    }
}


void RenderArea::draw(){
    painter->fillRect(image->rect(), Qt::black);
    painter->setPen(Qt::black);

    QColor c;
    int chan;
    painter->translate(1, 1);
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            chan = 255 - grid[x][y]*200;
            c.setRgb(chan, chan, chan);
            painter->fillRect(x*(CSIZE+1), y*(CSIZE+1), CSIZE, CSIZE, c);
        }
    }
    painter->resetTransform();

    int n;  // neighbor
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            n = 0;
            for(int i = x-1; i <= x+1; i++){
                for(int j = y-1; j <= y+1; j++){
                    if (i > -1 && i < WIDTH && j > -1 && j < HEIGHT){
                        if ((i!=x || j!=y) && grid[i][j]) n++;
                    }
                }
            }

            if (!grid[x][y] && n==3)
                next[x][y] = 1;
            else if (grid[x][y] && !(n==3 || n==2)) {
                next[x][y] = 0;
            }
            else {
                next[x][y] = grid[x][y];
            }

        }
    }
    swap();

    update();
}








