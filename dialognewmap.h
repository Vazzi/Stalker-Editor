#ifndef DIALOGNEWMAP_H
#define DIALOGNEWMAP_H

#include <QDialog>

namespace Ui {
    class DialogNewMap;
}

class DialogNewMap : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewMap(QWidget *parent = 0);
    ~DialogNewMap();


private slots:

    void on_pushButtonOk_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::DialogNewMap *ui;
    bool m_enableCancel;

signals:
    void newAccepted(int,QString,QString);
};

#endif // DIALOGNEWMAP_H
