#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QImage>
#include <QGraphicsView>
#include <QString>
#include <QFileDialog>
#include "renderarea.h"

#define FRAMERATE 1000

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    double dA = 1.0;
    double dB = 0.5;
    double feed = 0.045;
    double kill = 0.062;

    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Start_clicked();
    void on_Stop_clicked();
    void execute();
    void on_Quit_clicked();
    void on_Load_clicked();

private:
    void draw();
    QTimer *tmr;
    RenderArea *renderArea;
    Ui::Widget *ui;
};

#endif // WIDGET_H
