#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QPalette>
#include <QString>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <mygraphicsview.h>
#include "newimage.h"
#include "dialog.h"
#include "anglechoice.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void show_coordinates(int x, int y);   // отслеживание координат

    void on_open_file_triggered();  // открытие файла
    void on_save_file_triggered();  // сохранение файла

    void on_color_clicked();  // выбор цвета
    void on_in_color_clicked(); //выбор цвета заливки

    void on_incolor_clicked(bool checked); // наличие заливки

    void on_width_valueChanged(int arg1);  // ширина линий

    void on_func_1_clicked();
    void rectangl(int sx, int sy, int fx, int fy);

    void on_func_2_clicked();
    void circle(int sx, int sy, int fx, int fy);


    void on_func_3_clicked();
    void frame_1(int width, QColor col);
    void frame_2(int width, QColor col, QColor in_col);
    void frame_3(int width, QColor col, QColor in_col);
    void frame_4(int width, QColor col);

    void on_func_4_clicked();
    void rotate90(int sx, int sy, int fx, int fy);
    void rotate180(int sx, int sy, int fx, int fy);
    void rotate270(int sx, int sy, int fx, int fy);


signals:
   // void rotate_signal(int, int, int, int);

private:
     QColor col = QColor(0, 0, 0);
     QColor in_col = QColor(0, 0, 0);
    newimage *img;   // изображение
    MyGraphicsView *GraphicsView;   // видимые операции
    bool incolor = false;
    int width = 10;
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
