#ifndef CREATEFRAMEDIALOG_H
#define CREATEFRAMEDIALOG_H

#include <QDialog>
#include "grapher.h"

#define OFF 0
#define BRANCH 1
#define RIM 2
#define CROSS 3
#define SQR_SIDE 88

namespace Ui {
class CreateFrameDialog;
}

class CreateFrameDialog : public QDialog
{
    Q_OBJECT

public:
    double radius = 0;
    int density = 1;
    double angle = 30 * PI / 180;
    int func = OFF;
    explicit CreateFrameDialog(QWidget *parent = nullptr);
    ~CreateFrameDialog();


private slots:
    void on_apply_clicked();
    void on_reject_clicked();

    void on_branches_clicked();
    void on_angle_value_valueChanged(int value);

    void on_line_frame_clicked();
    void on_density_value_valueChanged(int value);

    void on_kelt_cross_clicked();
    void on_radius_value_valueChanged(int value);

private:
    Grapher *map;
    Ui::CreateFrameDialog *ui;
    void drawBranch(double angle);
    void drawLineFrame(int density);
    void drawKeltCross(double radius);
};

#endif // CREATEFRAMEDIALOG_H
