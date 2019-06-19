#include "anglechoice.h"
#include "ui_anglechoice.h"

AngleChoice::AngleChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AngleChoice)
{
    ui->setupUi(this);
}

AngleChoice::~AngleChoice()
{
    delete ui;
}


void AngleChoice::on_angle90_clicked()
{
    done(90);
}



void AngleChoice::on_angle180_clicked()
{
    done(180);
}


void AngleChoice::on_angle270_clicked()
{
    done(270);
}
