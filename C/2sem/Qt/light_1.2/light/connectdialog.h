#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    QString first;
    QString second;
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

private slots:
    void on_first_clicked();

    void on_second_clicked();

    void on_accept_clicked();

    void on_reject_clicked();

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
