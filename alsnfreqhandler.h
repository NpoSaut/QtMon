#ifndef ALSNFREQHANDLER_H
#define ALSNFREQHANDLER_H

#include <QObject>
#include <qtBlokLib/parser.h>

class AlsnFreqHandler : public QObject
{
    Q_OBJECT
public:
    explicit AlsnFreqHandler(QObject *parent = 0)
        : QObject (parent) { }

signals:
    // При получении новой актуальной частоты МП-АЛС
    void actualAlsnFreqChanged (int freq);
    // Задаёт при инициализации целевую, равную актуальной
    void targetAlsnFreqChanged (int freq);

public slots:
    // Принимает новую целевую частоту в качестве задания
    virtual void proccessNewTargetAlsnFreq (int freq) = 0;

protected:
    int getIntFromFreq (const AlsnFrequency& freq);
};

class AlsnFreqPassHandler : public AlsnFreqHandler
{
    Q_OBJECT
public:
    explicit AlsnFreqPassHandler(Parser *parser, QObject *parent = 0);

signals:
    // При получении новой актуальной частоты МП-АЛС
    void actualAlsnFreqChanged (int freq);
    // Задаёт при инициализации целевую, равную актуальной
    void targetAlsnFreqChanged (int freq);

public slots:
    // Принимает новую целевую частоту в качестве задания
    void proccessNewTargetAlsnFreq (int freq) { }

private slots:
    void convertEnumToInt (AlsnFrequency freq);
};

// Задатчик частоты АЛСН (наподобии задатчика РМП, хорошо бы их унаследовать от чего-то общего..)
//  Из интерфейса принимает целевую частоу
//  При инициализации устанавливает целевую частоту в интерфейсе равной фактической
//  Натыкивает кнопкой F в CAN до тех пор, пока не получит фактическую частоту, равную целевой
class AlsnFreqSettingHandler : public AlsnFreqHandler
{
    Q_OBJECT
public:
    explicit AlsnFreqSettingHandler(Can *can, Parser *parser, QObject *parent = 0);
    
signals:
    // При получении новой актуальной частоты МП-АЛС
    void actualAlsnFreqChanged (int freq);
    // Задаёт при инициализации целевую, равную актуальной
    void targetAlsnFreqChanged (int freq);
    
public slots:
    // Принимает новую целевую частоту в качестве задания
    void proccessNewTargetAlsnFreq (int freq);

protected slots:
    // Принимает новую частоту от МП-АЛС
    //  Испускает actualAlsnFreqChanged()
    //  и в первый раз устанавливает целевую через targetAlsnFreqChanged()
    void proccessNewActualAlsnFreq (AlsnFrequency freq);

    // Принимает каждое сообщение МП-АЛС (для контроля "устаканености")
    //  Если частота установилась (устаканилась) и не равна целевой,
    //  делает попытку исправить ситуацию путём эмитации нажатия на кнопку F
    void proccessNewMpMessage ();

protected:
    Can *can;
    Parser *parser;

    int target;
    quint8 convergenceCounter; // счётчик сообщений МП-АЛС с частотой, не совпадающей с целевой
    bool init;
};

#endif // ALSNFREQHANDLER_H
