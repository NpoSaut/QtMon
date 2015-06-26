#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

#include <QObject>

class IConfiguration : public QObject
{
    Q_OBJECT
public:
    explicit IConfiguration (QObject *parent = 0);

public slots:
    virtual void update () = 0; // Обновляет значение свойств и вызывает испускание всех сигналов

signals:
    void breakAssistRequiredChanged (bool); // Напоминание о необходимости поднять ручник после остановки
};

#endif // ICONFIGURATION_H

