#include "widget.h"
#include "ui_widget.h"
#include <QDebug>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    renderArea = new RenderArea;
    renderArea->setFixedSize(RSIZE, RSIZE);
    ui->Field->addWidget(renderArea);
    renderArea->setCursor(QCursor(Qt::CrossCursor));
    renderArea->update();

    tmr = new QTimer;
    tmr->setInterval(0);
    setMouseTracking(true);

    connect(tmr, SIGNAL(timeout()), this, SLOT(execute()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Start_clicked()
{
    ui->Start->setEnabled(false);
    ui->Stop->setEnabled(true);
    tmr->start();
}


void Widget::execute(){
    draw();
}

void Widget::draw(){
    double a;
    double b;
    for(int x = 1; x < RSIZE-1; x++)
        for(int y = 1; y < RSIZE-1; y++){
            a = renderArea->grid[x][y].a;
            b = renderArea->grid[x][y].b;
            renderArea->next[x][y].a = (a) +
                                       ((dA*renderArea->laplaceA(x, y)) -
                                       (a*b*b) +
                                       (feed*(1 - a)));
            renderArea->next[x][y].b = (b) +
                                       ((dB*renderArea->laplaceB(x, y)) +
                                       (a*b*b) -
                                       ((kill + feed)*b));
            if(renderArea->next[x][y].a < 0) renderArea->next[x][y].a = 0;
            if(renderArea->next[x][y].a > 1) renderArea->next[x][y].a = 1;
            if(renderArea->next[x][y].b < 0) renderArea->next[x][y].b = 0;
            if(renderArea->next[x][y].b > 1) renderArea->next[x][y].b = 1;
        }

    swap(renderArea->next, renderArea->grid);
    renderArea->update();
}

void Widget::on_Stop_clicked()
{
    ui->Start->setEnabled(true);
    ui->Stop->setEnabled(false);
    tmr->stop();
}

void Widget::on_Quit_clicked()
{
    QApplication::exit(0);
}

void Widget::on_Load_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Загрузка", "/home/", "*.bmp");
    if(path ==  nullptr) return;
    renderArea->imageToGrid(QImage(path));
}
