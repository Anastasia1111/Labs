#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QMap< QPair<QString, QString>, QPair<QString, QString> > *map, QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_linelogin_editingFinished();

    void on_linequestion_editingFinished();

    void on_finish_clicked();

private:
    Ui::Dialog *ui;
    QMap< QPair<QString, QString>, QPair<QString, QString> >* map;
    QString login;
    QString password;
    QString question;
    QString answer;
};

#endif // DIALOG_H
