#include "newimage.h"
#include <QDebug>

/*newimage::newimage()
{

}*/

int newimage::loadImage(const char *path){
    FILE *inp = fopen(path, "rb");
    if (!inp) return 1;

    for(int i = 0; i < bih.biHeight; i++)
        delete [] rgb[i];
    delete [] rgb;

    fread(&bfh, sizeof(BITMAPFILEHEADER), 1, inp);
    fread(&bih, sizeof(BITMAPINFOHEADER), 1, inp);
    if (bih.biWidth > 8192 || bih.biHeight > 6144) return 2;

    rgb = new RGBTRIPPLE* [unsigned(bih.biHeight)];
    for(int i = 0; i < bih.biHeight; i++)
        rgb[i] = new RGBTRIPPLE [unsigned(bih.biWidth)];

    fseek(inp, long(bfh.bfOffBits), SEEK_SET);
    long int len_of_pdng = (4 - (bih.biWidth*3)%4)%4;

    for(int i = bih.biHeight - 1; i >= 0; i--){
        for(int j = 0; j < bih.biWidth; j++){
//            fread(&(rgb[i][j]), sizeof(RGB), 1, inp);
            fread(&(rgb[i][j].blue), sizeof(uchar), 1, inp);
            fread(&(rgb[i][j].green), sizeof(uchar), 1, inp);
            fread(&(rgb[i][j].red), sizeof(uchar), 1, inp);
        }
        fseek(inp, len_of_pdng, SEEK_CUR);
    }
    fclose(inp);
    return 0;
}

int newimage::saveImage(const char *path){
    FILE *out = fopen(path, "wb");
    if (!out) return 1;
    fwrite(&bfh, sizeof(bfh), 1, out);
    fwrite(&bih, sizeof(bih), 1, out);
    fseek(out, long(bfh.bfOffBits), SEEK_SET);

    size_t len_of_pdng = (4 - (bih.biWidth*3)%4)%4;             // Расчет длины выравнивания
    char *pdng = static_cast<char*>(new char[len_of_pdng]);     // Создание массива нулей для выравнивания

    for(int i = bih.biHeight - 1; i >= 0; i--){                 // Инвертирование в высоту в силу расположения битов в BMP
        for(int j = 0; j < bih.biWidth; j++){
            //fwrite(&(rgb[i][j]), sizeof(RGB), 1, out);
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


QPixmap newimage::getMap(){
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




int newimage::paint_rect(int sx, int sy, int fx, int fy, bool incolor, int width, QColor col, QColor in_col){

    for(int i = std::max(std::min(sy, fy), 0); i<std::min(std::max(sy,fy), bih.biHeight); i++){
        for(int j = std::max(std::min(sx, fx), 0); j<std::min(std::max(sx,fx), bih.biWidth); j++){
            if((i<std::min(sy, fy)+width || i>std::max(sy, fy)-width) || (j<std::min(sx, fx)+width || j>std::max(sx, fx)-width)){
                rgb[i][j].blue = uchar(col.blue());
                rgb[i][j].green = uchar(col.green());
                rgb[i][j].red = uchar(col.red());
             }
             else{
                 if(incolor == true){
                    rgb[i][j].blue = uchar(in_col.blue());
                    rgb[i][j].green = uchar(in_col.green());
                    rgb[i][j].red = uchar(in_col.red());
                 }
            }
        }
    }

    return 0;
}

int newimage::paint_circ(int sx, int sy, int fx, int fy, bool incolor, int width, QColor col, QColor in_col){

    int r = (int)std::sqrt(abs(sx-fx)*abs(sx-fx) + abs(sy-fy)*abs(sy-fy));
    for(int i = std::max(0, std::min(sy-r, bih.biHeight)); i < std::min(bih.biHeight, std::max(sy+r, 0)); i++){
        for(int j = std::max(0, std::min(sx-r, bih.biWidth)); j < std::min(bih.biWidth, std::max(sx+r, 0)); j++){
            int k = abs(sy - i);
            int l = abs(sx - j);
            if((k*k + l*l < r*r) && (k*k + l*l > (r-width)*(r-width))){
                rgb[i][j].blue = uchar(col.blue());
                rgb[i][j].green = uchar(col.green());
                rgb[i][j].red = uchar(col.red());
            }
            if(k*k + l*l <= (r-width)*(r-width)){
                if(incolor == true){
                   rgb[i][j].blue = uchar(in_col.blue());
                   rgb[i][j].green = uchar(in_col.green());
                   rgb[i][j].red = uchar(in_col.red());
                }
            }
        }
    }
//    for(int i = std::max(0, sx-r); i<)
    return 0;
}



newimage::~newimage(){
    for(int i = 0; i < bih.biHeight; i++)
        delete [] rgb[i];
    delete [] rgb;
}
