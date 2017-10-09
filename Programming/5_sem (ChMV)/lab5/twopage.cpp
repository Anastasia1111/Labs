#include "twopage.h"

TwoPage::TwoPage(QString a, QWidget *parent /*= 0*/) : QWizardPage(parent)
{
    setTitle("Шаг 2");
//    setSubTitle("Выберите файл шаблона из списка");
//    setCommitPage(true);
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(lbl = new QLabel);
    vbl->addWidget(cmb1 = new QComboBox);
    cmb1->addItem("Выберите файл шаблона из списка");
    cmb1->addItem("anketa2.txt");
    cmb1->addItem("anketa3.txt");
    setLayout(vbl);
    registerField("combo1", cmb1);
}

void TwoPage::initializePage()
{
    if(field("rbt_1")== 1)
        lbl->setText(trUtf8("Вы выбрали тип анлеты 1"));
}

int TwoPage::nextId() const
{
    return FINAL_PAGE;
}

