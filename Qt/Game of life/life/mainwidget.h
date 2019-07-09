#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include "renderarea.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_quit_clicked();
    void on_start_clicked();

    void on_stop_clicked();

    void on_clean_clicked();

private:
    QTimer *timer;
    RenderArea *renderArea;
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
