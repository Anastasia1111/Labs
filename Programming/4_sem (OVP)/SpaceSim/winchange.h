#ifndef WINCHANGE_H
#define WINCHANGE_H

#include <QDialog>

namespace Ui {
class WinChange;
}

class WinChange : public QDialog
{
    Q_OBJECT

public:
    explicit WinChange(QWidget *parent = 0);
    ~WinChange();
    qint32 width();
    qint32 height();

private:
    Ui::WinChange *ui;
};

#endif // WINCHANGE_H