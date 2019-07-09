#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    renderArea = new RenderArea;
    renderArea->setFrameStyle(0);
    timer = new QTimer;

    ui->setupUi(this);
    ui->field->addWidget(renderArea);
    ui->field->setAlignment(renderArea, Qt::AlignCenter);

    timer->setInterval(90);

    this->resize(WSIZE+50, HSIZE+100);
    ui->quit->setShortcut(Qt::Key_Escape);

    connect(timer, SIGNAL(timeout()), renderArea, SLOT(draw()));
}

MainWidget::~MainWidget()
{
    delete renderArea;
    delete timer;
    delete ui;
}

void MainWidget::on_quit_clicked()
{
    QApplication::exit(0);
}

void MainWidget::on_start_clicked()
{
    timer->start();
}

void MainWidget::on_stop_clicked()
{
    timer->stop();
}

void MainWidget::on_clean_clicked()
{
    renderArea->clean();
}
