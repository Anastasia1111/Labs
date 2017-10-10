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
    bar->setMaximum(100);
    vbl->addWidget(txt);
    vbl->addWidget(btn);
    vbl->addWidget(bar);
    bar->hide();
    time->setInterval(50);

    setLayout(vbl);

    connect(btn, SIGNAL(clicked()), this, SLOT(fileSave()));
    connect(txt, SIGNAL(textChanged()), this, SLOT(setAble()));
    connect(time, SIGNAL(timeout()), this, SLOT(TimerTick()));
    lFileName = "";
}

void FinalPage::initializePage()
{
    QString str;
    if(field("combo") == 1)
        str.append("C:\\Users\\student\\Desktop\\anketa.txt");
    if(field("combo") == 2)
        str.append("C:\\Users\\student\\Desktop\\anketa1.txt");
    if(field("combo1") == 1)
        str.append("C:\\Users\\student\\Desktop\\anketa2.txt");
    if(field("combo1") == 2)
        str.append("C:\\Users\\student\\Desktop\\anketa3.txt");
    QFile file(str);
    QTextStream textStream(&file);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        txt->setText(textStream.readAll());
    file.close();
}

void FinalPage::cleanupPage()
{
    time->stop();
    txt->clear();
    bar->hide();
    bar->reset();
}

void FinalPage::fileSave()
{
    if(lFileName.isEmpty())
        lFileName = QFileDialog::getSaveFileName(0,
                                                 QObject::tr("Save File..."),
                                                 QDir::currentPath(),
                                                 QObject::tr("Text Files(*.txt);;All Files (*.*)"));
    if(!lFileName.isEmpty())
    {
        QFile file(lFileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream textStream(&file);
        textStream << txt->toPlainText();
        file.close();
        btn->setEnabled(false);
        time->stop();
        bar->reset();
    }
    bar->hide();
}

void FinalPage::TimerTick( void )
{
    if (!lFileName.isEmpty())
    {
        if( bar->value() >= bar->maximum() )
            fileSave();
        bar->setValue(bar->value()+1);
    }
}

void FinalPage::setAble()
{
    time->start();
    if(!lFileName.isEmpty())
        bar->show();
    btn->setEnabled(true);
}
