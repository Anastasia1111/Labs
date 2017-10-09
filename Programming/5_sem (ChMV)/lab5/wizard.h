#ifndef WIZARD_H
#define WIZARD_H

#include <QWidget>
#include <QWizard>

namespace Ui
{class Wizard;}
class Wizard : public QWizard
{
    Q_OBJECT
public:
    explicit Wizard(QWizard *parent = 0);
    ~Wizard();
private:
    Ui::Wizard *ui;
private slots:
    void showHelp();
};

#endif // WIZARD_H
