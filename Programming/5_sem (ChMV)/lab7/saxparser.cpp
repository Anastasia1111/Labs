#include "saxparser.h"

SaxParser::SaxParser(QIODevice *device, QTreeWidget* tree, QProgressBar *bar)
{
    progress = bar;
    treeWidget = tree;
    inputSource = new QXmlInputSource(device);
    currentItem = NULL;
    QXmlSimpleReader reader;

    progress->setMinimum(1);
    progress->setMaximum(100);
    progress->setValue(1);
    progress->show();
    for(int i = 2; i < 50; ++i)
        progress->setValue(i);
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    reader.parse(inputSource);
    for(int i = 50; i < 101; ++i)
        progress->setValue(i);
}

bool SaxParser::startElement(const QString &namespaceURI,
                             const QString &localName,
                             const QString &qName,
                             const QXmlAttributes &atts)
{
    if (qName == "food" || qName == "attr") {
        currentItem = new QTreeWidgetItem(currentItem ?
                                              currentItem : treeWidget->invisibleRootItem());
        currentItem->setText(0, atts.value("name"));
    } else if (qName == "value") {
        currentText.clear();
    }
    return true;
}

bool SaxParser::characters(const QString& str)
{
    currentText += str;
    return true;
}

bool SaxParser::endElement(const QString &namespaceURI,
                           const QString &localName,
                           const QString &qName)
{
    if(qName == "food" || qName == "attr") {
        currentItem = currentItem->parent();
    } else if (qName == "value") {
        if(currentItem) {
            QString allPages = currentItem->text(1);
            if(!allPages.isEmpty())
                allPages += ", ";
            allPages += currentText;
            currentItem->setText(1, allPages);
        }
    }
    return true;
}

bool SaxParser::fatalError(const QXmlParseException &exception)
{
    QMessageBox::warning(0,
                         QObject::tr("SAX Parser"),
                         QObject::tr("Parse error at line %1, column %2:\n%3")
                         .arg(exception.lineNumber())
                         .arg(exception.columnNumber())
                         .arg(qPrintable(exception.message()))
                         );
}
