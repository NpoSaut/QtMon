#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <QObject>
#include <QString>

namespace Commands {

class TextManager : public QObject
{
    Q_OBJECT
public:
    explicit TextManager(QObject *parent = 0);

signals:
//    void valueChanged (int value);
    void outputStringChanged ();
    void submitted (int value);

public slots:
    void clear ();

    void numericKeyPressed (int digit);
    void backscapeKeyPressed ();
    void enterKeyPressed ();

public:
    void setOutputFormat (QString s); // %1 заменится на value
    QString getOuputString () const;

    void setValue (int v);
    int getValue () const;

private:
    int value;
    QString outputFormat;
};

}

#endif // TEXTMANAGER_H
