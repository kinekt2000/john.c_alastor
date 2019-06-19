#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    grapher = new Grapher;
    grapher->scene->setSceneRect(0, 0, 512, 512);
    img = new Image;
    ui->setupUi(this);
    ui->Field->addWidget(grapher);

    QPalette forecolor = ui->foreground->palette();                 // Изъятие палитры из кнопки осн. цвета
    QPalette backcolor = ui->background->palette();                 // Изъятие палитры из кнопки доп. цвета
    forecolor.setColor(QPalette::Button, QColor(0, 0, 0));          // Изменение палитры кнопки осн. цвета (на черный)
    backcolor.setColor(QPalette::Button, QColor(255, 255, 255));    // Изменение палитры кнопки доп. цвета (на белый )
    ui->foreground->setPalette(forecolor);                          // Применение измененной палитры к кнопке осн. цвета
    ui->background->setPalette(backcolor);                          // Применение измененной палитры к кнопке доп. цвета
    ui->foreground->update();                                       // Обновление кнопки осн. цвета
    ui->background->update();                                       // Обновление кнопки доп. цвета

    connect(grapher, SIGNAL(copy_signal(int, int, int, int, int, int)), this, SLOT(copy(int, int, int, int, int, int)));
    connect(grapher, SIGNAL(square_signal(int, int, int, int)), this, SLOT(recolor(int, int, int, int)));
    connect(grapher, SIGNAL(hexagon_signal(int, int, double, double)), SLOT(hexagon(int, int, double, double)));

    connect(grapher, SIGNAL(pen_signal()), this, SLOT(pen())); // Соединение сигнала с мыши (при условии выбранной функции) для вызова пера
    connect(grapher, SIGNAL(mouse_track_signal(int, int)), this, SLOT(show_coordinates(int, int))); // Соединение сигнала с мыши для вывода координат в статусбар
}

MainWindow::~MainWindow()
{
    delete grapher;
    delete img;
    delete ui;
}


void MainWindow::on_about_triggered()
{
    About *abt = new About;
    abt->exec();
    delete abt;
    return;
}


void MainWindow::on_about_image_triggered()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    ImageInfo *info = new ImageInfo;
    info->update(img);
    info->exec();
    delete info;
    return;
}


void MainWindow::on_new_file_triggered()
{
    NewImageDialog *imageSize = new NewImageDialog;             // Вызов окна создания нового изображения
    imageSize->exec();
    if (imageSize->result()){
        img->newImage(imageSize->width, imageSize->height);
        grapher->update(img->getMap());
    }
    grapher->scene->setSceneRect(0, 0, imageSize->width, imageSize->height);
    delete imageSize;
    return;
}


void MainWindow::on_save_file_triggered()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "Сохранение", "/home/", "*.bmp");
    path += ".bmp";
    int error = img->saveImage(path.toLocal8Bit().data());
    if(error){
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при сохранении файла");
        return;
    }
}


void MainWindow::on_open_file_triggered()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Загрузка", "/home/", "*.bmp");
    if(path == nullptr) return;
    int error = img->loadImage(path.toLocal8Bit().data());
    if (error == 1){
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при чтении файла");
        return;
    }
    if (error == 2){
        QMessageBox::critical(this, "Ошибка", "Файл не является BMP изображением");
        return;
    }
    if (error == 3){
        QMessageBox::warning(this, "Ошибка", "Размер изображения должен быть не больше 8192x6144px");
        return;
    }
    if (error == 4){
        QMessageBox::critical(this, "Ошибка", "Программа не поддерживает изображения с таблицей цветов");
        return;
    }
    grapher->scene->setSceneRect(0, 0, img->bih.biWidth, img->bih.biHeight);
    grapher->update(img->getMap());
}


void MainWindow::on_Fill_stateChanged(int arg1)
{
    if (arg1) fill = true;
    else fill = false;
}


void MainWindow::on_Width_valueChanged(int arg1)
{
    thick = arg1;
}


void MainWindow::on_foreground_clicked()    // Изменение основного цвета в рантайме (аналогично конструктору)
{
    fore = QColorDialog::getColor();
    if(!fore.isValid()) return;
    QPalette forecolor = ui->foreground->palette();
    forecolor.setColor(QPalette::Button, fore);
    ui->foreground->setPalette(forecolor);
    ui->foreground->update();
}


void MainWindow::on_background_clicked()    // Изменение дополнительного цвета в рантайме (аналогично конструктору)
{
    back = QColorDialog::getColor();
    if(!back.isValid()) return;
    QPalette backcolor = ui->background->palette();
    backcolor.setColor(QPalette::Button, back);
    ui->background->setPalette(backcolor);
    ui->background->update();
}


void MainWindow::on_Hexagon_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    grapher->copy = 0;
    grapher->func = HEXAGON;
}


void MainWindow::on_Copy_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    grapher->copy = 0;
    grapher->func = COPY;
}


void MainWindow::on_Recolor_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    grapher->copy = 0;
    grapher->func = RECOLOR;
}



void MainWindow::on_Frame_clicked()
{
    if(img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    grapher->copy = 0;
    if(img->bih.biWidth < 50 || img->bih.biHeight < 50){
        QMessageBox::warning(this, "Ошибка", "Каждая сторона изображения должна быть больше 50px");
        return;
    }

    CreateFrameDialog *frameParameters = new CreateFrameDialog;
    frameParameters->setFixedSize(312, 253);
    frameParameters->exec();

    int error = 0;
    if (frameParameters->result()){
        switch (frameParameters->func){
        case BRANCH:
            error = img->createFrame(fore, back, fill, BRANCH, frameParameters->angle);
            break;

        case RIM:
            error = img->createFrame(fore, back, fill, RIM, frameParameters->density);
            break;

        case CROSS:
            error = img->createFrame(fore, back, fill, CROSS, (frameParameters->radius*200)/SQR_SIDE);
            break;
        }
    }
    delete frameParameters;
    if(error){
        qDebug() << "error";
        return;
    }
    grapher->update(img->getMap());
    return;
}


void MainWindow::on_Pen_clicked()
{
    if (img->bih.biWidth == 0 || img->bih.biHeight == 0){
        QMessageBox::warning(this, "Ошибка", "Отсутствует изображение");
        return;
    }
    grapher->copy = 0;
    grapher->func = PEN;
}


void MainWindow::show_coordinates(int x, int y){    // Конструирование строк по значениям сообщенным в слот и их вывод
    std::string str_x = std::to_string(x);
    std::string str_y = std::to_string(y);
    ui->statusBar->showMessage(QString::fromStdString("x = " + str_x + "; " + "y = " + str_y + ";"));
}


void MainWindow::pen(){ // Рисует мелкие отрезки пока зажата мышь
    int error = img->setPart(grapher->start.x, grapher->start.y, grapher->finish.x, grapher->finish.y, fore, thick);
    if(error){
        qDebug() << "error";
        return;
    }
    grapher->update(img->getMap());
}


void MainWindow::hexagon(int sx, int sy, double radius, double angle){
    int error = img->paintHexagon(sx, sy, radius, angle, thick, fill, fore, back);
    if(error){
        qDebug() << "error";
        return;
    }
    grapher->update(img->getMap());
}


void MainWindow::copy(int sx, int sy, int fx, int fy, int nx, int ny){
    int error = img->copyRect(sx, sy, fx, fy, nx, ny);
    if (error){
        qDebug() << "position error";
        return;
    }
    grapher->update(img->getMap());
}


void MainWindow::recolor(int sx, int sy, int fx, int fy){
    int error = img->recolorRect(sx, sy, fx, fy, fore, back);
    if (error){
        qDebug() << "error";
        return;
    }
    grapher->update(img->getMap());
}













void MainWindow::on_quit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_Connect_clicked()
{
    ConnectDialog *dlg = new ConnectDialog;
    dlg->exec();
    int error = 0;
    if(dlg->result()){
        error = img->connect(dlg->first.toLocal8Bit().data(), dlg->second.toLocal8Bit().data());
    }
    if(error)
        qDebug() << "read error";
    delete dlg;
    grapher->scene->setSceneRect(0, 0, img->bih.biWidth, img->bih.biHeight);
    grapher->update(img->getMap());
    return;
}
