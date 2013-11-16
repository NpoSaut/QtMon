#ifndef DISPLAYSTATE_H
#define DISPLAYSTATE_H

#include <QObject>

#include "qtCanLib/can.h"
#include "qtBlokLib/parser.h"

// Отправляет периодические сообщения с состоянием монитора
//  - отслеживает нажатие кнопок и дублирует их в своём периодическом сообщении
class DisplayStateSander : public QObject
{
    Q_OBJECT
public:
    explicit DisplayStateSander(Parser *parser, Can *can, QObject *parent = 0);
    
signals:
    
public slots:

protected:
    void timerEvent(QTimerEvent *event);

private:
    Can *can;
    Parser *parser;
};

#endif // DISPLAYSTATE_H
