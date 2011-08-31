#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewmap.h"


DialogNewMap *newMap;
QFileDialog *saveDialog;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    m_layerZLock = false;

    //set up m_mainScene
    m_mainScene = new MyScene(10, ":/images/none", 1000);
    ui->graphicsView->setScene(m_mainScene);
    ui->graphicsView->setSceneRect(0,0,1000,600);

    //set up slider
    ui->horizontalSlider->setMinimum(400);
    ui->horizontalSlider->setMaximum(1000 - 400);


    //set up secondScene
    m_secondScene = new QGraphicsScene;
    m_item = new QGraphicsPixmapItem;
    m_item = m_secondScene->addPixmap(QString(":/images/none"));
    ui->graphicsView_2->setScene(m_secondScene);
    ui->graphicsView_2->setSceneRect(0,0,80,80);
    m_secondScene->setBackgroundBrush(Qt::lightGray);

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

    newMap = new DialogNewMap(this);
    connect(newMap,SIGNAL(newAccepted(int,QString,QString)),this,SLOT(clearForm(int,QString,QString)));


}


MainWindow::~MainWindow()
{
    delete m_item;
    delete m_secondScene;
    delete m_mainScene;
    delete saveDialog;
    delete ui;

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //set image m_mainScene to current image in comboBox
    m_mainScene->setImage(ui->comboBox->itemData(index).toString());
    m_mainScene->setItemZValue(ui->spinBox->value());
    //show image in secondScene
    m_item->setPixmap(ui->comboBox->itemData(index).toString());
    //refresh labels
    //if user select **eraser** set the specific objects
    if(ui->comboBox->itemData(index).toString()==":/images/rubber"){
        ui->labelWidth->setText("10 px");
        ui->labelHeight->setText("10 px");
    }
    else{
        ui->labelWidth->setText(QString::number(m_item->pixmap().width()) + " px");
        ui->labelHeight->setText(QString::number(m_item->pixmap().height())+ " px");
        //resize if it is necessary
        if(m_item->pixmap().width() > 78)
            m_item->setPixmap(m_item->pixmap().scaledToHeight(78,Qt::FastTransformation));
        else if(m_item->pixmap().height() > 78)
            m_item->setPixmap(m_item->pixmap().scaledToWidth(78,Qt::FastTransformation));
    }

    //set pixmap position into the midle of graphicsview
    int x,y;
    x = (ui->graphicsView_2->width()/2) - (m_item->pixmap().width()/2);
    y = (ui->graphicsView_2->height()/2) - (m_item->pixmap().height()/2);
    m_item->setPos(x,y);

    //set focus on scene
    ui->graphicsView->setFocus();
}


void MainWindow::on_pushButtonFill_clicked(){
    //fill the screen with images
    m_mainScene->fill();
    ui->graphicsView->update();
    ui->graphicsView->setFocus();
}

void MainWindow::on_pushButtonRemoveNone_clicked(){
    //remove all none images
    m_mainScene->removeNone();
    ui->graphicsView->update();
    ui->graphicsView->setFocus();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index){
    //select background
    m_mainScene->setBackground(ui->comboBox_2->itemData(index).toString(),ui->checkBoxBackgRepeat->checkState());
    ui->graphicsView->setFocus();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position){
    //move with scene in graphicsView
    ui->graphicsView->centerOn(QPoint(position,300));
    ui->graphicsView->update();
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
    if(m_layerZLock){
        if(index!=0){
            ui->spinBox->setValue(index);
        }
    }
    m_mainScene->showLayer(index);
    ui->graphicsView->setFocus();
}

void MainWindow::clearForm(int width,QString mapName,QString info){

    //slot witch clears the scene
    m_mainScene->clearlyNewScene(width,mapName,info);
    ui->graphicsView->setSceneRect(0,0,width,600);
    ui->horizontalSlider->setMaximum(width - 400);
    ui->graphicsView->update();
    ui->actionShow_Grid->setChecked(true);
    ui->actionShow_Background->setChecked(true);
    ui->checkBoxBackgRepeat->setChecked(false);
    ui->horizontalSlider->setValue(0);

}


void MainWindow::on_actionNew_triggered(){
    newMap->show();
}

void MainWindow::on_actionQuit_triggered(){
    this->close();
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
    //still doesnt work in Windows OS
    //its seems that scene is over cursor so its "invisible"
    if(checked)
        ui->graphicsView->setCursor(Qt::ArrowCursor);
    else
        ui->graphicsView->setCursor(Qt::BlankCursor);
    ui->graphicsView->setFocus();
}

void MainWindow::on_actionLayer_zValue_Lock_triggered(bool checked)
{
    m_layerZLock = checked;

}

void MainWindow::on_checkBoxBackgRepeat_toggled(bool checked)
{
    QString background = ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toString();
    m_mainScene->setBackground(background,checked);
}

void MainWindow::on_actionSave_triggered()
{
    saveDialog = new QFileDialog(this, Qt::Sheet);
    saveDialog->setFilter("Maps (*.map)");
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    connect(saveDialog,SIGNAL(accepted()),this,SLOT(saveMap()));
    saveDialog->show();
}

void MainWindow::saveMap(){
    if(!m_mainScene->saveMap(saveDialog->selectedFiles().last()))
        QMessageBox::warning(this, "Saveing Map", "Cant save file!");

}
