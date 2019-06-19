#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QPalette>
#include <QMessageBox>
#include <string>
#include "image.h"
#include "newimagedialog.h"
#include "grapher.h"
#include "createframedialog.h"
#include "imageinfo.h"
#include "about.h"
#include "connectdialog.h"


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
    void on_new_file_triggered();
    void on_save_file_triggered();
    void on_open_file_triggered();
    void on_about_image_triggered();
    void on_about_triggered();

    void on_Fill_stateChanged(int arg1);
    void on_Width_valueChanged(int arg1);
    void on_foreground_clicked();
    void on_background_clicked();
    void show_coordinates(int x, int y);

    void on_Hexagon_clicked();
    void on_Copy_clicked();
    void on_Recolor_clicked();
    void on_Pen_clicked();

    void pen();
    void hexagon(int sx, int sy, double radius, double angle);
    void copy(int sx, int sy, int fx, int fy, int nx, int ny);
    void recolor(int sx, int sy, int fx, int fy);
    void on_Frame_clicked();


    void on_quit_triggered();

    void on_Connect_clicked();

private:
    QColor fore = QColor(0, 0, 0);
    QColor back = QColor(255, 255, 255);
    Image *img;                 // изображение
    Grapher *grapher;           // видимые операции
    bool fill = false;          // заливка
    int thick = 10;              // толщина линий
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
