#ifndef FINALPAGE_H
#define FINALPAGE_H
#include <QWizardPage>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QPushButton>

class FinalPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit FinalPage(QWidget *parent = 0);
protected:
    void initializePage();
private:
    QTextEdit *txt;
    QPushButton *btn;
private slots:
    void fileSave();
};

#endif // FINALPAGE_H
