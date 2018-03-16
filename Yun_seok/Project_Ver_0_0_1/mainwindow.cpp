#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItem>
#include <QPalette>
#include <QProcess>
QGraphicsScene * scene;

QGraphicsPixmapItem * LED_1;
static int speed=0;
void change_image(QGraphicsPixmapItem * image);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QIcon UP_ARROW("UP_ARROW.png");
    QIcon DOWN_ARROW("DOWN_ARROW.png");
    QIcon RIGHT_ARROW("RIGHT_ARROW.png");
    QIcon LEFT_ARROW("LEFT_ARROW.png");

    ui->setupUi(this);
    ui->progressBar->setValue(0);


    ui->Acc_button->setIcon(UP_ARROW);
    ui->Break_button->setIcon(DOWN_ARROW);
    ui->Left_button->setIcon(LEFT_ARROW);
    ui->Right_button->setIcon(RIGHT_ARROW);


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

void MainWindow::on_Acc_button_clicked()
{
    ui->lineEdit->setText("ACC Button");
    if(speed<=100) speed+=20;
    ui->progressBar->setValue(speed);
}

void MainWindow::on_Break_button_clicked()
{
    ui->lineEdit->setText("break Button");
    if(speed>0)speed-=20;
    ui->progressBar->setValue(speed);
}

void MainWindow::on_button_A_clicked()
{
    change_image(LED_1);


    QProcess Process;
    QString program = "TCP_Client";
    QStringList arguments;

    arguments<<"192.168.0.90"<<"A button"<<"7";
    //Process=new QProcess(this);

    Process.start(program,arguments);

}

void change_image(QGraphicsPixmapItem * image){
    static int count=0;
    count++;
    QPixmap LED_RED("LED_RED.png");
    QPixmap LED_GREEN("LED_GREEN.png");
    if(count%2==0) image->setPixmap(LED_GREEN);
    else image->setPixmap(LED_RED);
}
