#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QPoint>



#define OFF 0
#define ROTATE90 1
#define ROTATE180 2
#define ROTATE270 3
#define RECT 4
#define CIRC 5
#define FR1 6
#define FR2 7
#define FR3 8
#define FR4 9



typedef struct{
    int x;
    int y;
}coordinate;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    coordinate start;
    coordinate finish;

    int func = OFF; // Текущая функция

    void update(QPixmap); //Функция помещения объекта Pixmap в сцену;
    explicit MyGraphicsView(QWidget *parent = nullptr);
    ~MyGraphicsView();

signals:
    void mouse_track_signal(int x, int y);
    void rotate_signal_90(int, int, int, int);
    void rotate_signal_180(int, int, int, int);
    void rotate_signal_270(int, int, int, int);
    void rect_signal(int, int, int, int);
    void circ_signal(int, int, int, int);

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool mouse_p;
    QGraphicsItemGroup *rect; // Группа, в которую будут объединяться линии для рисования прямоугольника
    QGraphicsScene *scene; //Сцена на которую указывает graphicsview и на которой будет визуально отображаться выбранная область
    void freeGroup(QGraphicsItemGroup *object); //Функция для удаления всех элементов из группы
};

#endif // MYGRAPHICSVIEW_H
