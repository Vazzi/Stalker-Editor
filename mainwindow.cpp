#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QtGui>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyScene *mainScene = new MyScene;
    mainScene->AddTexture(":/images/chest");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(update()));
    timer->start(10);
}



MainWindow::~MainWindow()
{
    delete ui;
}
