#ifndef CRYPTER_H
#define CRYPTER_H

#include <QObject>

class Crypter : public QObject
{
    Q_OBJECT

public:

    static QString cryptString(QString toCrypt);

    static QString decryptString(QString toDecrypt);

private:
    static const QString key;

    Crypter(QObject *parent = 0);

    static int keyIndex(int index);

};

#endif // CRYPTER_H
