#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <QTreeWidget>
#include <QDomDocument>
#include <QMessageBox>
#include <QProgressBar>
#include <QDebug>

class DomParser
{
public:
    DomParser(QIODevice *device, QTreeWidget *tree, QProgressBar *bar);

private:
    void parseEntry(const QDomElement &element, QTreeWidgetItem *parent);
    int countNodes(QDomElement root);
    int countNodes(QDomElement root, QString tag);

    QTreeWidget *treeWidget;
    QProgressBar *progress;
    int nodeCount;
};

#endif // DOMPARSER_H
