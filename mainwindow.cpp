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
    mainScene = new MyScene(10, ":/images/background", ":/images/none");
    mainScene->setImage(":/images/chest");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);


    //set up combobox
    ui->comboBox->addItem("None",":/images/none");
    ui->comboBox->addItem("Chest",":/images/chest");
    ui->comboBox->addItem("Dirt",":/images/dirt");
}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //set image mainScene to current image in comboBox
    mainScene->setImage(ui->comboBox->itemData(index).toString());

}

void MainWindow::on_GridOnOff_stateChanged(int arg1)
{
    //hide or show grid
    if(arg1 == 0)
        mainScene->hideGrid();
    else
        mainScene->showGrid();
}

void MainWindow::on_pushButtonFill_clicked()
{
    //fill the screen with images
    mainScene->paintImagesRect(QPointF(0,0),QPointF(800,600));
}

void MainWindow::on_pushButtonRemoveNone_clicked()
{
    //remove all none images
    mainScene->removeNone();
}
