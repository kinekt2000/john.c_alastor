#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent){}
PaintWidget::~PaintWidget(){}

void PaintWidget::paintEvent(QPaintEvent *){
    QPainter img(this);
    img.drawLine(0,0,20,20);
}
