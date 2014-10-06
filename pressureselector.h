#ifndef PRESSURESELECTOR_H
#define PRESSURESELECTOR_H

#include <QObject>

#include "qtBlokLib/parser.h"
#include "qtBlokLib/parsers/pressure.h"

// Выбирает какое давление показывать
// ----------------------------------
// 1. Задача:
//  Давления поступают от двух источников: МСУЛа и датчиков, подключенных напрямую к модулю ВЫВОДа
//  У обоих источников лдя каждого датчика есть признак достоверности.
//  Сами источники могут отсутствовать (нет их сообщений в CAN)
//  В интерфейс нужны три строки с давлениями.
// 2. Алгоритм:
//  Каждый датчик независим.
//  Выбирается нетухлое достоверное значение. При прочих равных берётся УКТОЛ.
//
class PressureSelector : public QObject
{
    Q_OBJECT
public:
    enum Unit
    {
        ATM = 0,
        BAR = 1,
        MPA = 2
    };
    explicit PressureSelector(Unit unit, bool showUnits, Parser *parser,  QObject *parent = 0);

    // Виберает в каких единицах выдавать давление
    void setUnit (Unit unit);
    
signals:
    void tcPressureChagned (QString p);
    void tmPressureChanged (QString p);
    void urPressureChanged (QString p);

public slots:
    // Что бы не произошло (т.е. изменилось давление УКТОЛ или давление ВЫВОДа или протухло что),
    // всегда точка входа одна. В ней анализируется всё текущее состояние и делается выбор.
    void updateTcPressure ();
    void updateTmPressure ();
    void updateUrPressure ();

protected:
    // Берёт нетухлый более достоверный. При прочих равных - a.
    const Pressure &takeOne (bool aFresh, const Pressure &a, bool bFresh, const Pressure &b);
    // Берёт более достоверный, при прочих равных - a
    const Pressure &takeOne (const Pressure &a, const Pressure &b);

    Parser *parser;
    // Указатель на одну из функций класса Pressure, возвращающих давление в виде строки в заданных единицах
    QString (Pressure::*print) (bool) const;

    bool showUnits;
};

#endif // PRESSURESELECTOR_H
