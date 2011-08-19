#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "menu.h"
#include <QtGui>


MyScene *mainScene;
QGraphicsScene *secondScene;
QGraphicsPixmapItem *item;
Menu *m;
QTimer *timer;
int sceneWidth;
bool LayerZLock;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    m = new Menu(this);
    //set up mainscene
    sceneWidth=1000;
    mainScene = new MyScene(10, ":/images/none", ":/images/background1", sceneWidth);
    mainScene->setImage(":/images/chest");
    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setSceneRect(0,0,sceneWidth,600);


    //set up secondScene
    secondScene = new QGraphicsScene;
    item = new QGraphicsPixmapItem;
    item = secondScene->addPixmap(QString(":/images/none"));
    ui->graphicsView_2->setScene(secondScene);
    ui->graphicsView_2->setSceneRect(0,0,80,80);
    secondScene->setBackgroundBrush(Qt::lightGray);

    //set up combobox with items
    ui->comboBox->addItem("**None**",":/images/none");
    ui->comboBox->addItem("**Eraser**",":/images/rubber");
    ui->comboBox->addItem("Chest",":/images/chest");
    ui->comboBox->addItem("Dirt",":/images/dirt");
    ui->comboBox->addItem("Stone",":/images/stone");
    ui->comboBox->addItem("Wood",":/images/wood");
    ui->comboBox->addItem("Online",":/images/online");

    //set up combobox with backgrounds
    ui->comboBox_2->addItem("background1",":/images/background");

    //set up combobox with layres
    ui->comboBoxLayer->addItem("all *");
    for(int i = 1; i < 11; i++)
        ui->comboBoxLayer->addItem(QString::number(i) + ". layer");

    timer = new QTimer;
    timer->setInterval(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(labelupdate()));
    timer->start();

    //set up slider
    ui->horizontalSlider->setMinimum(400);
    ui->horizontalSlider->setMaximum(sceneWidth / 2);


}


MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //set image mainScene to current image in comboBox
    mainScene->setImage(ui->comboBox->itemData(index).toString());
    mainScene->setItemZValue(ui->spinBox->value());
    //show image in secondScene
    item->setPixmap(ui->comboBox->itemData(index).toString());
    //refresh labels
    if(ui->comboBox->itemData(index).toString()==":/images/rubber"){
        ui->labelWidth->setText("10 px");
        ui->labelHeight->setText("10 px");
    }
    else{
        ui->labelWidth->setText(QString::number(item->pixmap().width()) + " px");
        ui->labelHeight->setText(QString::number(item->pixmap().height())+ " px");
        //resize if it is necessary
        if(item->pixmap().width() > 78)
            item->setPixmap(item->pixmap().scaledToHeight(78,Qt::FastTransformation));
        else if(item->pixmap().height() > 78)
            item->setPixmap(item->pixmap().scaledToWidth(78,Qt::FastTransformation));
    }

    //set pixmap position into the midle of graphicsview
    int x,y;
    x = (ui->graphicsView_2->width()/2) - (item->pixmap().width()/2);
    y = (ui->graphicsView_2->height()/2) - (item->pixmap().height()/2);
    item->setPos(x,y);

    //set focus on scene
    ui->graphicsView->setFocus();

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

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    mainScene->setBackground(ui->comboBox_2->itemData(index).toString());
    ui->graphicsView->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    m->show();
}

void MainWindow::labelupdate(){
    ui->xlabel->setText(QString::number(mainScene->xyposition.x()));
    ui->ylabel->setText(QString::number(mainScene->xyposition.y()));
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->graphicsView->centerOn(QPoint(position,300));
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    mainScene->setItemZValue(arg1);
    ui->graphicsView->setFocus();
}

void MainWindow::on_comboBoxLayer_currentIndexChanged(int index)
{
    if(LayerZLock){
        if(index!=0){
            ui->spinBox->setValue(index);
        }
    }
    mainScene->showLayer(index);
    ui->graphicsView->setFocus();
}

void MainWindow::on_checkBoxLayerZLock_stateChanged(int arg1)
{
        LayerZLock=arg1;
}
