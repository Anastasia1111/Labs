#include "finalpage.h"

FinalPage::FinalPage(QWidget *parent):QWizardPage(parent)
{
    setTitle("Анкета");
    QVBoxLayout *vbl = new QVBoxLayout;
    txt = new QTextEdit;
    btn = new QPushButton("Сохранить как...");
    bar = new QProgressBar(this);
    time = new QTimer(this);
    bar->setMinimum(0);
    bar->setMaximum(500);
    vbl->addWidget(txt);
    vbl->addWidget(btn);
    vbl->addWidget(bar);

    setLayout(vbl);

    connect(btn, SIGNAL(clicked()), this, SLOT(fileSave()));
    connect(txt, SIGNAL(textChanged()), this, SLOT(setAble()));
    connect(time, SIGNAL(timeout()), this, SLOT(TimerTick()));
    time->setInterval(100);
    time->start();
    lFileName = "";
}

void FinalPage::initializePage()
{
    QString str;
    if(field("combo") == 1)
        str.append("C:\\Users\\Vanya\\Desktop\\anketa.txt");
    if(field("combo") == 2)
        str.append("C:\\Users\\Vanya\\Desktop\\anketa2.txt");
    if(field("combo1") == 1)
        str.append("C:\\Users\\Vanya\\Desktop\\anketa1.txt");
    if(field("combo1") == 2)
        str.append("C:\\Users\\Vanya\\Desktop\\anketa2.txt");
    QFile file(str);
    QTextStream textStream(&file);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        txt->setText(textStream.readAll());
    file.close();
}

void FinalPage::fileSave()
{
    if(lFileName.isEmpty())
        lFileName = QFileDialog::getSaveFileName(0,
                                                 QObject::tr("Save File..."),
                                                 QDir::currentPath(),
                                                 QObject::tr("Text Files(*.txt);;All Files (*.*)"));
    QFile file(lFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream textStream(&file);
    textStream << txt->toPlainText();
    file.close();
    btn->setEnabled(false);
}

void FinalPage::TimerTick( void )
{
    if( bar->value() >= bar->maximum() ) {
        bar->reset();
        fileSave();
    }
    bar->setValue(bar->value()+1);
}

void FinalPage::setAble()
{
    btn->setEnabled(true);
}
