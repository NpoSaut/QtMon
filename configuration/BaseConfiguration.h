#ifndef BASECONFIGURATION_H
#define BASECONFIGURATION_H

#include "IConfiguration.h"

// Хранит значения свойтв,
// даёт потомкам возможность их устанавливать, при этом испускает сигнал об изменении (если нужно)
class BaseConfiguration : public IConfiguration
{
    Q_OBJECT
public:
    explicit BaseConfiguration(QObject *parent = 0);

protected:
    void setBreakAssistRequired (bool v, bool forceSignal);

private:
    bool breakAssistRequired;
};

#endif // BASECONFIGURATION_H
