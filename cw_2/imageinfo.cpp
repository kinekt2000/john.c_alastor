#include "imageinfo.h"
#include "ui_imageinfo.h"

ImageInfo::ImageInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageInfo)
{
    ui->setupUi(this);
    ui->width->setBackgroundRole(QPalette::Base);
    ui->height->setBackgroundRole(QPalette::Base);
    ui->size->setBackgroundRole(QPalette::Base);
}

ImageInfo::~ImageInfo()
{
    delete ui;
}


void ImageInfo::update(Image *img){
    ui->width->setText("  " + QString::number(img->bih.biWidth) + " px");
    ui->height->setText("  " + QString::number(img->bih.biHeight) + " px");
    ui->size->setText("  " + QString::number(double(img->bfh.bfSize)/1024.0) + " KB");
}
