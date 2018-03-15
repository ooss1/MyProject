#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItem>
QGraphicsScene * scene;

QGraphicsPixmapItem * LED_1;
static int speed=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->progressBar->setValue(0);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    QPixmap LED("LED_GREEN.png");
    LED_1 = scene->addPixmap(LED);
    LED_1->setPos(3,3);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_A_clicked()
{
    QPixmap LED("LED_RED.png");
    LED_1 = scene->addPixmap(LED);
    LED_1->setPos(3,3);
}

void MainWindow::on_Acc_button_clicked()
{
    ui->lineEdit->setText("ACC Button");
    if(speed<=100) speed+=20;
    ui->progressBar->setValue(speed);
}

void MainWindow::on_break_button_clicked()
{
    ui->lineEdit->setText("break Button");
    if(speed>0)speed-=20;
    ui->progressBar->setValue(speed);
}
