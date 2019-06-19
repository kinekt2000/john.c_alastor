#ifndef ANGLECHOICE_H
#define ANGLECHOICE_H

#include <QDialog>

namespace Ui {
class AngleChoice;
}

class AngleChoice : public QDialog
{
    Q_OBJECT

public:
    explicit AngleChoice(QWidget *parent = 0);
    ~AngleChoice();

private slots:


    void on_angle90_clicked();

    void on_angle180_clicked();

    void on_angle270_clicked();

private:
    Ui::AngleChoice *ui;
};

#endif // ANGLECHOICE_H
