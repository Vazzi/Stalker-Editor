#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
    class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButtonContinue_clicked();

    void on_pushButtonQuit_clicked();

    void on_pushButtonNew_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
