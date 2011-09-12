#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "myscene.h"
enum importType{background, item};



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_comboBox_currentIndexChanged(int index);
    void on_pushButtonFill_clicked();
    void on_pushButtonRemoveNone_clicked();
    void on_comboBox_2_currentIndexChanged(int index);
    void on_horizontalSlider_sliderMoved(int position);
    void on_spinBox_valueChanged(int arg1);
    void on_comboBoxLayer_currentIndexChanged(int index);
    void on_actionNew_triggered();
    void on_actionQuit_triggered();
    void on_actionShow_Grid_triggered(bool checked);
    void on_actionShow_Background_triggered(bool checked);
    void on_actionLayer_zValue_Lock_triggered(bool checked);
    void on_checkBoxBackgRepeat_toggled(bool checked);
    void on_actionSave_triggered();
    void on_actionInformation_2_triggered();

    void on_actionSave_as_triggered();

    void on_actionLoad_triggered();

    void on_actionAbout_triggered();

    void on_actionImport_Item_triggered();

    void on_actionImport_Background_triggered();


private:

    void start();
    void saveAs();
    void importImage(QString path, importType whatImporting);
    void saveMap(QString path);
    void loadMap(QString path);
    void loadImportedItems();

    Ui::MainWindow *ui;
    MyScene *m_mainScene;
    QGraphicsScene *m_secondScene;
    QGraphicsPixmapItem *m_item;
    bool m_layerZLock, m_saved;




public slots:
    void clearForm(int width,QString mapName,QString info);
    void setMapInfo(QString mapName,QString info);


};

#endif // MAINWINDOW_H
