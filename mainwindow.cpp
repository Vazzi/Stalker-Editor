#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QtGui>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyScene *mainSceen = new MyScene;

    ui->graphicsView->setScene(mainSceen);
    ui->graphicsView->setSceneRect(0,0,800,600);


}



MainWindow::~MainWindow()
{
    delete ui;
}
