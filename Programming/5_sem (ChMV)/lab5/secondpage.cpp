#include "secondpage.h"

SecondPage::SecondPage(QWidget *parent) : QWizardPage(parent)
{
    setTitle("Шаг 2");
//    setSubTitle("Выберите файл шаблона из списка");
//    setCommitPage(true);
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(lbl = new QLabel);
    vbl->addWidget(cmb = new QComboBox);
    cmb->addItem("Выберите файл шаблона из списка");
    cmb->addItem("МИЭТ");
    cmb->addItem("Гусевский ПолиТех");
    setLayout(vbl);
    registerField("combo", cmb);
}

void SecondPage::initializePage()
{
    if(field("rbt_1")== 1)
        lbl->setText(trUtf8("Вы выбрали тип анкеты 1"));
}

int SecondPage::nextId() const
{
    return FINAL_PAGE;
}

