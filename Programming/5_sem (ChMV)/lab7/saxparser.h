#ifndef SAXPARSER_H
#define SAXPARSER_H

#include <QTreeWidget>
#include <QMessageBox>
#include <QXmlSimpleReader>
#include <QProgressBar>
#include <QDebug>

class SaxParser : public QXmlDefaultHandler
{
public:
    SaxParser(QIODevice *device, QTreeWidget* tree, QProgressBar *bar);
protected:
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);
private:
    int nodeCount;
    QProgressBar *progress;
    QTreeWidget *treeWidget;
    QTreeWidgetItem *currentItem;
    QXmlInputSource *inputSource;
    QString currentText;
};

#endif // SAXPARSER_H
