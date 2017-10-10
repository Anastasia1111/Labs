#ifndef FINALPAGE_H
#define FINALPAGE_H
#include <QWizardPage>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>

class FinalPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit FinalPage(QWidget *parent = 0);
protected:
    void initializePage();
    void cleanupPage();
private:
    QTextEdit *txt;
    QPushButton *btn;
    QProgressBar *bar;
    QTimer *time;
    QString lFileName;
private slots:
    void fileSave();
    void TimerTick( void );
    void setAble();
};

#endif // FINALPAGE_H
