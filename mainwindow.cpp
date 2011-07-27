#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QtGui>

MyScene *mainScene;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainScene = new MyScene(10);
    mainScene->AddTexture(":/images/chest");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);
    ui->comboBox->addItem("None","None");
    ui->comboBox->addItem("Chest",":/images/chest");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(update()));
    timer->start(10);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(QString::number(mainScene->getImages()));
}
