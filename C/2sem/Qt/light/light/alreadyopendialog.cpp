#include "alreadyopendialog.h"
#include "ui_alreadyopendialog.h"

AlreadyOpenDialog::AlreadyOpenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlreadyOpenDialog)
{
    ui->setupUi(this);
}

AlreadyOpenDialog::~AlreadyOpenDialog()
{
    delete ui;
}

void AlreadyOpenDialog::on_accept_clicked()
{
    reply = 1;
}

void AlreadyOpenDialog::on_reject_clicked()
{
    reply = 0;
}
