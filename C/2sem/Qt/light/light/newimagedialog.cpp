#include "newimagedialog.h"
#include "ui_newimagedialog.h"

NewImageDialog::NewImageDialog(QWidget *parent) :
    QDialog(parent),
    newimage(new Ui::NewImageDialog)
{
    newimage->setupUi(this);
    this->setWindowTitle("Новое изображение");
}

NewImageDialog::~NewImageDialog()
{
    delete newimage;
}


void NewImageDialog::on_Cancel_clicked()
{
    this->done(0);
}

void NewImageDialog::on_Apply_clicked()
{
    this->width = newimage->width->value();
    this->height = newimage->height->value();
    this->done(1);
}
