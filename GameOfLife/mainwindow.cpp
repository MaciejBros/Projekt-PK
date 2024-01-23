#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}






void MainWindow::on_pushButton_2_clicked()
{
    ui->graphicsView->scene()->clear();
    int windowHeight = ui->graphicsView->height();
    int windowWidth = ui->graphicsView->width();

    int width = windowWidth / ui->spinBoxWidth->value();
    int height = windowHeight / ui->spinBoxHeight->value();



    for (int x=0; x<=600; x+=width)
        scene->addLine(x,0,x,600, QPen(Qt::black));

    for (int y=0; y<=600; y+=height)
        scene->addLine(0,y,600,y, QPen(Qt::black));

    ui->graphicsView->
}
