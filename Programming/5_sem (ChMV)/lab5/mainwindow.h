#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWizard>
#include <QWidget>
#include <QLabel>
#include "firstpage.h"
#include "secondpage.h"
#include "twopage.h"
#include "finalpage.h"
#include "spisok.h"

class MainWindow : public QWizard
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void showHelp();
};

#endif // MAINWINDOW_H
