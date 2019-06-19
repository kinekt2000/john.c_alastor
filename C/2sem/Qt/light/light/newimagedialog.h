#ifndef NEWIMAGEDIALOG_H
#define NEWIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class NewImageDialog;
}

class NewImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewImageDialog(QWidget *parent = nullptr);
    ~NewImageDialog();

public:
    int32_t width = 0;
    int32_t height = 0;

private slots:
    void on_Cancel_clicked();
    void on_Apply_clicked();

private:

    Ui::NewImageDialog *newimage;
};

#endif // NEWIMAGEDIALOG_H
