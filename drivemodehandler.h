#ifndef DRIVEMODEHANDLER_H
#define DRIVEMODEHANDLER_H

#include <QObject>

#include "qtCanLib/can.h"
#include "qtBlokLib/parser.h"

class DrivemodeHandler : public QObject
{
    Q_OBJECT
public:
    explicit DrivemodeHandler (QObject *parent = 0)
        : QObject (parent) { }

signals:
    // Запрос на принудительное изменение целевого режима.
    void targetDrivemodeChanged (int dm);
    // Сигнал изменения акутального режима движения ЦО
    void actualDrivemodeChanged (int dm);

public slots:
    // Нажатие на кнопку выбора режима из интерфейса
    virtual void drivemodeChangeButtonPressed () = 0;
};

// Простая передача режима в интерфейс (просто преобразователь формата)
class DrivemodePassHandler : public DrivemodeHandler
{
    Q_OBJECT
public:
    explicit DrivemodePassHandler (Parser *parser, QObject *parent = 0);

signals:
    // Запрос на принудительное изменение целевого режима.
    void targetDrivemodeChanged (int dm);
    // Сигнал изменения акутального режима движения ЦО
    void actualDrivemodeChanged (int dm);

public slots:
    // Нажатие на кнопку выбора режима из интерфейса
    void drivemodeChangeButtonPressed () { }

private slots:
    void convertEnumToInt (DriveMode dm);
};

// Переключатель режимов движения "для КХ"
//  Позволяет установить целевой режим движения путём последовательного нажатия на кнопку (натыкивания)
//  Обеспечивает применение в ЦО целевого режима движения путём перебора режимов ЦО посредством SYS_KEY
//  Изменяет список доступных режимов в зависимости от положения катков
//  При изменении положения катков автоматически осуществляет выбор целевого режима движения
// входные и выходные данные:
//  - Из интерфейса воспринимает нажатие кнопки смены режима
//    В интерфейс отадет текущий выбранный (заданный) режим и актуальный (установленный в ЦО) режим
//  - Из CAN принимет состояние катков и актуальный режим
//    В CAN выдаёт сообщение нажатие клавиши для переключения актуального режима
class DrivemodeSettingHandler : public DrivemodeHandler
{
    Q_OBJECT
public:
    // Parser для получения информации о акутальном режиме и положении катков
    // Can для оптавки команды SYS_KEY на смену режима
    explicit DrivemodeSettingHandler(Parser *parser, Can *can, QObject *parent = 0);
    
signals:
    // Принудительное изменение целевого режима. Возникает при смене пложения катков.
    void targetDrivemodeChanged (int dm);
    // Сигнал изменения акутального режима движения ЦО
    void actualDrivemodeChanged (int dm);
    
public slots:
    // Нажатие на кнопку выбора режима
    void drivemodeChangeButtonPressed ();

private slots:
    void processIronWheelsChange (bool ironWheels);
    void processActualDrivemodeChage (DriveMode dm);
    void processNewState ();

private:
    void setTarget (DriveMode tm);
    DriveMode getTarget () const;

    Parser *parser;
    Can *can;
    DriveMode target;
    quint8 convergenceCounter; // счётчик сообщений ЦО с режимом, не совпадающим с целевым
};

#endif // DRIVEMODEHANDLER_H
