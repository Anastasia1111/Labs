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
    bool isFirstSectionSelected();
    bool isSecondSectionSelected();
    QString text();

private:
    Ui::AddRec *ui;

};

#endif // ADDREC_H
