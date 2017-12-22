#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QTime>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(bool editMode, int bougette, QSqlRecord record, QWidget *parent = 0);

    ~Page();

public slots:
    void setUsedBougette(int value);

signals:
    void nameChanged(QString);

    void bougetteChanged();

private slots:
    void on_navigationButton_clicked();

    void on_bougetteSpinBox_valueChanged(int arg1);

    void on_photoButton_clicked();

    void setPhoto(const QString &value);

    void updateRecord(QString value, QString field);

    void on_nameEdit_textChanged(const QString &arg1);

    void on_descriptionEdit_textChanged();

    void on_timeEdit_timeChanged(const QTime &time);

    void on_itemAddButton_clicked();

    void on_itemRemoveButton_clicked();

    void on_peopleAddButton_clicked();

    void on_peopleRemoveButton_clicked();

    void on_orgAddButton_clicked();

    void on_orgRemoveButton_clicked();

private:
    Ui::Page *ui;

    bool editMode;
    bool inConstruction;

    int bougette;
    int id;

    QSqlRecord record;

    QSqlQueryModel *itemMod;
    QSqlQueryModel *peopleMod;
    QSqlQueryModel *orgMod;
};

#endif // PAGE_H
