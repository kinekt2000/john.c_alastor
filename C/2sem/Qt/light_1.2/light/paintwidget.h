#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();
    void paintEvent(QPaintEvent* event);

signals:

public slots:
};

#endif // PAINTWIDGET_H
