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
    cmb1->addItem("БизГид");
    cmb1->addItem("НоуНэйм");
    setLayout(vbl);
    registerField("combo1", cmb1);
}

void TwoPage::initializePage()
{
    if(field("rbt_2")== 1)
        lbl->setText(trUtf8("Вы выбрали тип анкеты 2"));
}

int TwoPage::nextId() const
{
    return FINAL_PAGE;
}

