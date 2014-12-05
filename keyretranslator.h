#ifndef KEYRETRANSLATOR_H
#define KEYRETRANSLATOR_H

#include <QObject>

#include "qtCanLib/can.h"
#include "qtBlokLib/parsers/console_key.h"
#include "qtBlokLib/parsers/sys_key.h"

class KeyRetranslator : public QObject
{
    Q_OBJECT
public:
    explicit KeyRetranslator(Can *can, QObject *parent = 0);

public slots:
    void catchKeyPress (ConsoleKey::ConsKey key);
    void catchKeyReleased (ConsoleKey::ConsKey key);

protected:
    Can *can;

    SysKey::Key convert (ConsoleKey::ConsKey key);
};

#endif // KEYRETRANSLATOR_H
