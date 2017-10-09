#include "firstpage.h"

FirstPage::FirstPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle("Шаг 1");
    setSubTitle("Выберите тип анкеты");
    QVBoxLayout *bit = new QVBoxLayout;
    bit->addWidget(lbl = new QLabel("========================="));
    bit->addWidget(rbt1 = new QRadioButton("Анкета абитуриента"));
    bit->addWidget(rbt2 = new QRadioButton("Анкета для поступления на работу"));
    bit->addWidget(lbl_err = new QLabel(""));
    lbl->setStyleSheet("color:blue; font-size: 14px");
    lbl_err->setStyleSheet("color:red; font-size: 12px");
    bit->addWidget(lbl_err);
    bit->addStretch(1);
    setLayout(bit);
    registerField("rbt_1", rbt1);
    registerField("rbt_2", rbt2);
}

int FirstPage::nextId() const
{
    if(rbt1->isChecked())
    {
        return SECOND_PAGE;
    }
    if(rbt2->isChecked())
    {
        return TWO_PAGE;
    }
}

bool FirstPage :: validatePage()
{
    bool ok = false;
    ok = ((rbt1->isChecked())||(rbt2->isChecked()));
    lbl_err->setText(ok ? "" : "Вы не выбрали тип анкеты");
    return ok;
}

