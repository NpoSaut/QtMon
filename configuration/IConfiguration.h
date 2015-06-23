#ifndef ICONFIGURATION_H
#define ICONFIGURATION_H

class IConfiguration
{
public:
    virtual bool isBreakAssistRequired() const = 0; // Напоминание о необходимости поднять ручник после остановки
};

#endif // ICONFIGURATION_H
