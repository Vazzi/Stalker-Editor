#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "menu.h"
#include <QtGui>

Menu *menuForm;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    menuForm = new Menu(this);

    //set up m_mainScene
    m_mainScene = new MyScene(10, ":/images/none", 1000);
    ui->graphicsView->setScene(m_mainScene);
    ui->graphicsView->setSceneRect(0,0,1000,600);

    //set up slider
    ui->horizontalSlider->setMinimum(400);
    ui->horizontalSlider->setMaximum(1000 - 400);


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
    ui->comboBox_2->addItem("background1",":/images/background");

    //set up combobox with layres
    ui->comboBoxLayer->addItem("all *");
    for(int i = 1; i < 11; i++)
        ui->comboBoxLayer->addItem(QString::number(i) + ". layer");


}


MainWindow::~MainWindow()
{
    delete item;
    delete secondScene;
    delete m_mainScene;
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //set image m_mainScene to current image in comboBox
    m_mainScene->setImage(ui->comboBox->itemData(index).toString());
    m_mainScene->setItemZValue(ui->spinBox->value());
    //show image in secondScene
    item->setPixmap(ui->comboBox->itemData(index).toString());
    //refresh labels
    //if user select **eraser** set the specific objects
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
    m_mainScene->fill();

}

void MainWindow::on_pushButtonRemoveNone_clicked()
{
    //remove all none images
    m_mainScene->removeNone();
    ui->graphicsView->update();


}


void MainWindow::on_backgroundOnOff_toggled(bool checked)
{
    //set background on or off
    m_mainScene->showHideBackgroudImage(checked);
    ui->graphicsView->setFocus();

}

void MainWindow::on_GridOnOff_toggled(bool checked)
{
    //show or hide GRID
    m_mainScene->showHideGrid(checked);
    ui->graphicsView->setFocus();
}

void MainWindow::on_cursorOnOff_toggled(bool checked)
{
    //set cursor
    //doesnt work in Windows OS
    if(checked)
        ui->graphicsView->setCursor(Qt::ArrowCursor);
    else
        ui->graphicsView->setCursor(Qt::BlankCursor);
    ui->graphicsView->setFocus();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    //select background
    m_mainScene->setBackground(ui->comboBox_2->itemData(index).toString());
    ui->graphicsView->setFocus();
}

void MainWindow::on_pushButton_clicked()
{
    //show menu form
    menuForm->show();
    ui->graphicsView->setFocus();
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    //move with scene in graphicsView
    ui->graphicsView->centerOn(QPoint(position,300));
    ui->graphicsView->setFocus();
}

void MainWindow::on_spinBox_valueChanged(int arg1){
    //set z value of item
    m_mainScene->setItemZValue(arg1);
    ui->graphicsView->setFocus();
}

void MainWindow::on_comboBoxLayer_currentIndexChanged(int index){
    //show only selected layer or all if 0
    //if layer & z value is locked it change value of ZValue spinbox
    if(LayerZLock){
        if(index!=0){
            ui->spinBox->setValue(index);
        }
    }
    m_mainScene->showLayer(index);
    ui->graphicsView->setFocus();
}

void MainWindow::on_checkBoxLayerZLock_stateChanged(int arg1){
    //set Layer & Z Value lock
    LayerZLock=arg1;
}

void MainWindow::clearForm(){
    //slot witch clears the scene
    m_mainScene->clearlyNewScene(1500);
    ui->graphicsView->setSceneRect(0,0,1500,600);
    ui->horizontalSlider->setMaximum(1500 - 400);
    ui->graphicsView->update();
}

