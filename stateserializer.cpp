#include "stateserializer.h"

void StateSerializer::DeserializeFrom(SystemStateViewModel *model, QTextStream *stream)
{
    QString line = stream->readLine();
    Deserialize(model, line);
}

void StateSerializer::Deserialize(SystemStateViewModel *model, const QString stateLine)
{
    QStringList parameters = stateLine.split(_separator);
    // load parameters start
    model->setSpeed(parameters[0].toDouble());
    // load parameters end
}

void StateSerializer::SerializeTo(const SystemStateViewModel *model, QTextStream *stream)
{
    *stream << Serialize(model);
}

const QString StateSerializer::Serialize(const SystemStateViewModel *model)
{
    QStringList parameters;
    // save parameters start
    parameters.append(QString::number(model->getSpeed()));
    // save parameters end
    return parameters.join(_separator) + "\n";
}
