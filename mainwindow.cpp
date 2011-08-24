#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myscene.h"
#include "dialognewmap.h"
#include <QtGui>

DialogNewMap *newMap;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

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

    newMap =new DialogNewMap(this);
    connect(newMap,SIGNAL(newAccepted(int,QString)),this,SLOT(clearForm(int,QString)));


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


void MainWindow::on_pushButtonFill_clicked(){
    //fill the screen with images
    m_mainScene->fill();
}

void MainWindow::on_pushButtonRemoveNone_clicked(){
    //remove all none images
    m_mainScene->removeNone();
    ui->graphicsView->update();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index){
    //select background
    m_mainScene->setBackground(ui->comboBox_2->itemData(index).toString(),ui->checkBoxBackgRepeat->checkState());
    ui->graphicsView->setFocus();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position){
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

void MainWindow::clearForm(int width,QString mapName){

    //slot witch clears the scene
    m_mainScene->clearlyNewScene(width);
    ui->graphicsView->setSceneRect(0,0,width,600);
    ui->horizontalSlider->setMaximum(width - 400);
    ui->graphicsView->update();
    ui->actionShow_Grid->setChecked(true);
    ui->actionShow_Background->setChecked(true);
    ui->checkBoxBackgRepeat->setChecked(false);

}


void MainWindow::on_actionNew_triggered(){
    newMap->show();
}

void MainWindow::on_actionQuit_triggered(){
    if(QMessageBox::question(this,"Quit", "Really want to quit?",QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes){
        this->close();
    }
}



void MainWindow::on_actionShow_Grid_triggered(bool checked){
    //show or hide GRID
    m_mainScene->showHideGrid(checked);
}

void MainWindow::on_actionShow_Background_triggered(bool checked){
    //set background on or off
    m_mainScene->showHideBackgroudImage(checked);
}

void MainWindow::on_actionShow_Cursor_triggered(bool checked){
    //doesnt work in Windows OS
    if(checked)
        ui->graphicsView->setCursor(Qt::ArrowCursor);
    else
        ui->graphicsView->setCursor(Qt::BlankCursor);
    ui->graphicsView->setFocus();
}

void MainWindow::on_actionLayer_zValue_Lock_triggered(bool checked)
{
    LayerZLock = checked;
}

void MainWindow::on_checkBoxBackgRepeat_toggled(bool checked)
{
    QString background = ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toString();
    m_mainScene->setBackground(background,checked);
}
