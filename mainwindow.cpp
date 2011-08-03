#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include <QtGui>

MyScene *mainScene;
QGraphicsScene *secondScene;
QGraphicsPixmapItem *item;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //set up mainscene
    mainScene = new MyScene(10, ":/images/background", ":/images/none");
    mainScene->setImage(":/images/chest");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,800,600);

    //set up secondScene
    secondScene = new QGraphicsScene;
    //secondScene->setBackgroundBrush(Qt::);
    item = new QGraphicsPixmapItem;
    item = secondScene->addPixmap(QString(":/images/none"));
    ui->graphicsView_2->setScene(secondScene);
    ui->graphicsView_2->setSceneRect(0,0,80,80);
    secondScene->setBackgroundBrush(Qt::lightGray);

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
    //show image in secondScene
    item->setPixmap(ui->comboBox->itemData(index).toString());
    //refresh labels
    ui->labelWidth->setText(QString::number(item->pixmap().width()) + "px");
    ui->labelHeight->setText(QString::number(item->pixmap().height())+ "px");
    //resize if it is necessary
    if(item->pixmap().width() > 78)
        item->setPixmap(item->pixmap().scaledToHeight(78,Qt::FastTransformation));
    else if(item->pixmap().height() > 78)
        item->setPixmap(item->pixmap().scaledToWidth(78,Qt::FastTransformation));
    //set pixmap position into the midle of graphicsview
    int x,y;
    x = (ui->graphicsView_2->width()/2) - (item->pixmap().width()/2);
    y = (ui->graphicsView_2->height()/2) - (item->pixmap().height()/2);
    item->setPos(x,y);



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


void MainWindow::on_backgroundOnOff_toggled(bool checked)
{
    mainScene->showHideBackgroudImage(checked);
}

void MainWindow::on_GridOnOff_toggled(bool checked)
{
    mainScene->showHideGrid(checked);
}

void MainWindow::on_cursorOnOff_toggled(bool checked)
{
    if(checked)
        ui->graphicsView->setCursor(Qt::ArrowCursor);
    else
        ui->graphicsView->setCursor(Qt::BlankCursor);
}
