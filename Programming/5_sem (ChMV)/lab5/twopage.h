#ifndef TWOPAGE_H
#define TWOPAGE_H


#include "spisok.h"

#include <QLabel>
#include <QComboBox>
#include <QWizardPage>
#include <QVBoxLayout>

class TwoPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit TwoPage(QString a, QWidget *parent = 0);
protected:
    int nextId() const;
    void initializePage();
private:
    QLabel *lbl;
    QComboBox *cmb1;
};

#endif // TWOPAGE_H
