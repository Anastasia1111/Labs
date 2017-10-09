#ifndef SECONDPAGE_H
#define SECONDPAGE_H

#include <QLabel>
#include <QComboBox>
#include <QWizardPage>
#include <QVBoxLayout>
#include "spisok.h"

class SecondPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit SecondPage(QWidget *parent = 0);
protected:
    int nextId() const;
    void initializePage();
private:
    QLabel *lbl;
    QComboBox *cmb;
};

#endif // SECONDPAGE_H
