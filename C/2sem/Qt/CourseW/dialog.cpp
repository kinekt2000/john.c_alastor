#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_frame1_clicked()
{
   done(1);
}

void Dialog::on_frame2_clicked()
{
    done(2);
}

void Dialog::on_frame3_clicked()
{
    done(3);
}

void Dialog::on_frame4_clicked()
{
    done(4);
}
