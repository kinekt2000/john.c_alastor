#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    renderArea = new RenderArea;
    timer = new QTimer;

    ui->setupUi(this);
    ui->field->addWidget(renderArea);
    ui->field->setAlignment(renderArea, Qt::AlignCenter);

    timer->setInterval(1);
    timer->start();

    this->resize(RSIZE+50, RSIZE+100);


    connect(timer, SIGNAL(timeout()), renderArea, SLOT(draw()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_quit_clicked()
{
    QApplication::exit(0);
}
