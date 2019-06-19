#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <QDialog>
#include <QString>
#include "image.h"

namespace Ui {
class ImageInfo;
}

class ImageInfo : public QDialog
{
    Q_OBJECT

public:
    void update(Image *img);
    explicit ImageInfo(QWidget *parent = nullptr);
    ~ImageInfo();

private:
    Ui::ImageInfo *ui;
};

#endif // IMAGEINFO_H
