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
    cmb->addItem("anketa2.txt");
    cmb->addItem("anketa3.txt");
    setLayout(vbl);
    registerField("combo1", cmb);
}

void SecondPage::initializePage()
{
    if(field("rbt_1")== 1)
        lbl->setText(trUtf8("Вы выбрали тип анлеты 1"));
}

int SecondPage::nextId() const
{
    return FINAL_PAGE;
}

