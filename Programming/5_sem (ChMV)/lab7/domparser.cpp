#include "domparser.h"

DomParser::DomParser(QIODevice *device, QTreeWidget *tree, QProgressBar *bar) :
    treeWidget(tree),
    progress(bar)
{
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(device, true, &errorStr, &errorLine, &errorColumn)) {
        QMessageBox::warning(0,
                             QObject::tr("DOM Parser"),
                             QObject::tr("Parse error at line %1, column %2:\n%3")
                             .arg(errorLine)
                             .arg(errorColumn)
                             .arg(errorStr)
                             );
        return;
    }

    nodeCount = 1;
    nodeCount += doc.elementsByTagName("value").count();
    nodeCount += doc.elementsByTagName("attr").count();
    nodeCount += doc.elementsByTagName("food").count();
    progress->setMinimum(1);
    progress->setMaximum(nodeCount);
    progress->setValue(1);
    progress->show();

    QDomElement root = doc.documentElement();
    if (root.tagName() != "breakfast_menu")
        return;
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.toElement().tagName() == "food")
            parseEntry(node.toElement(), 0);
        node = node.nextSibling();
    }
}

void DomParser::parseEntry(const QDomElement &element, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item;
    if (parent) {
        item = new QTreeWidgetItem(parent);
    } else {
        item = new QTreeWidgetItem(treeWidget);
    }
    item->setText(0, element.attribute("name"));
    QDomNode node = element.firstChild();
    while (!node.isNull()) {
        if (node.toElement().tagName() == "food" || node.toElement().tagName() == "attr") {
            parseEntry(node.toElement(), item);
        } else if (node.toElement().tagName() == "value") {
            QDomNode childNode = node.firstChild();
            while (!childNode.isNull()) {
                if (childNode.nodeType() == QDomNode::TextNode) {
                    QString page = childNode.toText().data();
                    QString allPages = item->text(1);
                    if (!allPages.isEmpty())
                        allPages += ", ";
                    allPages += page;
                    item->setText(1, allPages);
                    break;
                }
                childNode = childNode.nextSibling();
            }
        }
        progress->setValue(progress->value() + 1);
        node = node.nextSibling();
    }
}
