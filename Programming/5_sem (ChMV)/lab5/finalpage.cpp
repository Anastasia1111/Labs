#include "finalpage.h"

FinalPage::FinalPage(QWidget *parent):QWizardPage(parent)
{
    setTitle("Анкета");
    QVBoxLayout *vbl = new QVBoxLayout;
    txt = new QTextEdit;
    btn = new QPushButton("Сохранить как...");
    vbl->addWidget(txt);
    vbl->addWidget(btn);
    setLayout(vbl);
    connect(btn, SIGNAL(clicked()), this, SLOT(fileSave()));
}

void FinalPage::initializePage()
{
    QString str;
    if(field("combo") == 1)
        str.append("C:\\Users\\student\\Desktop\\anketa.txt");
    if(field("combo") == 2)
        str.append("C:\\Users\\student\\Desktop\\anketa2.txt");
    if(field("combo1") == 1)
        str.append("C:\\Users\\student\\Desktop\\anketa1.txt");
    if(field("combo1") == 2)
        str.append("C:\\Users\\student\\Desktop\\anketa2.txt");
    QFile file(str);
    QTextStream textStream(&file);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        txt->setText(textStream.readAll());
    file.close();
}

void FinalPage::fileSave()
{
    QString lFileName = QFileDialog::getSaveFileName(0,
                                                     QObject::tr("Save File..."),
                                                     QDir::currentPath(),
                                                     QObject::tr("Text Files(*.txt);;All Files (*.*)"));
    QFile file(lFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream textStream(&file);
    textStream << txt->toPlainText();
    file.close();
}
