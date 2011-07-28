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
    mainScene->setImage(":/images/chest");

    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);
    //set up combobox
    ui->comboBox->addItem("Chest",":/images/chest");
    ui->comboBox->addItem("Dirt",":/images/dirt");
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

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //set image mainScene to current image in comboBox
    mainScene->setImage(ui->comboBox->itemData(index).toString());
}
