#ifndef NEWIMAGE_H
#define NEWIMAGE_H

#include <QPixmap>
#include <QMessageBox>
#include <cmath>
#include <fstream>
#include <stdint.h>


class newimage
{
    #pragma pack(push, 1)
    typedef struct BITMAPFILEHEADER {
        uint16_t bfType         = 0;
        uint32_t bfSize         = 0;
        uint16_t bfReserved1    = 0;
        uint16_t bfReserved2    = 0;
        uint32_t bfOffBits      = 0;
    }BITMAPFILEHEADER;

    typedef struct BITMAPINFOHEADER {
        uint32_t biSize         = 0;
        int32_t biWidth         = 0;
        int32_t biHeight        = 0;
        uint16_t biPlanes       = 0;
        uint16_t biBitCount     = 0;
        uint32_t biCompression  = 0;
        uint32_t biSizeImage    = 0;
        int32_t biXPelsPerMeter = 0;
        int32_t biYPelsPerMeter = 0;
        uint32_t biClrUsed      = 0;
        uint32_t biClrImportant = 0;
    }BITMAPINFOHEADER;
public:
    typedef struct RGBTRIPPLE {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char visible = 1;
    }RGB;
    #pragma pack(pop)

public:
    ~newimage();
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    RGB** rgb = nullptr;
    //RGB*** t_rgb;
    QPixmap getMap();
    int loadImage(const char *path);
    int saveImage(const char *path);

    int paint_rect(int sx, int sy, int fx, int fy, bool incolor, int width, QColor col, QColor in_col);
    int paint_circ(int sx, int sy, int fx, int fy, bool incolor, int width, QColor col, QColor in_col);
};

#endif // NEWIMAGE_H
