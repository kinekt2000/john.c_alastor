#include "renderarea.h"


double map(double A, double A1, double A2, double min, double max){
    long double percentage = static_cast<long double>(A-A1)/static_cast<long double>(A1-A2);
    return static_cast<double>((percentage) * static_cast<long double>((min-max)+min));
}

RenderArea::RenderArea(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene;
    image = new QImage(QSize(RSIZE*2+VWALL, RSIZE), QImage::Format_ARGB32);
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


void RenderArea::keyPressEvent(QKeyEvent *event){
    switch (event->key()){
    case 65:    // LEFT
        particle->rotate(-5);
        break;
    case 68:    // RIGHT
        particle->rotate( 5);
        break;
    case 87:    // FRONT
        particle->move( 5);
        break;
    case 83:    // BACK
        particle->move(-5);
        break;
    }
    qDebug() << event->key();
}


void RenderArea::mouseMoveEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();

    if (x < 0) x = 0;
    if (x >= RSIZE) x = RSIZE - 1;
    if (y < 0) y = 0;
    if (y >= RSIZE) y = RSIZE - 1;

    finish = {x, y};
}

void RenderArea::mousePressEvent(QMouseEvent* event){
    m_pressed = 1;

    int x = event->x();
    int y = event->y();

    if (x < 0) x = 0;
    if (x >= RSIZE) x = RSIZE - 1;
    if (y < 0) y = 0;
    if (y >= RSIZE) y = RSIZE - 1;

    finish = {x, y};
    start = {x, y};
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();

    if (x < 0) x = 0;
    if (x >= RSIZE) x = RSIZE - 1;
    if (y < 0) y = 0;
    if (y >= RSIZE) y = RSIZE - 1;

    finish = {x, y};
}


void RenderArea::setup(){
    screen = new std::vector<double>;

    walls = new std::vector<Boundary>;
    walls->push_back(Boundary(0, 0, RSIZE, 0));
    walls->push_back(Boundary(RSIZE, 0, RSIZE, RSIZE));
    walls->push_back(Boundary(0, RSIZE, RSIZE, RSIZE));
    walls->push_back(Boundary(0, 0, 0, RSIZE));

    std::default_random_engine generator(uint64_t(time(nullptr)));
    std::uniform_int_distribution<int> distribution(0,RSIZE);
    for(int i = 0; i < WCOUNT; i++){
        int x1 = distribution(generator);
        int y1 = distribution(generator);
        int x2 = distribution(generator);
        int y2 = distribution(generator);

        walls->push_back(Boundary(x1, y1, x2, y2));
    }

    particle = new Particle({finish[0], finish[1]});
    particle->update(20, 20);

    painter->setBrush(Qt::white);
    painter->setPen(QPen(painter->brush(), 2));
}


void RenderArea::draw(){
    painter->fillRect(image->rect(), QBrush(Qt::black));

    painter->setPen(QPen(QColor(255, 255, 255, 200), 0));
    //particle->update(finish[0], finish[1]);
    *screen = particle->look(painter, walls);

    painter->setPen(QPen(QColor(255, 0, 255), 4));
    for(auto wall: *walls)
        wall.show(painter);

    painter->translate(RSIZE+VWALL, 0);
    int w = RSIZE / screen->size();
    int h;
    int sRs = RSIZE * RSIZE;

    for(auto i = 0ul; i < screen->size(); i++){
        double sq = (*screen)[i] * (*screen)[i];
        int c = int(map(sq, 0, sRs, 0, 255));

        h = int((*screen)[i]);
        if (h >= RSIZE) h = RSIZE - 1;

        if (c < 0) c = 0;
        if (c > 255) c = 255;
        c = 255 - c;
        //qDebug() << c << i;
        painter->fillRect(int(i)*w, h/2, w, RSIZE - h, QColor(c, c, c));
    }
    painter->resetTransform();
    //particle->rotate(1);

    painter->fillRect(RSIZE, 0, VWALL, RSIZE, QColor(224, 96, 0));
    update();
}
