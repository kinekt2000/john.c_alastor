#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QDebug>

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_first_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Загрузка", "/home/", "*.bmp");
    if (path == nullptr){
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при открытии фалйа");
        return;
    }
    ui->first_path->setText(path);
}

void ConnectDialog::on_second_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Загрузка", "/home/", "*bmp");
    if (path == nullptr){
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при открытии фалйа");
        return;
    }
    ui->second_path->setText(path);
}

void ConnectDialog::on_accept_clicked()
{
    first = ui->first_path->text();
    second = ui->second_path->text();
    if (first.isEmpty() || second.isEmpty())
        this->done(0);
    else
        this->done(1);
}
void ConnectDialog::on_reject_clicked()
{
    this->done(0);
}
