#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QtGui>

MyScene *mainScene;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //set up scene
    ui->setupUi(this);
    mainScene = new MyScene(10, ":/images/background");

    mainScene->setImage(":/images/dirt");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);
    //set up combobox
    ui->comboBox->addItem("Chest",":/images/chest");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //set text on label how many pictures are in the mainscene
    ui->label->setText(mainScene->getImages());
}
