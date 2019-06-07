#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QMessageBox>
#include <cmath>
#include <fstream>
#include <stdint.h>
#include <stack>
#include <algorithm>
#include "grapher.h"

#define PI 3.14159265359
#define VERTICAL 1
#define HORIZONTAL 0

class Image
{

#pragma pack(push, 1)
    typedef struct{
        uint16_t bfType         = 0;
        uint32_t bfSize         = 0;
        uint16_t bfReserved1    = 0;
        uint16_t bfReserved2    = 0;
        uint32_t bfOffBits      = 0;
    }BITMAPFILEHEADER;

    typedef struct{
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
#pragma pack(pop)

    typedef struct RGB{
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char visible = 1;
        friend bool operator!=(const RGB& left, const RGB& right){
            return !(left.red == right.red &&
                    left.green == right.green &&
                    left.blue == right.blue &&
                    left.visible == right.visible);
        }
    }RGB;

public:
    ~Image();
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    RGB** rgb = nullptr;
    QPixmap getMap();

    void floodFill(int x, int y, QColor color, bool fill);
    int setPart(int s_x, int s_y, int f_x, int f_y, QColor color, int thick);
    void drawLine(int s_x, int s_y, int f_x, int f_y, QColor color, bool fill = 1);
    void drawThickLine(int s_x, int s_y, int f_x, int f_y, int thick, QColor color, bool fill = 1);
    void defCircle(int s_x, int s_y, double radius, QColor color, bool fill = 1);
    void drawCircle(int s_x, int s_y, double radius, int thick, QColor color);
    void mirror_hor();
    void mirror_ver();
    void rotate();

    int defHexagon(int s_x, int s_y, double radius, double angle, QColor color, bool fill = 1);
    int paintHexagon(int s_x, int s_y, double radius, double angle, int thick, bool fill, QColor fore, QColor back);
    int copyRect(int s_x, int s_y, int f_x, int f_y, int n_x, int n_y);
    int recolorRect(int s_x, int s_y, int f_x, int f_y, QColor old_color, QColor new_color);
    int createFrame(QColor primary, QColor additional, bool fill, int type, double parameter);

    int newImage(const int32_t width, const int32_t height);
    int saveImage(const char *path);
    int loadImage(const char *path);
};

#endif // IMAGE_H
