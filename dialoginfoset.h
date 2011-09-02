#ifndef DIALOGINFOSET_H
#define DIALOGINFOSET_H

#include <QDialog>

namespace Ui {
    class DialogInfoSet;
}

class DialogInfoSet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfoSet(QWidget *parent = 0);
    ~DialogInfoSet();

     void setlinesText(QString Name, QString Info);

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();



private:
    Ui::DialogInfoSet *ui;

signals:
    void newAccepted(QString,QString);
};

#endif // DIALOGINFOSET_H
