#ifndef SYSKEYSENDER_H
#define SYSKEYSENDER_H

#include <QObject>
#include <QMap>

#include "qtCanLib/ICan.h"
#include "interaction/keyboard.h"
#include "qtBlokLib/parsers/sys_key.h"

class SysKeySender : public QObject
{
    Q_OBJECT
public:
    explicit SysKeySender(Interaction::Keyboard *keyboard, ICan *can, QObject *parent = 0);

private slots:
    void keyDown (Interaction::Keyboard::Key key);
    void keyUp (Interaction::Keyboard::Key key);

private:
    ICan *can;
    QMap<Interaction::Keyboard::Key, SysKey::Key> map;
};

#endif // SYSKEYSENDER_H
