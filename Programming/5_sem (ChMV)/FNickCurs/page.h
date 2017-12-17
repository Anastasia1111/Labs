#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QTime>

namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(bool editMode, int bougette, QWidget *parent = 0);
    ~Page();

    /*QString name;
    QString descr;
    QTime time;
    int price;
    QString photo;*/

private slots:
    void on_navigationButton_clicked();

    void on_bougetteSpinBox_valueChanged(int arg1);

    void on_photoButton_clicked();

    void on_nameEdit_editingFinished();

private:
    Ui::Page *ui;
    bool editMode;
    int allBougette;
    int usedBougette;
};

#endif // PAGE_H
