#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

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

    void on_backgroundOnOff_toggled(bool checked);

    void on_GridOnOff_toggled(bool checked);

    void on_cursorOnOff_toggled(bool checked);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void labelupdate();


    void on_horizontalSlider_sliderMoved(int position);

    void on_spinBox_valueChanged(int arg1);

    void on_comboBoxLayer_currentIndexChanged(int index);

    void on_checkBoxLayerZLock_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;


};

#endif // MAINWINDOW_H
