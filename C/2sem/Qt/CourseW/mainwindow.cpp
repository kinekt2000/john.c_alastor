#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :   //конструктор основного окна
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphicsView = new MyGraphicsView;
    img = new newimage;
    ui->picture->addWidget(GraphicsView);

    // ставим черный как начальный цвет
     QPalette col = ui->color->palette();
     col.setColor(QPalette::Button, QColor(0, 0, 0));
     ui->color->setPalette(col);
     ui->color->update();

     // ставим черный как нач цвет для заливки
     QPalette in_col = ui->in_color->palette();
     in_col.setColor(QPalette::Button, QColor(0, 0, 0));
     ui->in_color->setPalette(in_col);
     ui->in_color->update();

    connect(GraphicsView, SIGNAL(mouse_track_signal(int, int)), this, SLOT(show_coordinates(int, int))); //соединение сигнала мыши и выводимых в статусбар координат
    connect(GraphicsView, SIGNAL(rotate_signal_90(int, int, int, int)), this, SLOT(rotate90(int, int, int, int)));
    connect(GraphicsView, SIGNAL(rotate_signal_180(int, int, int, int)), this, SLOT(rotate180(int, int, int, int)));
    connect(GraphicsView, SIGNAL(rotate_signal_270(int, int, int, int)), this, SLOT(rotate270(int, int, int, int)));
    connect(GraphicsView, SIGNAL(rect_signal(int,int,int,int)), this, SLOT(rectangl(int, int, int, int)));
    connect(GraphicsView, SIGNAL(circ_signal(int,int,int,int)), this, SLOT(circle(int, int, int, int)));
}


MainWindow::~MainWindow()    //деструктор основного окна
{
    delete GraphicsView;
    delete img;
    delete ui;
}

void MainWindow::show_coordinates(int x, int y){    // Конструирование строк по значениям сообщенным в слот и их вывод
    std::string str_x = std::to_string(x);
    std::string str_y = std::to_string(y);
    ui->statusBar->showMessage(QString::fromStdString("x = " + str_x + "; " + "y = " + str_y + ";"));
}


void MainWindow::on_color_clicked() //изменение цвета
{
     col = QColorDialog::getColor();
     if(!col.isValid()) return;
     QPalette ch_color = ui->color->palette();
     ch_color.setColor(QPalette::Button, col);
     ui->color->setPalette(ch_color);
     ui->color->update();
}

void MainWindow::on_in_color_clicked()
{
    in_col = QColorDialog::getColor();
    if(!in_col.isValid()) return;
    QPalette ch_color = ui->in_color->palette();
    ch_color.setColor(QPalette::Button, in_col);
    ui->in_color->setPalette(ch_color);
    ui->in_color->update();
}

void MainWindow::on_open_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Загрузка", "/home/", "*.bmp");
    if(path == nullptr) return;
    int error = img->loadImage(path.toLocal8Bit().data());
    if (error) return;
    GraphicsView->update(img->getMap());
}

void MainWindow::on_save_file_triggered()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранение", "/home/", "*.bmp");
    int error = img->saveImage(path.toLocal8Bit().data());
    if(error) return;
}

void MainWindow::on_incolor_clicked(bool checked)
{
   if (checked) incolor = true;
   else incolor = false;
}

void MainWindow::on_width_valueChanged(int arg1)
{
    width = arg1;
}

void MainWindow::on_func_1_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        // doesn't exsist error
        return;
    }
    GraphicsView->func = RECT;
    // сигнал рисования прямоугольника
}

void MainWindow::rectangl(int sx, int sy, int fx, int fy)
{
   int error = img->paint_rect(sx, sy, fx, fy, incolor, width, col, in_col);
    if(error){
        qDebug() << "error";
        return;
    }
    GraphicsView->update(img->getMap());
    return;
    // функция рисования прямоугольника
}

void MainWindow::on_func_2_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        // doesn't exsist error
        return;
    }
    GraphicsView->func = CIRC;
    //сигнал рисования окружности
}

void MainWindow::circle(int sx, int sy, int fx, int fy)
{
    int error = img->paint_circ(sx, sy, fx, fy, incolor, width, col, in_col);
     if(error){
         qDebug() << "error";
         return;
     }
     GraphicsView->update(img->getMap());
     return;
    // функция рисования окружности
}



void MainWindow::on_func_3_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        // doesn't exsist error
        return;
    }
    Dialog* dialwind  = new Dialog;
    dialwind->exec();
    if(dialwind->result() == 1) frame_1(width, col); //GraphicsView->func = FR1;
    if(dialwind->result() == 2) frame_2(width, col, in_col); //GraphicsView->func = FR2;
    if(dialwind->result() == 3) frame_3(width, col, in_col); //GraphicsView->func = FR3;
    if(dialwind->result() == 4) frame_4(width, col); //GraphicsView->func = FR4;
    delete dialwind;
}

void MainWindow::frame_1(int width, QColor col){

    for(int i=0; i<img->bih.biHeight; i++){
        for(int j=0; j<img->bih.biWidth; j++){
            if(i<width || i>img->bih.biHeight-width ||j<width || j>img->bih.biWidth-width){
                img->rgb[i][j].blue = rand() % 256;
                img->rgb[i][j].green = rand() % 256;
                img->rgb[i][j].red = rand() % 256;
            }
        }
    }

    GraphicsView->update(img->getMap());
     return;
}

void MainWindow::frame_2(int width, QColor col, QColor in_col){

    int col_flag_y = 0;
    int col_flag_x = 0;

    for(int i=0; i<img->bih.biHeight; i++){
        for(int j=0; j<img->bih.biWidth; j++){
            if(i<width || i>img->bih.biHeight-width ||j<width || j>img->bih.biWidth-width){
                if(col_flag_y == col_flag_x){
                    img->rgb[i][j].blue = uchar(col.blue());
                    img->rgb[i][j].green = uchar(col.green());
                    img->rgb[i][j].red = uchar(col.red());
                }
                else{
                    img->rgb[i][j].blue = uchar(in_col.blue());
                    img->rgb[i][j].green = uchar(in_col.green());
                    img->rgb[i][j].red = uchar(in_col.red());
                }
            }
            if(col_flag_x+1<width) col_flag_x++;
            else col_flag_x = 0;
        }
        if(col_flag_y+1<width) col_flag_y++;
        else col_flag_y = 0;
    }

    GraphicsView->update(img->getMap());
     return;
}

void MainWindow::frame_3(int width, QColor col, QColor in_col){

//    if(width%2) width++;
//    bool col_flag_y = 0;
//    bool col_flag_x = 0;
//    int a = width/2;

//    int i = 0;
//    int j = 0;
//    while(i<img->bih.biHeight){
//        j = 0;
//        while(j<img->bih.biWidth){
//            if(i<width || i>img->bih.biHeight-width ||j<width || j>img->bih.biWidth-width){
//                if(col_flag_y == col_flag_x){
//                    img->rgb[i][j].blue = uchar(col.blue());
//                    img->rgb[i][j].green = uchar(col.green());
//                    img->rgb[i][j].red = uchar(col.red());
//                }
//                else{
//                    img->rgb[i][j].blue = uchar(in_col.blue());
//                    img->rgb[i][j].green = uchar(in_col.green());
//                    img->rgb[i][j].red = uchar(in_col.red());
//                }
//            }
//            j++;
//            if(j%a == 0) col_flag_x = !col_flag_x;
//        }
//        i++;
//        if(i%a == 0) col_flag_y = !col_flag_y;
//    }

    if (width%2) width++;
    int half = width >> 1;
    for (int i = 0; i < width; i++)
        for(int j = 0; j < img->bih.biWidth; j++){
            if (i < half && (j / half)%2){
                img->rgb[i][j].red = uchar(in_col.red());
                img->rgb[i][j].green = uchar(in_col.green());
                img->rgb[i][j].blue = uchar(in_col.blue());
            }
            else if (i < half){
                img->rgb[i][j].red = uchar(col.red());
                img->rgb[i][j].green = uchar(col.green());
                img->rgb[i][j].blue = uchar(col.blue());
            }
            else if (i >= half && (j / half)%2){
                img->rgb[i][j].red = uchar(col.red());
                img->rgb[i][j].green = uchar(col.green());
                img->rgb[i][j].blue = uchar(col.blue());
            }
            else{
                img->rgb[i][j].red = uchar(in_col.red());
                img->rgb[i][j].green = uchar(in_col.green());
                img->rgb[i][j].blue = uchar(in_col.blue());

            }
        }

    GraphicsView->update(img->getMap());
     return;
}

void MainWindow::frame_4(int width, QColor col){

    int a = 5;
    int b = width/2;
    int c = b + b/2;

    for(int i = a; i<img->bih.biHeight-a; i++){
        for(int j = a; j<img->bih.biWidth-a; j++){
            if((i<a+width || i>img->bih.biHeight-a-width) || (j<a+width || j>img->bih.biWidth-a-width)){
                if(i!=a+b && i!=img->bih.biHeight-a-b && i!=a+c && i!=img->bih.biHeight-a-c && j!=a+b && j!=img->bih.biWidth-a-b && j!=a+c && j!=img->bih.biWidth-a-c){
                    img->rgb[i][j].blue = uchar(col.blue());
                    img->rgb[i][j].green = uchar(col.green());
                    img->rgb[i][j].red = uchar(col.red());
                }
             }
        }
    }
    GraphicsView->update(img->getMap());
     return;
}


void MainWindow::on_func_4_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        // doesn't exsist error
        return;
    }
    AngleChoice* choice = new AngleChoice;
    choice->exec();
    if(choice->result() == 90) GraphicsView->func = ROTATE90;
    if(choice->result() == 180) GraphicsView->func = ROTATE180;
    if(choice->result() == 270) GraphicsView->func = ROTATE270;
    delete choice;
}

void MainWindow::rotate90(int sx, int sy, int fx, int fy)
{
    if(fx < 0) fx = 0;
    if(fy < 0) fy = 0;
    if(fx > img->bih.biWidth) fx = img->bih.biWidth;
    if(fy > img->bih.biHeight) fy = img->bih.biHeight;
    int m = abs(sx-fx);
    int n = abs(sy-fy);
   newimage::RGB*** t_rgb = (newimage::RGB***)calloc(std::max(n, m), sizeof(newimage::RGB**));
   for(int i = 0; i<std::max(n, m); i++){
       t_rgb[i] = (newimage::RGB**)calloc(std::max(n, m), sizeof(newimage::RGB*));
   }
   for(int j = 0; j<std::max(n, m); j++){
       for(int i = 0; i<std::max(n, m); i++){
           t_rgb[i][j] = new newimage::RGB;
            t_rgb[i][j]->blue = 255;
             t_rgb[i][j]->green = 255;
              t_rgb[i][j]->red = 255;
       }
   }
       for(int i = std::min(fy, sy); i<std::min(fy, sy)+n; i++){
           for(int j = std::min(fx, sx); j<std::min(fx, sx)+m; j++){
               if(n<m){
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->blue = img->rgb[i][j].blue;
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->green = img->rgb[i][j].green;
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->red = img->rgb[i][j].red;
               }
               else{
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->blue = img->rgb[i][j].blue;
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->green = img->rgb[i][j].green;
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->red = img->rgb[i][j].red;
               }
               img->rgb[i][j].blue = 255;
               img->rgb[i][j].green = 255;
               img->rgb[i][j].red = 255;
       }
   }

       int arr[4] = {0, 1, -1, 0};
       for(int i = std::min(fy, sy); i<std::min(fy, sy)+std::min(n, m); i++){
           for(int j = std::min(fx, sx); j<std::min(fx, sx)+std::min(n, m); j++){
               if(n<m){
                   int i1 = i - std::min(fy, sy);
                   int j1 = j - std::min(fx, sx);

                    int k = (i1)*arr[3] + (j1+ (m-n)/2)*arr[2] + std::max(n, m) - 1;
                    int l = (i1)*arr[1] + (j1 + (m-n)/2)*arr[0];

                    img->rgb[i][j+(m-n)/2].blue = t_rgb[k][l]->blue;
                    img->rgb[i][j+(m-n)/2].green = t_rgb[k][l]->green;
                    img->rgb[i][j+(m-n)/2].red = t_rgb[k][l]->red;
               }
               else{
                   int i1 = i - std::min(fy, sy);
                   int j1 = j - std::min(fx, sx);

                   int k = (i1 + (n-m)/2)*arr[3] + (j1)*arr[2] + std::max(n, m) - 1;
                   int l = (i1 + (n-m)/2)*arr[1] + (j1)*arr[0];

                   img->rgb[i+(n-m)/2][j].blue = t_rgb[k][l]->blue;
                   img->rgb[i+(n-m)/2][j].green = t_rgb[k][l]->green;
                   img->rgb[i+(n-m)/2][j].red = t_rgb[k][l]->red;
               }
           }
       }

   for(int i = 0; i<std::max(n, m); i++){
       for(int j = 0; j<std::max(n, m); j++){
           delete t_rgb[i][j];

       }
       free(t_rgb[i]);
   }
   free(t_rgb);
   GraphicsView->update(img->getMap());
    return;
}

void MainWindow::rotate180(int sx, int sy, int fx, int fy)
{
    if(fx < 0) fx = 0;
    if(fy < 0) fy = 0;
    if(fx > img->bih.biWidth) fx = img->bih.biWidth;
    if(fy > img->bih.biHeight) fy = img->bih.biHeight;

    int m = abs(sx-fx);
    int n = abs(sy-fy);

    int arr[4] = {-1, 0, 0, -1};
    for(int i = std::min(sy, fy); i < std::min(sy, fy)+n/2; i++){
        for(int j = std::min(sx, fx); j < std::min(sx, fx)+m; j++){

            newimage::RGB* t_rgb = new newimage::RGB;

            int k = (i-std::min(sy, fy))*arr[3] + (j-std::min(sx, fx))*arr[2] + std::min(sy, fy) + n - 1;
            int l = (i-std::min(sy, fy))*arr[1] + (j-std::min(sx, fx))*arr[0] + std::min(sx, fx) + m - 1;

            t_rgb->blue = img->rgb[i][j].blue;
            t_rgb->green = img->rgb[i][j].green;
            t_rgb->red = img->rgb[i][j].red;

            img->rgb[i][j].blue = img->rgb[k][l].blue;
            img->rgb[i][j].green = img->rgb[k][l].green;
            img->rgb[i][j].red = img->rgb[k][l].red;

            img->rgb[k][l].blue = t_rgb->blue;
            img->rgb[k][l].green = t_rgb->green;
            img->rgb[k][l].red = t_rgb->red;

            delete t_rgb;
        }
    }

    if(n % 2){
        for (int j = std::min(sx, fx); j < std::min(sx, fx)+m/2; j++){

            newimage::RGB* t_rgb = new newimage::RGB;

            int k = n/2 + std::min(sy, fy);  //(m/2+1)*arr[3] + (j-std::min(sx, fx))*arr[2] + n - 1;
            int l = (n/2)*arr[1] + (j-std::min(sx, fx))*arr[0] + std::min(sx, fx) + m - 1;

            t_rgb->blue = img->rgb[n/2+std::min(sy, fy)][j].blue;
            t_rgb->green = img->rgb[n/2+std::min(sy, fy)][j].green;
            t_rgb->red = img->rgb[n/2+std::min(sy, fy)][j].red;

            img->rgb[n/2+std::min(sy, fy)][j].blue = img->rgb[k][l].blue;
            img->rgb[n/2+std::min(sy, fy)][j].green = img->rgb[k][l].green;
            img->rgb[n/2+std::min(sy, fy)][j].red = img->rgb[k][l].red;

            img->rgb[k][l].blue = t_rgb->blue;
            img->rgb[k][l].green = t_rgb->green;
            img->rgb[k][l].red = t_rgb->red;

            delete t_rgb;
        }
    }
    GraphicsView->update(img->getMap());
     return;

}

void MainWindow::rotate270(int sx, int sy, int fx, int fy)
{
    if(fx < 0) fx = 0;
    if(fy < 0) fy = 0;
    if(fx > img->bih.biWidth) fx = img->bih.biWidth;
    if(fy > img->bih.biHeight) fy = img->bih.biHeight;
    int m = abs(sx-fx);
    int n = abs(sy-fy);
   newimage::RGB*** t_rgb = (newimage::RGB***)calloc(std::max(n, m), sizeof(newimage::RGB**));
   for(int i = 0; i<std::max(n, m); i++){
       t_rgb[i] = (newimage::RGB**)calloc(std::max(n, m), sizeof(newimage::RGB*));
   }
   for(int j = 0; j<std::max(n, m); j++){
       for(int i = 0; i<std::max(n, m); i++){
           t_rgb[i][j] = new newimage::RGB;
            t_rgb[i][j]->blue = 255;
             t_rgb[i][j]->green = 255;
              t_rgb[i][j]->red = 255;
       }
   }
       for(int i = std::min(fy, sy); i<std::min(fy, sy)+n; i++){
           for(int j = std::min(fx, sx); j<std::min(fx, sx)+m; j++){
               if(n<m){
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->blue = img->rgb[i][j].blue;
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->green = img->rgb[i][j].green;
                    t_rgb[i-std::min(sy, fy)+(m-n)/2][j-std::min(fx, sx)]->red = img->rgb[i][j].red;
               }
               else{
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->blue = img->rgb[i][j].blue;
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->green = img->rgb[i][j].green;
                   t_rgb[i-std::min(sy, fy)][j-std::min(fx, sx)+(n-m)/2]->red = img->rgb[i][j].red;
               }
               img->rgb[i][j].blue = 255;
               img->rgb[i][j].green = 255;
               img->rgb[i][j].red = 255;
       }
   }

       int arr[4] = {0, -1, 1, 0};
       for(int i = std::min(fy, sy); i<std::min(fy, sy)+std::min(n, m); i++){
           for(int j = std::min(fx, sx); j<std::min(fx, sx)+std::min(n, m); j++){
               if(n<m){
                   int i1 = i - std::min(fy, sy);
                   int j1 = j - std::min(fx, sx);

                    int k = (i1)*arr[3] + (j1+ (m-n)/2)*arr[2];
                    int l = (i1)*arr[1] + (j1 + (m-n)/2)*arr[0] + std::max(n, m) - 1;

                    img->rgb[i][j+(m-n)/2].blue = t_rgb[k][l]->blue;
                    img->rgb[i][j+(m-n)/2].green = t_rgb[k][l]->green;
                    img->rgb[i][j+(m-n)/2].red = t_rgb[k][l]->red;
               }
               else{
                   int i1 = i - std::min(fy, sy);
                   int j1 = j - std::min(fx, sx);

                   int k = (i1 + (n-m)/2)*arr[3] + (j1)*arr[2];
                   int l = (i1 + (n-m)/2)*arr[1] + (j1)*arr[0] + std::max(n, m) - 1;

                   img->rgb[i+(n-m)/2][j].blue = t_rgb[k][l]->blue;
                   img->rgb[i+(n-m)/2][j].green = t_rgb[k][l]->green;
                   img->rgb[i+(n-m)/2][j].red = t_rgb[k][l]->red;
               }
           }
       }

   for(int i = 0; i<std::max(n, m); i++){
       for(int j = 0; j<std::max(n, m); j++){
           delete t_rgb[i][j];

       }
       free(t_rgb[i]);
   }
   free(t_rgb);
   GraphicsView->update(img->getMap());
    return;
}












