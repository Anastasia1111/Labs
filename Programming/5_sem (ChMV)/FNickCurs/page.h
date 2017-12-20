#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include <QTime>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QSqlQuery>
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

private:
    Ui::Page *ui;

    bool editMode;
    bool inConstruction;

    int bougette;
    int id;

    QSqlRecord record;
};

#endif // PAGE_H
