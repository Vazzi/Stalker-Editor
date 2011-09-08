#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewmap.h"
#include "dialoginfoset.h"



DialogNewMap *newMap;
DialogInfoSet *setInfoMap;
QString fileSavePath;
int itemsCount, bgCount;





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    newMap = new DialogNewMap(this);
    setInfoMap = new DialogInfoSet(this);



    start();

    connect(newMap,SIGNAL(newAccepted(int,QString,QString)),this,SLOT(clearForm(int,QString,QString)));
    connect(setInfoMap, SIGNAL(newAccepted(QString,QString)), this,SLOT(setMapInfo(QString,QString)));
}


MainWindow::~MainWindow()
{
    delete m_item;
    delete m_secondScene;
    delete m_mainScene;
    delete newMap;
    delete setInfoMap;
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




void MainWindow::on_actionNew_triggered(){
    //warn if user hasnt saved changed map
    if(!m_mainScene->isChanged()){
        if(QMessageBox::question(this,"New Map", "Map is not saved! Do you really want to create new map? ", QMessageBox::Yes, QMessageBox::No)
                ==QMessageBox::Yes){
            newMap->show();
        }
    }
    else
        newMap->show();

}

void MainWindow::on_actionQuit_triggered(){
    //if user want to quit and map hasnt been saved warn
    if(!m_mainScene->isChanged()){
        if(QMessageBox::question(this,"Quit", "Map is not saved! Do you really want to quit? ", QMessageBox::Yes, QMessageBox::No)
                ==QMessageBox::Yes){
            this->close();
        }
    }
    else
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


void MainWindow::on_actionLayer_zValue_Lock_triggered(bool checked){
    //set layer and z value lock
    m_layerZLock = checked;

}

void MainWindow::on_checkBoxBackgRepeat_toggled(bool checked){
    //set bacground to repeat
    QString background = ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toString();
    m_mainScene->setBackground(background,checked);
}

void MainWindow::on_actionSave_triggered(){
    //save if map has been save or save as new map
    if(m_saved){
        if(!m_mainScene->saveMap(fileSavePath))
            QMessageBox::warning(this, "Saving Map", "Cant save file!");
        m_mainScene->setSaved(true);
    }
    else
        saveAs();
}




void MainWindow::on_actionInformation_2_triggered(){
    //show dialog to change name and info about map
    setInfoMap->setlinesText(m_mainScene->getName(), m_mainScene->getInfo());
    setInfoMap->show();
}



void MainWindow::on_actionSave_as_triggered(){
    saveAs();
}


void MainWindow::on_actionLoad_triggered(){
    //if map hasnt been saved from the last change warn user and show load dialog
    if(!m_mainScene->isChanged()){
        if(QMessageBox::question(this,"Load Map", "Map is not saved! Do you really want to load map? ", QMessageBox::Yes, QMessageBox::No)
                ==QMessageBox::Yes){
            QString path = QFileDialog::getOpenFileName(this, "Open File",0,"*.map");
            if(path!="")
                loadMap(path);
        }
    }
    else{
        QString path = QFileDialog::getOpenFileName(this, "Open File",0,"*.map");
        if(path!="")
            loadMap(path);
    }
}



void MainWindow::on_actionAbout_triggered(){

    //show about dialog
    QString text;
    text =  "Map editor for Stalker arkade game. <br><br> Developer: Jakub Vlasak (Vazzi)<br> Helper:";
    text += " Lukas Pohlreich (Polarkac) <br> Graphic: Michal Sova (TheDram)";
    QMessageBox::information(this,"About program", text);


}


void MainWindow::on_actionImport_Item_triggered(){
    if(m_saved){
        QString path = QFileDialog::getOpenFileName(this, "Open File",0,"*.png");
        if(path!="")
            importImage(path,item);
     }
    else
        QMessageBox::information(this,"Import", "You must save map first!");
}


void MainWindow::on_actionImport_Background_triggered(){
    if(m_saved){
        QString path = QFileDialog::getOpenFileName(this, "Open File",0,"*.png");
        if(path!="")
            importImage(path,background);
     }
    else
        QMessageBox::information(this,"Import", "You must save map first!");

}

//---------------------------PRIVATE FUNCTIONS----------------------------

void MainWindow::start(){
    m_layerZLock = false;
    m_saved = false;

    //set up m_mainScene
    m_mainScene = new MyScene(10, ":/images/none", 1000);
    ui->graphicsView->setScene(m_mainScene);
    ui->graphicsView->setSceneRect(0,0,1000,600);
    m_mainScene->setInfo("Delault", "");


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
    itemsCount = 7;
    ui->comboBox->addItem("**None**",":/images/none");
    ui->comboBox->addItem("**Eraser**",":/images/rubber");
    ui->comboBox->addItem("Chest",":/images/chest");
    ui->comboBox->addItem("Dirt",":/images/dirt");
    ui->comboBox->addItem("Stone",":/images/stone");
    ui->comboBox->addItem("Wood",":/images/wood");
    ui->comboBox->addItem("Online",":/images/online");

    //set up combobox with backgrounds
    bgCount = 2;
    ui->comboBox_2->addItem("background1",":/images/background");
    ui->comboBox_2->addItem("online",":/images/online");

    //set up combobox with layres
    ui->comboBoxLayer->addItem("all *");
    for(int i = 1; i < 11; i++)
        ui->comboBoxLayer->addItem(QString::number(i) + ". layer");


    m_mainScene->setSaved(true);
}


void MainWindow::saveAs(){
    //show dialog to save map as
    QString path = QFileDialog::getSaveFileName(this, "Save File",0, "*.map");
    if(path!="")
        saveMap(path);
}

void MainWindow::importImage(QString path ,importType whatImporting){
    //import image

    //find if directory with images exist
    QDir folder;
    QString folderPath = fileSavePath;
    folderPath.remove(".map",Qt::CaseSensitive);
    folderPath.append("_images");
    //if directory doesnt exist make a directory
    folder.mkdir(folderPath);
    folder.cd(folderPath);

    //copy image to folder
    QString imagePath = path;
    QFile image;
    QString newImagePath = folder.path() + "/" + imagePath.split("/").last();
    image.copy(imagePath, newImagePath);

    QString imageName = imagePath.split("/").last();

    imageName.remove(".png",Qt::CaseSensitive);
    //what user what to import
    if(whatImporting == background){
        ui->comboBox_2->addItem(imageName, newImagePath);
    }
    else if(whatImporting == item){
        ui->comboBox->addItem(imageName, newImagePath);

    }


}

void MainWindow::loadMap(QString path){
    //load map
    //first load map and if its not ok show messagebox
    if(m_mainScene->loadMap(path)){
        //save path
        fileSavePath = path;
        m_saved = true;
        //set width, background picture path and if background repeats
        int width = m_mainScene->getSceneWidth();
        QString bgPathTemp = m_mainScene->getBgPath();
        bool bgRepeatTemp = m_mainScene->getBgRepeat();

        //set some objects
        ui->graphicsView->setSceneRect(0,0,width,600);
        ui->horizontalSlider->setMaximum(width - 400);
        ui->graphicsView->update();
        ui->actionShow_Grid->setChecked(true);
        ui->actionShow_Background->setChecked(true);
        ui->horizontalSlider->setValue(0);
        //select the background in combobox witch is in current map
        for(int i = 0 ; i < ui->comboBox_2->count();i++){
            if(ui->comboBox_2->itemData(i).toString() == bgPathTemp){
                ui->comboBox_2->setCurrentIndex(i);
                break;
            }
        }
        //set background repeat checkbox (depends on loaded map)
        ui->checkBoxBackgRepeat->setChecked(bgRepeatTemp);
        //set again background in scene because the scene has been changed when it changed combobox
            //and repeat checkbox
        m_mainScene->setBgIndividualy(bgPathTemp, bgRepeatTemp);
        //set saved true because of loaded map
        m_mainScene->setSaved(true);
    }
    else
        QMessageBox::warning(this, "Loading Map", "Cant load file!");

}

void MainWindow::saveMap(QString path){
    //saved map path to fileSavePath
    fileSavePath = path;

    if(fileSavePath.contains(".map",Qt::CaseSensitive)==false)
        fileSavePath.append(".map");

    //if map doesnt save properly messageBox else set save values to true
    if(!m_mainScene->saveMap(fileSavePath))
        QMessageBox::warning(this, "Saving Map", "Cant save file!");
    else{
        m_mainScene->setSaved(true);
        m_saved = true;
    }

}

//---------------------------SLOTS----------------------------

void MainWindow::clearForm(int width,QString mapName,QString info){

    //slot witch clears the scene
    m_mainScene->clearlyNewScene(width,mapName,info);
    //set objects to default values
    ui->graphicsView->setSceneRect(0,0,width,600);
    ui->horizontalSlider->setMaximum(width - 400);
    ui->graphicsView->update();
    ui->actionShow_Grid->setChecked(true);
    ui->actionShow_Background->setChecked(true);
    ui->checkBoxBackgRepeat->setChecked(false);
    ui->horizontalSlider->setValue(0);
    //remove imported items
    for(int i = itemsCount; i < ui->comboBox->count() ;i++){
        ui->comboBox->removeItem(i);
    }
    for(int i = bgCount; i < ui->comboBox_2->count();i++){
        ui->comboBox_2->removeItem(i);
    }

    //set saved
    m_mainScene->setSaved(false);
    m_saved = false;
}

void MainWindow::setMapInfo(QString mapName, QString info){
    //SLOT that set new info about map to scene
    m_mainScene->setInfo(mapName, info);
}






