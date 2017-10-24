#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QMap<QString, QString> *map, QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_linelogin_editingFinished();

private:
    Ui::Dialog *ui;
    QMap<QString, QString>* map;
};

#endif // DIALOG_H
