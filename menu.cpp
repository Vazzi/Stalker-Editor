#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::Popup);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButtonContinue_clicked()
{
    this->close();
}

void Menu::on_pushButtonQuit_clicked()
{
    this->close();

}
