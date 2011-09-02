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
    QString name = ui->lineEdit->text().trimmed();
    QString information = ui->plainTextEdit->toPlainText().trimmed();
    if(name!= ""){
        emit newAccepted(name,information);
        this->close();
    }
    else{
        ui->lineEdit->setFocus();
    }
}

void DialogInfoSet::on_pushButtonCancel_clicked()
{
     this->close();
}

void DialogInfoSet::setlinesText(QString Name, QString Info){
    ui->lineEdit->setText(Name);
    ui->plainTextEdit->setPlainText(Info);
}
