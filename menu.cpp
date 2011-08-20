#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::Popup);

    connect(ui->pushButtonNew,SIGNAL(clicked()),parent,SLOT(clearForm()));
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
    exit(0);
}

void Menu::on_pushButtonNew_clicked()
{
    this->close();
}
