#ifndef DISPLAYSTATE_H
#define DISPLAYSTATE_H

#include <QObject>
#include <QVector>

#include "qtCanLib/ICan.h"
#include "illumination/interfaces/IAnalogDevice.h"
#include "interaction/KeyboardState.h"

// Отправляет периодические сообщения с состоянием монитора
//  - отслеживает нажатие кнопок и дублирует их в своём периодическом сообщении
class DisplayStateSender : public QObject, public IAnalogDevice
{
    Q_OBJECT
public:
    explicit DisplayStateSender(Interaction::KeyboardState *keyboardState, ICan *can, QObject *parent = 0);

    void setValue(double backlightLevel);

public slots:
    void setDriveMode (int driveMode);

private slots:
    void onKeyboardStateChange ();

private:
    CanFrame constructA ();
    CanFrame constructB ();
    void sendState (CanFrame A, CanFrame B);
    void timerEvent(QTimerEvent *event);

    Interaction::KeyboardState *keyboardState;
    ICan *can;
    CanFrame lastA, lastB;
    int backlightLevel;
    int driveMode;
};

#endif // DISPLAYSTATE_H
