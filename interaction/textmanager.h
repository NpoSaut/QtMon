#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QObject>
#include <QString>

#include "keyboard.h"

namespace Interaction {

class TextManager : public QObject
{
    Q_OBJECT
public:
    explicit TextManager(Keyboard *keyboard, QObject *parent = 0);

signals:
//    void valueChanged (int value);
    void outputStringChanged ();
    void submitted (int value);

public slots:
    void clear ();

public:
    void init (QString format); // %1 заменится на value
    void init (QString format, int initialValue); // %1 заменится на value
    QString getOuputString () const;

    void setValue (int v);
    int getValue () const;

private slots:
    void numericKeyPressed (int digit);
    void backscapeKeyPressed ();
    void enterKeyPressed ();

private:
    int value;
    QString outputFormat;
};

}

#endif // TEXTMANAGER_H
