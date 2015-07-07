#ifndef NOTIFICATOR_H
#define NOTIFICATOR_H

// Выдаёт информационные сообщения для показа на экране машинисту в подходящий момент
// ----------------------------------------------------------------------------------

#include <QObject>
#include <QString>
#include <QTimer>

#include "qtBlokLib/parser.h"

class Notificator : public QObject
{
    Q_OBJECT
public:
    explicit Notificator(Parser *onParser, QObject *parent = 0);
    
signals:
    void notificationTextChanged (QString text);

public slots:
    void setHandbrakeHintRequired (bool v);
    
private slots:
    void getStateChangedSignal ();
    void handbrakeHintShow ();
    
private:
    Parser *parser;
    
    QTimer handbrakeHintTimeout;
    bool handbrakeHint;
    bool handbrakeHintRequired;
};

#endif // NOTIFICATOR_H
