#include "createframedialog.h"
#include "ui_createframedialog.h"

#include <QDebug>


CreateFrameDialog::CreateFrameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFrameDialog)
{
    ui->setupUi(this);
    ui->angle_value->setEnabled(0);
    ui->density_value->setEnabled(0);

    map = new Grapher;
    map->setFixedSize(170,170);
    map->scene->setBackgroundBrush(Qt::white);
    map->scene->setSceneRect(0, 0, 160, 160);
    this->ui->Field->addWidget(map);

    this->setWindowTitle("Создать рамку");
}

CreateFrameDialog::~CreateFrameDialog()
{
    delete ui;
}


void CreateFrameDialog::drawBranch(double angle){

    foreach(QGraphicsItem *item, map->scene->items())
        delete item;

    QPen pen(Qt::black, 4);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    double length = 25;
    coordinate start;
    coordinate finish = {110, 140};
    coordinate tmp;

    for(int i = 1; length > 3; i++){
        length *= 0.8;
        start = finish;
        finish = {start.x + static_cast<int>(round(length*sin(angle*i))), start.y - static_cast<int>(round(length*cos(angle*i)))};
        if (i == 1) tmp = finish;
        map->scene->addLine(start.x, start.y, finish.x, finish.y, pen);
    }

    length = 25;
    finish = tmp;
    for(int i = 1; length > 5; i++){
        length *= 0.9;
        start = finish;
        finish = {start.x - static_cast<int>(round(length*sin(angle*i/2))), start.y - static_cast<int>(round(length*cos(angle*i/2)))};
        map->scene->addLine(start.x, start.y, finish.x, finish.y, pen);
    }
}


void CreateFrameDialog::drawLineFrame(int density){
    foreach(QGraphicsItem *item, map->scene->items())
        delete item;

    QPen pen(Qt::black);
    pen.setJoinStyle(Qt::MiterJoin);
    int frame_count = 0;
    int width = 0;

    switch (density){
    case 1:
        width = 16;
        frame_count = 1;
        break;
    case 2:
        width = 12;
        frame_count = 2;
        break;
    case 3:
        width = 8;
        frame_count = 3;
        break;
    case 4:
        width = 6;
        frame_count = 4;
        break;
    case 5:
        width = 4;
        frame_count = 5;
        break;
    }
    pen.setWidth(width);

    int s_x = width/2;
    int s_y = width/2;
    int f_x = 168 - width;
    int f_y = 168 - width;

    for(int i = 0; i < frame_count; i++){
        map->scene->addRect(s_x, s_y, f_x, f_y, pen);
        s_x += width*3/2;
        s_y += width*3/2;
        f_x -= width*3;
        f_y -= width*3;
    }
}


void CreateFrameDialog::drawKeltCross(double radius){
    foreach(QGraphicsItem *item, map->scene->items())
        delete item;

    QPen pen(Qt::black, 5);
    pen.setCapStyle(Qt::FlatCap);

    map->scene->addLine(40, 40, 40+SQR_SIDE, 40+SQR_SIDE, pen);
    map->scene->addLine(40, 40+SQR_SIDE, 40+SQR_SIDE, 40, pen);
    map->scene->addEllipse(40+(SQR_SIDE/2-radius), 40+(SQR_SIDE/2-radius), 2*radius, 2*radius, pen);
}


void CreateFrameDialog::on_branches_clicked()
{
    func = BRANCH;
    ui->angle_value->setEnabled(1);
    ui->density_value->setEnabled(0);
    ui->radius_value->setEnabled(0);
    drawBranch(angle);
}

void CreateFrameDialog::on_angle_value_valueChanged(int value)
{
    angle = (PI * static_cast<double>(value))/180.0;
    drawBranch(angle);
}


void CreateFrameDialog::on_line_frame_clicked()
{
    func = RIM;
    ui->density_value->setEnabled(1);
    ui->angle_value->setEnabled(0);
    ui->radius_value->setEnabled(0);
    drawLineFrame(density);

}

void CreateFrameDialog::on_density_value_valueChanged(int value)
{
    density = value;
    drawLineFrame(density);
}


void CreateFrameDialog::on_kelt_cross_clicked()
{
    func = CROSS;
    ui->radius_value->setEnabled(1);
    ui->angle_value->setEnabled(0);
    ui->density_value->setEnabled(0);
    drawKeltCross(radius);
}

void CreateFrameDialog::on_radius_value_valueChanged(int value)
{
    radius = static_cast<double>(SQR_SIDE*value)/200.0;
    drawKeltCross(radius);
}


void CreateFrameDialog::on_apply_clicked()
{
    this->done(1);
}

void CreateFrameDialog::on_reject_clicked()
{
    this->done(0);
}












