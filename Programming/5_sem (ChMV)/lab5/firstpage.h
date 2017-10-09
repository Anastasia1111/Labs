#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QLabel>
#include <QRadioButton>
#include <QWizardPage>
#include <QVBoxLayout>
#include "spisok.h"

class FirstPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit FirstPage(QWidget *parent = 0);
protected:
    int nextId() const;
    bool validatePage();
private:
    QLabel *lbl, *lbl_err;
    QRadioButton *rbt1, *rbt2;
};

#endif // FIRSTPAGE_H
