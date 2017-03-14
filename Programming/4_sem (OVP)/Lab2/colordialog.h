#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class ColorDialog;
}
class QGraphicsScene;

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QColor color, QWidget *parent = 0);
    ~ColorDialog();
    QColor getColor();

private:
    Ui::ColorDialog *ui;
    QColor colorResult;
    QGraphicsScene *scene;

private slots:
    void on_pushButton_clicked();

protected:
    virtual void timerEvent(QTimerEvent *e);
};

#endif // COLORDIALOG_H
