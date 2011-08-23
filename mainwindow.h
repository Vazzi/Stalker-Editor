#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "myscene.h"


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

    void on_actionShow_Cursor_triggered(bool checked);

    void on_actionLayer_zValue_Lock_triggered(bool checked);

private:
    void clearForm();

    Ui::MainWindow *ui;
    MyScene *m_mainScene;
    QGraphicsScene *secondScene;
    QGraphicsPixmapItem *item;
    bool LayerZLock;




};

#endif // MAINWINDOW_H
