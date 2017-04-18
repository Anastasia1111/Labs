#ifndef ADDREC_H
#define ADDREC_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddRec;
}

class AddRec : public QDialog
{
    Q_OBJECT

public:
    explicit AddRec(QString &name2,
                    QString &name3,
                    QString &name4,
                    QString &name5,
                    QSqlQueryModel* mod,
                    QWidget *parent = 0);
    ~AddRec();
    QString data();

private:
    Ui::AddRec *ui;
    QSqlQueryModel* lmod;
    QString fifthColumn;
};

#endif // ADDREC_H