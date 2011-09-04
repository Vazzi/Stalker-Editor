#include "dialognewmap.h"
#include "ui_dialognewmap.h"
#include "mainwindow.h"

DialogNewMap::DialogNewMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewMap)
{
    ui->setupUi(this);
    m_enableCancel = true;
}

DialogNewMap::~DialogNewMap()
{
    delete ui;
}





void DialogNewMap::on_pushButtonOk_clicked()
{
    int width = ui->spinBoxWidth->value();
    QString name = ui->lineEditName->text().trimmed();
    QString information = ui->plainTextEdit->toPlainText().trimmed();
    if(name!= "" && !name.contains(";", Qt::CaseSensitive)){
        if(width % 10 == 0){
            if(!information.contains(";", Qt::CaseSensitive)){
                emit newAccepted(width,name,information);
                this->close();
            }
            else
               ui->plainTextEdit->setFocus();

        }
        else{
            ui->spinBoxWidth->setFocus();
        }
    }
    else{
        ui->lineEditName->setFocus();
    }
}

void DialogNewMap::on_pushButtonCancel_clicked()
{
    this->close();
}


