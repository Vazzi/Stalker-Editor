#include "menu.h"
#include "ui_menu.h"
#include "mainwindow.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    //set clear form without frame and buttons
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
    //continue button
    this->close();
}

void Menu::on_pushButtonQuit_clicked()
{
    //exit button
    exit(0);
}

void Menu::on_pushButtonNew_clicked()
{
    //new button
    //clear form
    this->close();
}
