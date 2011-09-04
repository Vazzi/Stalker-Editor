#include "dialoginfoset.h"
#include "ui_dialoginfoset.h"

DialogInfoSet::DialogInfoSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfoSet)
{
    ui->setupUi(this);
}

DialogInfoSet::~DialogInfoSet()
{
    delete ui;
}



void DialogInfoSet::on_pushButtonOK_clicked()
{
    //save informations
    QString name = ui->lineEdit->text().trimmed();
    QString information = ui->plainTextEdit->toPlainText().trimmed();

    //if name is empty or has a ";" in cant accept dialog
    if(name!= "" && !name.contains(";", Qt::CaseSensitive)){
        if(!information.contains(";", Qt::CaseSensitive)){
            emit newAccepted(name,information);
            this->close();
        }
        else
           ui->plainTextEdit->setFocus();
    }
    else{
        ui->lineEdit->setFocus();
    }

}

void DialogInfoSet::on_pushButtonCancel_clicked()
{
    //cancel button
     this->close();
}

void DialogInfoSet::setlinesText(QString Name, QString Info){
    //set text before user edit
    ui->lineEdit->setText(Name);
    ui->plainTextEdit->setPlainText(Info);
}
