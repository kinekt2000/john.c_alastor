#include "image.h"
#include <QDebug>



int Image::newImage(const int32_t width, const int32_t height){

        /*
         * Настройки первых двух
         * Блоков памяти нового BMP файла
         */
    bfh.bfType = 0x4d42;
    bfh.bfSize = (unsigned(width)*3 + (4 - (unsigned(width)*3)%4)%4)*unsigned(height) + 54;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;

    bih.biSize = 40;
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biClrUsed = 0;
    bih.biBitCount = 24;
    bih.biSizeImage = unsigned(width*height);
    bih.biCompression = 0;
    bih.biClrImportant = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;

    /* Создание матрицы пикселей */
    rgb = new RGB* [unsigned(height)];
    for(int i = 0; i < height; i++){
        rgb[i] = new RGB [unsigned(width)];
        for(int j = 0; j < width; j++){
            rgb[i][j] = {255, 255, 255};
        }
    }

//    drawThickLine(10, 10, 50, 50, 10, Qt::black);
    return 0;
}


int Image::saveImage(const char *path){
    FILE *out = fopen(path, "wb");
    if (!out) return 1;
    fwrite(&bfh, sizeof(bfh), 1, out);
    fwrite(&bih, sizeof(bih), 1, out);
    fseek(out, long(bfh.bfOffBits), SEEK_SET);

    size_t len_of_pdng = (4 - (bih.biWidth*3)%4)%4;             // Расчет длины выравнивания
    char *pdng = static_cast<char*>(new char[len_of_pdng]);     // Создание массива нулей для выравнивания

    for(int i = bih.biHeight - 1; i >= 0; i--){                 // Инвертирование в высоту в силу расположения битов в BMP
        for(int j = 0; j < bih.biWidth; j++){
//            fwrite(&(rgb[i][j]), sizeof(RGB), 1, out);
            fwrite(&(rgb[i][j].blue), sizeof(uchar), 1, out);
            fwrite(&(rgb[i][j].green), sizeof(uchar), 1, out);
            fwrite(&(rgb[i][j].red), sizeof(uchar), 1, out);
        }
        fwrite(pdng, len_of_pdng, 1, out);
    }
    fclose(out);
    delete [] pdng;
    return 0;
}


int Image::loadImage(const char *path){
    FILE *inp = fopen(path, "rb");
    if (!inp) return 1;

    for(int i = 0; i < bih.biHeight; i++)
        delete [] rgb[i];
    delete [] rgb;

    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, inp);

    if(bfh.bfType != 0x4d42){
        bfh = {0, 0, 0, 0, 0};
        fclose(inp);
        return 2;
    }

    fread(&bih, sizeof(BITMAPINFOHEADER), 1, inp);
    if (bih.biWidth > 8192 || bih.biHeight > 6144){
        bfh = {0, 0, 0, 0, 0};
        bih = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        fclose(inp);
        return 3;
    }
    if (bih.biClrUsed){
        bfh = {0, 0, 0, 0, 0};
        bih = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        fclose(inp);
        return 4;
    }

    rgb = new RGB* [unsigned(bih.biHeight)];
    for(int i = 0; i < bih.biHeight; i++)
        rgb[i] = new RGB [unsigned(bih.biWidth)];

    fseek(inp, long(bfh.bfOffBits), SEEK_SET);
    long int len_of_pdng = (4 - (bih.biWidth*3)%4)%4;

    for(int i = bih.biHeight - 1; i >= 0; i--){
        for(int j = 0; j < bih.biWidth; j++){
            fread(&(rgb[i][j].blue), sizeof(unsigned char), 1, inp);
            fread(&(rgb[i][j].green), sizeof(unsigned char), 1, inp);
            fread(&(rgb[i][j].red), sizeof(unsigned char), 1, inp);
            rgb[i][j].visible = 1;
        }
        fseek(inp, len_of_pdng, SEEK_CUR);
    }
    fclose(inp);
    return 0;
}


Image::~Image(){
    for(int i = 0; i < bih.biHeight; i++)
        delete [] rgb[i];
    delete [] rgb;
}


QPixmap Image::getMap(){
    /* Построение изображения с помощью матрицы пикселей rgb */
    QImage *image = new QImage(bih.biWidth, bih.biHeight, QImage::Format_RGB666);
    QColor pixel;
    for(int i = 0; i < bih.biHeight; i++){
        for(int j = 0; j < bih.biWidth; j++){
            pixel.setRed(rgb[i][j].red);
            pixel.setGreen(rgb[i][j].green);
            pixel.setBlue(rgb[i][j].blue);
            image->setPixel(j,i,pixel.rgb());
        }
    }
    QPixmap out = QPixmap::fromImage(*image);
    delete image;
    return out;
}



typedef struct{
    int x;
    int y;
}point;


void Image::floodFill(int x, int y, QColor color, bool fill = 1){
    point pt, curr;
    RGB pix = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};

    pt.x = x;
    pt.y = y;
    std::stack<point> stk;
    rgb[pt.y][pt.x] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
    stk.push(pt);

    while(!stk.empty()){
        curr = stk.top();
        stk.pop();

        if (curr.x > 0 && rgb[curr.y][curr.x - 1] != pix){
            pt.x = curr.x - 1;
            pt.y = curr.y;
            rgb[pt.y][pt.x] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
            stk.push(pt);
        }

        if (curr.x + 1 < bih.biWidth && rgb[curr.y][curr.x + 1] != pix){
            pt.x = curr.x + 1;
            pt.y = curr.y;
            rgb[pt.y][pt.x] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
            stk.push(pt);
        }

        if (curr.y > 0 && rgb[curr.y - 1][curr.x] != pix){
            pt.x = curr.x;
            pt.y = curr.y - 1;
            rgb[pt.y][pt.x] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
            stk.push(pt);
        }

        if (curr.y + 1 < bih.biHeight && rgb[curr.y + 1][curr.x] != pix){
            pt.x = curr.x;
            pt.y = curr.y + 1;
            rgb[pt.y][pt.x] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
            stk.push(pt);
        }
    }
}


int Image::setPart(int s_x, int s_y, int f_x, int f_y, QColor color, int thick){
    for(int s_i = s_x - thick/2, f_i = f_x - thick/2; s_i <= s_x + thick/2 || f_i <= f_x + thick/2; s_i++, f_i++){
        for(int s_j = s_y - thick/2, f_j = f_y - thick/2; s_j <= s_y + thick/2 || f_j <= f_y + thick/2; s_j++, f_j++){
            if (    (s_j >= 0) && (s_j < bih.biHeight) &&
                    (s_i >= 0) && (s_i < bih.biWidth)  &&
                    (f_j >= 0) && (f_j < bih.biHeight) &&
                    (f_i >= 0) && (f_i < bih.biWidth)     ){
                rgb[s_j][s_i].red = uchar(color.red());
                rgb[s_j][s_i].green = uchar(color.green());
                rgb[s_j][s_i].blue = uchar(color.blue());
                rgb[f_j][f_i].red = uchar(color.red());
                rgb[f_j][f_i].green = uchar(color.green());
                rgb[f_j][f_i].blue = uchar(color.blue());
            }
        }
    }

    if ((s_x - f_x) * (s_y - f_y) > 0){
        for(int i = -thick/2; i <= thick/2; i++){
            drawLine(s_x - i, s_y + i, f_x - i, f_y + i, color);
            drawLine(s_x - i - 1, s_y + i, f_x - i - 1, f_y + i, color);
        }
    }
    else {
        for(int i = -thick/2; i <= thick/2; i++){
            drawLine(s_x + i, s_y + i, f_x + i, f_y + i, color);
            drawLine(s_x + i - 1, s_y + i, f_x + i - 1, f_y + i, color);
        }
    }
    return 0;
}


void Image::drawLine(int s_x, int s_y, int f_x, int f_y, QColor color, bool fill){
    const int deltaX = abs(f_x - s_x);
    const int deltaY = abs(f_y - s_y);
    const int signX = s_x < f_x ? 1 : -1;
    const int signY = s_y < f_y ? 1 : -1;

    int error = deltaX - deltaY;

    if(f_y >= 0 && f_x >= 0 && f_y < bih.biHeight && f_x < bih.biWidth){
        rgb[f_y][f_x].red = uchar(color.red());
        rgb[f_y][f_x].green = uchar(color.green());
        rgb[f_y][f_x].blue = uchar(color.blue());
        rgb[f_y][f_x].visible = fill;
    }

    while(s_x != f_x || s_y != f_y){
        if(s_y >= 0 && s_x >= 0 && s_y < bih.biHeight && s_x < bih.biWidth){
            rgb[s_y][s_x].red = uchar(color.red());
            rgb[s_y][s_x].green = uchar(color.green());
            rgb[s_y][s_x].blue = uchar(color.blue());
            rgb[s_y][s_x].visible = fill;
        }

        const int error2 = error*2;

        if(error2 > -deltaY){
            error -= deltaY;
            s_x += signX;
        }
        if(error2 < deltaX){
            error += deltaX;
            s_y += signY;
        }
    }
}


void Image::drawThickLine(int s_x, int s_y, int f_x, int f_y, int thick, QColor color, bool fill){
    if (thick == 1){
        drawLine(s_x, s_y, f_x, f_y, color, fill);
        return;
    }

       // VERTICAL
    for(int i = 0; i < thick; i++){
        drawLine(s_x, s_y - i/2, f_x, f_y - i/2, color, fill);
    }
       // HORIZONTAL
    for(int i = 0; i < thick; i++){
        drawLine(s_x - i/2, s_y, f_x - i/2, f_y, color, fill);
    }
}


void Image::defCircle(int s_x, int s_y, double radius, QColor color, bool fill){
    for(int i = -int(radius); i <= int(radius); i++){
        for(int j = -int(radius); j <= int(radius); j++){
            if(i*i + j*j <= int(radius*radius))
                rgb[s_y + i][s_x + j] = {uchar(color.red()), uchar(color.green()), uchar(color.blue()), fill};
        }
    }
}


void Image::drawCircle(int s_x, int s_y, double radius, int thick, QColor color){
    int32_t bufSide = static_cast<int32_t>(round((radius+1)*2));
    Image *buffer =  new Image;
    buffer->bih.biHeight = bufSide;
    buffer->bih.biWidth = bufSide;
    buffer->rgb = new RGB* [unsigned(bufSide)];
    for(int i = 0; i < bufSide; i++){
        buffer->rgb[i] = new RGB [unsigned(bufSide)];
        for(int j = 0; j < bufSide; j++)
            buffer->rgb[i][j].visible = 0;
    }
    int cntr = bufSide/2;

    buffer->defCircle(cntr, cntr, radius, color);
    if (thick) buffer->defCircle(cntr, cntr, radius - thick + 1, color, 0);

    for(int i = 0; i < bufSide; i++){
        for(int j = 0; j < bufSide; j++)
            if(s_y-cntr+i >= 0 && s_x-cntr+j >= 0 && s_y-cntr+i < bih.biHeight && s_x-cntr+j < bih.biWidth && buffer->rgb[i][j].visible)
                rgb[s_y-cntr+i][s_x-cntr+j] = buffer->rgb[i][j];
    }

    delete buffer;
    return;
}


void Image::mirror_hor(){
    for (int i = 0; i < bih.biHeight; i++)
        for(int j = 0; j <= bih.biWidth/2; j++){
            RGB buf = rgb[i][j];
            rgb[i][j] = rgb[i][bih.biWidth - 1 - j];
            rgb[i][bih.biWidth - 1 - j] =  buf;
        }
}


void Image::mirror_ver(){
    for (int i = 0; i <= bih.biHeight/2; i++)
        for(int j = 0; j < bih.biWidth; j++){
            RGB buf = rgb[i][j];
            rgb[i][j] = rgb[bih.biHeight - 1 - i][j];
            rgb[bih.biHeight - 1 - i][j] = buf;
        }
}


int Image::defHexagon(int s_x, int s_y, double radius, double angle, QColor color, bool fill){
    int s_node_x = static_cast<int>(s_x + round(radius*cos(angle)));
    int s_node_y = static_cast<int>(s_y + round(radius*sin(angle)));
    int f_node_x;
    int f_node_y;
    for(int i = 0; i <= 6; i++){
        f_node_x = static_cast<int>(s_x + round(radius*cos(PI/3*i + angle)));
        f_node_y = static_cast<int>(s_y + round(radius*sin(PI/3*i + angle)));
        drawLine(s_node_x, s_node_y, f_node_x, f_node_y, color, fill);
        s_node_x = f_node_x;
        s_node_y = f_node_y;
    }
    this->floodFill(s_x, s_y, color, fill);
    return 0;
}


int Image::paintHexagon(int s_x, int s_y, double radius, double angle, int thick, bool fill, QColor fore, QColor back){
    int32_t bufSide = static_cast<int32_t>(round((radius+1)*2));
    Image *buffer =  new Image;
    buffer->bih.biHeight = bufSide;
    buffer->bih.biWidth = bufSide;
    buffer->rgb = new RGB* [unsigned(bufSide)];
    for(int i = 0; i < bufSide; i++){
        buffer->rgb[i] = new RGB [unsigned(bufSide)];
        for(int j = 0; j < bufSide; j++)
            buffer->rgb[i][j] = {uchar(back.red()), uchar(back.green()), uchar(back.blue()), 0};
    }
    int cntr = bufSide/2;
    buffer->defHexagon(cntr, cntr, radius, angle, fore);
    buffer->defHexagon(cntr, cntr, radius - thick + 1, angle, back, fill);

    for(int i = 0; i < bufSide; i++){
        for(int j = 0; j < bufSide; j++)
            if(s_y-cntr+i >= 0 && s_x-cntr+j >= 0 && s_y-cntr+i < bih.biHeight && s_x-cntr+j < bih.biWidth && buffer->rgb[i][j].visible)
                rgb[s_y-cntr+i][s_x-cntr+j] = buffer->rgb[i][j];
    }

    delete buffer;
    return 0;
}


int Image::copyRect(int s_x, int s_y, int f_x, int f_y, int n_x, int n_y){
    if(n_x <= 0 || n_y <= 0 || n_x > bih.biWidth || n_y > bih.biHeight) return 1;

    int ux;
    int uy;
    int lx;
    int ly;

    if (s_x < 0) s_x = 0;
    if (s_y < 0) s_y = 0;
    if (f_x < 0) f_x = 0;
    if (f_y < 0) f_y = 0;

    if (s_x >= bih.biWidth) s_x = bih.biWidth - 1;
    if (s_y >= bih.biHeight) s_y = bih.biHeight - 1;
    if (f_x >= bih.biWidth) f_x = bih.biWidth - 1;
    if (f_y >= bih.biHeight) f_y = bih.biHeight - 1;

    if (s_x > f_x) { ux = f_x; lx = s_x;}
    else {ux = s_x; lx = f_x;}

    if (s_y > f_y) {uy = f_y; ly = s_y;}
    else {uy = s_y; ly = f_y;}

    uint32_t bufHeight = static_cast<uint32_t>(ly - uy + 1);
    uint32_t bufWidth = static_cast<uint32_t>(lx - ux + 1);
    RGB **buffer = new RGB* [bufHeight];
    for(size_t i = 0; i < bufHeight; i++)
        buffer[i] = new RGB [bufWidth];

    for(int i = uy; i <= ly; i++)
        for(int j = ux; j <= lx; j++)
            buffer[i-uy][j-ux] = rgb[i][j];

    for(int i = n_y; i < n_y + int(bufHeight); i++)
        for(int j = n_x; j < n_x + int(bufWidth); j++)
            if(i >= 0 && j >= 0 && i < bih.biHeight && j < bih.biWidth)
                rgb[i][j] = buffer[i-n_y][j-n_x];

    for(size_t i = 0; i < bufHeight; i++)
        delete [] buffer[i];
    delete [] buffer;

    return 0;
}


int Image::recolorRect(int s_x, int s_y, int f_x, int f_y, QColor old_color, QColor new_color){
    int ux;
    int uy;
    int lx;
    int ly;

    if (s_x < 0) s_x = 0;
    if (s_y < 0) s_y = 0;
    if (f_x < 0) f_x = 0;
    if (f_y < 0) f_y = 0;

    if (s_x >= bih.biWidth) s_x = bih.biWidth - 1;
    if (s_y >= bih.biHeight) s_y = bih.biHeight - 1;
    if (f_x >= bih.biWidth) f_x = bih.biWidth - 1;
    if (f_y >= bih.biHeight) f_y = bih.biHeight - 1;

    if (s_x > f_x) { ux = f_x; lx = s_x;}
    else {ux = s_x; lx = f_x;}

    if (s_y > f_y) {uy = f_y; ly = s_y;}
    else {uy = s_y; ly = f_y;}

    for(int i = uy; i <= ly; i++)
        for(int j = ux; j <= lx; j++){
            if(i >= 0 && j >= 0 && i < bih.biHeight && j < bih.biWidth)
                if( (rgb[i][j].red == uchar(old_color.red()))     &&
                    (rgb[i][j].green == uchar(old_color.green())) &&
                    (rgb[i][j].blue == uchar(old_color.blue()))        ){

                        rgb[i][j].red = uchar(new_color.red());
                        rgb[i][j].green = uchar(new_color.green());
                        rgb[i][j].blue = uchar(new_color.blue());
                }
        }

    return 0;
}


int Image::createFrame(QColor primary, QColor additional, bool fill, int type, double parameter){
    Image *buffer = new Image;
    int elem_size = std::min(bih.biWidth, bih.biHeight)/5;

    buffer->bih.biWidth = bih.biWidth;
    buffer->bih.biHeight = bih.biHeight;
    buffer->rgb = new RGB* [unsigned(bih.biHeight)];
    for(int i = 0; i < bih.biHeight; i++){
        buffer->rgb[i] = new RGB [unsigned(bih.biWidth)];
        for(int j = 0; j < bih.biWidth; j++){
            buffer->rgb[i][j] = {uchar(primary.red()), uchar(primary.green()), uchar(primary.blue()), 0};
        }
    }

    if (type == 2){                     // RIM
        int frame_count = 0;
        int width = 0;
        switch (int(parameter)){
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

        int s_x = 0;
        int s_y = 0;
        int f_x = bih.biWidth - 1;
        int f_y = bih.biHeight - 1;

        for(int i = 0; i < frame_count; i++){
            for(int y = s_y; y <= s_y + width - 1; y++)
                for(int x = s_x; x <= f_x; x++)
                    buffer->rgb[y][x].visible = 1;

            for(int y = s_y + width - 1; y <= f_y - width + 1; y++)
                for(int x = s_x; x <= s_x + width - 1; x++)
                    buffer->rgb[y][x].visible = 1;

            for(int y = f_y - width + 1; y <= f_y; y++)
                for(int x = s_x; x <= f_x; x++)
                    buffer->rgb[y][x].visible = 1;

            for(int y = s_y + width - 1; y <= f_y - width + 1; y++)
                for(int x = f_x - width + 1; x <= f_x; x++)
                    buffer->rgb[y][x].visible = 1;

            s_x += width*3/2;
            s_y += width*3/2;
            f_x -= width*3/2;
            f_y -= width*3/2;
        }
    }
    else if (type == 3 || type == 1){
        Image *elem = new Image;

        int width = 4;
        if (type == 3){                 // CROSS
            elem->bih.biWidth = elem_size;
            elem->bih.biHeight = elem_size;
            elem->rgb = new RGB* [unsigned(elem_size)];
            for(int i = 0; i < elem_size; i++){
                elem->rgb[i] = new RGB [unsigned(elem_size)];
                for(int j = 0; j < elem_size; j++)
                    elem->rgb[i][j] = {255, 255, 255, 1};
            }
            elem->drawCircle(2, 2, double(width)/2.0, 0, Qt::black);
            elem->drawCircle(elem_size-3, 2, double(width)/2.0, 0, Qt::black);
            elem->drawCircle(elem_size-3, elem_size-3, double(width)/2.0, 0, Qt::black);
            elem->drawCircle(2, elem_size-3, double(width)/2.0, 0, Qt::black);

            for(int i = 0; i < 5; i++)
                elem->drawLine(2, 0 + i, elem_size-3, elem_size-5 + i, Qt::black);
            for(int i = 0; i < 5; i++)
                elem->drawLine(elem_size-3, 0 + i, 2, elem_size-5 + i, Qt::black);

            elem->drawCircle(elem_size/2, elem_size/2, (double(parameter*elem_size))/200.0, 5, Qt::black);

            double pdng;
            int count;

            //horizontal
            pdng = (double(bih.biWidth % elem_size))*double(elem_size)/double(bih.biWidth);
            count =  bih.biWidth/elem_size;
            for(int i = 0; i < count/2; i++){
                for(int y = 0; y < elem_size; y++)
                    for(int x = 0; x < elem_size; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[y][x + int(i*(elem_size + pdng))].visible = 1;
                            buffer->rgb[y+(bih.biHeight - (elem_size))][x + int(i*(elem_size + pdng))].visible = 1;

                            buffer->rgb[y][bih.biWidth - ((i+1)*elem_size + int(i*pdng)) + x].visible = 1;
                            buffer->rgb[y+(bih.biHeight - (elem_size))][bih.biWidth - ((i+1)*elem_size + int(i*pdng)) + x].visible = 1;
                        }
            }
            if (count%2)
                for(int y = 0; y < elem_size; y++)
                    for(int x = 0; x < elem_size; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[y][(bih.biWidth/2 - 1) - elem_size/2 + x].visible = 1;
                            buffer->rgb[y+(bih.biHeight - (elem_size))][(bih.biWidth/2 - 1) - elem_size/2 + x].visible = 1;
                        }

            //vertical
            pdng = (double(bih.biHeight % elem_size))*double(elem_size)/double(bih.biHeight);
            count = bih.biHeight/elem_size;
            for(int i = 1; i < count/2; i++){
                for(int y = 0; y < elem_size; y++)
                    for(int x = 0; x < elem_size; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[y + int(i*(elem_size + pdng))][x].visible = 1;
                            buffer->rgb[y + int(i*(elem_size + pdng))][x + (bih.biWidth - elem_size)].visible = 1;

                            buffer->rgb[bih.biHeight - (i+1)*(elem_size + int(pdng)) + y][x].visible = 1;
                            buffer->rgb[bih.biHeight - (i+1)*(elem_size + int(pdng)) + y][x + (bih.biWidth - elem_size)].visible = 1;

                        }
            }
            if (count%2)
                for(int y = 0; y < elem_size; y++)
                    for(int x = 0; x < elem_size; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[(bih.biHeight/2 - 1) - elem_size/2 + y][x].visible = 1;
                            buffer->rgb[(bih.biHeight/2 - 1) - elem_size/2 + y][x + (bih.biWidth - elem_size)].visible = 1;
                        }
        }

        if (type == 1){                 // BRANCH
            qDebug() << parameter;

            elem_size = std::min(bih.biWidth, bih.biHeight)/5;
            elem_size = std::max(elem_size, 80);


            elem->bih.biWidth = elem_size*2;
            elem->bih.biHeight = elem_size;
            elem->rgb = new RGB* [unsigned(elem->bih.biHeight)];
            for(int i = 0; i < elem->bih.biHeight; i++){
                elem->rgb[i] = new RGB [unsigned(elem->bih.biWidth)];
                for(int j = 0; j < elem->bih.biWidth; j++)
                    elem->rgb[i][j] = {255, 255, 255, 1};
            }
            double length = double(elem_size)/7.0;
            coordinate finish = {int(elem->bih.biWidth*0.6), int(elem->bih.biHeight*0.8)};
            coordinate start;
            coordinate tmp;
            double angle = parameter;

            for(int i = 1; length > 1; i++){
                length *= 0.8;
                start = finish;
                finish = {start.x + static_cast<int>(round(length*sin(angle*i))), start.y - static_cast<int>(round(length*cos(angle*i)))};
                if (i == 1) tmp = finish;
                elem->drawThickLine(start.x, start.y, finish.x, finish.y, width, Qt::black);
            }

            length = double(elem_size)/5.0;
            finish = tmp;
            for(int i = 1; length > 3; i++){
                length *= 0.9;
                start = finish;
                finish = {start.x - static_cast<int>(round(length*sin(angle*i/2))), start.y - static_cast<int>(round(length*cos(angle*i/2)))};
                elem->drawThickLine(start.x, start.y, finish.x, finish.y, width, Qt::black);
            }

            int base_move = -1;
            int side_move = elem->bih.biWidth;
            for(int i = elem->bih.biHeight - 1; i >= 0; i--){
                for(int j = 0; j < elem->bih.biWidth; j++){
                    if(elem->rgb[i][j].red == 0 && elem->rgb[i][j].green == 0 && elem->rgb[i][j].blue == 0){
                        if (i > base_move) base_move = i;
                        if (j < side_move) side_move = j;
                    }
                }
            }
            if (base_move == -1) base_move = 0;
            else base_move = elem->bih.biHeight - base_move - 1;

            if (side_move == elem->bih.biWidth) side_move = 0;


            int count;
            int branch_edge;

            branch_edge = elem->bih.biWidth/4;
            count = bih.biWidth/(2*branch_edge);

            //bottom left
            for(int i = 0; i < count; i ++){
                for(int y = 0; y < elem->bih.biHeight; y++)
                    for(int x = 0; x < elem->bih.biWidth; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[y + (bih.biHeight - elem->bih.biHeight) + base_move][x + i*branch_edge - side_move].visible = 1;
                        }
            }

            //bottom right
            for(int i = 0; i < count; i++){
                for(int y = 0; y < elem->bih.biHeight; y++)
                    for(int x = elem->bih.biWidth - 1; x >= 0; x--)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[y + (bih.biHeight - elem->bih.biHeight) + base_move][bih.biWidth - 1 - x - i*branch_edge + side_move].visible = 1;
                        }
            }

            //top left
            for(int i = 0; i < count ; i++){
                for(int y = elem->bih.biHeight - 1; y >= 0; y--)
                    for(int x = 0; x < elem->bih.biWidth; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[elem->bih.biHeight - 1 - y - base_move][x + i*branch_edge - side_move].visible = 1;
                        }
            }

            //top right
            for(int i = 0; i < count; i++){
                for(int y = elem->bih.biHeight - 1; y >= 0; y--)
                    for(int x = elem->bih.biWidth - 1; x >= 0; x--)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[elem->bih.biHeight - 1 - y - base_move][bih.biWidth - 1 - x - i*branch_edge + side_move].visible = 1;
                        }
            }


            count = bih.biHeight/(2*branch_edge);

            //right top
            for(int i = 0; i < count; i++)
                for(int y = 0; y < elem->bih.biHeight; y++)
                    for(int x = 0; x < elem->bih.biWidth; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[x - side_move + i*branch_edge][y + bih.biWidth - elem->bih.biHeight + base_move].visible = 1;
                        }

            //right bottom
            for(int i = 0; i < count; i++){
                for(int y = 0; y < elem->bih.biHeight; y++)
                    for(int x = elem->bih.biWidth - 1; x >= 0; x--)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[bih.biHeight - 1 - x - i*branch_edge + side_move][y + bih.biWidth - elem->bih.biHeight + base_move].visible = 1;
                        }
            }

            //left top
            for(int i = 0; i < count; i++){
                for(int y = elem->bih.biHeight - 1; y >= 0; y--)
                    for(int x = 0; x < elem->bih.biWidth; x++)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[x - side_move + i*branch_edge][elem->bih.biHeight - 1 - y - base_move].visible = 1;
                        }
            }

            //left bottom
            for(int i = 0; i < count; i++){
                for(int y = elem->bih.biHeight - 1; y >= 0; y--)
                    for(int x = elem->bih.biWidth - 1; x >= 0; x--)
                        if (elem->rgb[y][x].red == 0 && elem->rgb[y][x].green == 0 && elem->rgb[y][x].blue == 0){
                            buffer->rgb[bih.biHeight - 1 - x - i*branch_edge + side_move][elem->bih.biHeight - 1 - y - base_move].visible = 1;
                        }
            }
        }
    }

    else
        return 1;

    for(int i = 0; i < bih.biHeight; i++)
        for(int j = 0; j < bih.biWidth; j++)
            if(buffer->rgb[i][j].visible)
                rgb[i][j] = buffer->rgb[i][j];
    return 0;
}











