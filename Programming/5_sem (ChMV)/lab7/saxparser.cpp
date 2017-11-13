#include "saxparser.h"

SaxParser::SaxParser(QIODevice *device, QTreeWidget* tree)
{
    treeWidget = tree;
    inputSource = new QXmlInputSource(device);
    currentItem = NULL;
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    reader.parse(inputSource);
}

bool SaxParser::startElement(const QString &namespaceURI,
                             const QString &localName,
                             const QString &qName,
                             const QXmlAttributes &atts)
{
    if (qName == "entry") {
        currentItem = new QTreeWidgetItem(currentItem ?
                                              currentItem : treeWidget->invisibleRootItem());
        currentItem->setText(0, atts.value("term"));
    } else if (qName == "page") {
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
    if(qName == "entry") {
        currentItem = currentItem->parent();
    } else if (qName == "page") {
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
