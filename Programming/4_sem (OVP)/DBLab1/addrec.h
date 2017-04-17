#ifndef ADDREC_H
#define ADDREC_H

#include <QDialog>

namespace Ui {
class AddRec;
}

class AddRec : public QDialog
{
    Q_OBJECT

public:
    explicit AddRec(QWidget *parent = 0);
    ~AddRec();
    QString data();

private:
    Ui::AddRec *ui;

};

#endif // ADDREC_H