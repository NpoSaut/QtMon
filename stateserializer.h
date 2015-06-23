#ifndef STATESERIALIZER_H
#define STATESERIALIZER_H

#include <QTextStream>
#include "viewmodels/systemstateviewmodel.h"

// Инструмент по сериализации состояния системы
class StateSerializer
{
    // Разделитель параметров в строке
    QString _separator;

public:
    StateSerializer() : _separator("\t") {}

    // Десериализует состояние из текстового потока
    void DeserializeFrom(ViewModels::SystemStateViewModel *model, QTextStream *stream);
    // Десериализует состояние из строки
    void Deserialize(ViewModels::SystemStateViewModel *model, const QString stateLine);

    // Сериализует состояние в текстовый поток
    void SerializeTo(const ViewModels::SystemStateViewModel *model, QTextStream *stream);
    // Сериализует состояние в строку
    const QString Serialize(const ViewModels::SystemStateViewModel *model);
};

#endif // STATESERIALIZER_H
