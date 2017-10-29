#include "crypter.h"

const QString Crypter::key = QString("Wabba Labba Dabba Doo");

QString Crypter::cryptString(QString toCrypt)
{
    QString resultString = "";
    for (int i = 0; i < toCrypt.length(); ++i)
    {
        resultString.append(QString(QChar(toCrypt[i]).unicode()^QChar(key[keyIndex(i)]).unicode()));
    }
    return resultString;
}

QString Crypter::decryptString(QString toDecrypt)
{
    QString resultString = "";
    for (int i = 0; i < toDecrypt.length(); ++i)
    {
        resultString.append(QString(QChar(toDecrypt[i]).unicode()^QChar(key[keyIndex(i)]).unicode()));
    }
    return resultString;
}

Crypter::Crypter(QObject *parent) :
    QObject(parent)
{

}

int Crypter::keyIndex(int index)
{
    int len = key.length();
    int multiple = index / len;
    if (index >= len) {
        return index - (len * multiple);
    }
    return index;
}
