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
    model->setSpeedIsValid(parameters[1].toInt());
    model->setSpeedFromSky(parameters[2].toDouble());
    model->setSpeedFromEarth(parameters[3].toDouble());
    model->setSpeedRestriction(parameters[4].toInt());
    model->setTargetSpeed(parameters[5].toInt());
    model->setAcceleration(parameters[6].toDouble());
    model->setDesignSpeed(parameters[7].toInt());
    model->setPressureTC(parameters[8]);
    model->setPressureTM(parameters[9]);
    model->setPressureUR(parameters[10]);
    model->setBrakingCoefficient(parameters[11].toDouble());
    model->setLongitude(parameters[12].toDouble());
    model->setLatitude(parameters[13].toDouble());
    model->setGpsValid(parameters[14].toInt());
    model->setSystemWarningLevel(parameters[15].toInt());
    model->setFullSetWarningLevel(parameters[16].toInt());
    model->setIsPressureOk(parameters[17].toInt());
    model->setIsEpvReady(parameters[18].toInt());
    model->setIsEpvReleased(parameters[19].toInt());
    model->setModulesActivityString(parameters[20]);
    model->setMilage(parameters[21].toInt());
    model->setLight(parameters[22].toInt());
    model->setAlsnFreqTarget(parameters[23].toInt());
    model->setAlsnFreqFact(parameters[24].toInt());
    model->setAutolockTypeTarget(parameters[25].toInt());
    model->setAutolockTypeFact(parameters[26].toInt());
    model->setTime(parameters[27]);
    model->setDate(parameters[28]);
    model->setIsRegistrationTapeActive(parameters[29].toInt());
    model->setDriveModeTarget(parameters[30].toInt());
    model->setDriveModeFact(parameters[31].toInt());
    model->setIronWheels(parameters[32].toInt());
    model->setIsVigilanceRequired(parameters[33].toInt());
    model->setIsTractionOn(parameters[34].toInt());
    model->setDirection(parameters[35].toInt());
    model->setOrdinate(parameters[36].toInt());
    model->setNextStatinName(parameters[37]);
    model->setNextTargetKind(parameters[38].toInt());
    model->setNextTargetName(parameters[39]);
    model->setNextTargetDistance(parameters[40].toInt());
    model->setSautTargetDistance(parameters[41].toInt());
    model->setNotificationText(parameters[42]);
    model->setTrackNumber(parameters[43].toInt());
    model->setMachinistNumber(parameters[44].toInt());
    model->setTrainNumber(parameters[45].toInt());
    model->setWagonCount(parameters[46].toInt());
    model->setAxlesCount(parameters[47].toInt());
    model->setTrainMass(parameters[48].toInt());
    model->setManualOrdinateEnable(parameters[49].toInt());
    model->setManualOrdinate(parameters[50].toInt());
    model->setManualOrdinateIncreaseDirection(parameters[51].toInt());
    model->setAutolockSpeed(parameters[52].toInt());
    model->setTsvcIsOnline(parameters[53].toInt());
    model->setTsvcIsMachinistCheerful(parameters[54].toInt());
    model->setTsvcIsVigilanceRequired(parameters[55].toInt());
    model->setTsvcIsPreAlarmActive(parameters[56].toInt());
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
    parameters.append(QString::number(model->getSpeedIsValid()));
    parameters.append(QString::number(model->getSpeedFromSky()));
    parameters.append(QString::number(model->getSpeedFromEarth()));
    parameters.append(QString::number(model->getSpeedRestriction()));
    parameters.append(QString::number(model->getTargetSpeed()));
    parameters.append(QString::number(model->getAcceleration()));
    parameters.append(QString::number(model->getDesignSpeed()));
    parameters.append(model->getPressureTC());
    parameters.append(model->getPressureTM());
    parameters.append(model->getPressureUR());
    parameters.append(QString::number(model->getBrakingCoefficient()));
    parameters.append(QString::number(model->getLongitude()));
    parameters.append(QString::number(model->getLatitude()));
    parameters.append(QString::number(model->getGpsValid()));
    parameters.append(QString::number(model->getSystemWarningLevel()));
    parameters.append(QString::number(model->getFullSetWarningLevel()));
    parameters.append(QString::number(model->getIsPressureOk()));
    parameters.append(QString::number(model->getIsEpvReady()));
    parameters.append(QString::number(model->getIsEpvReleased()));
    parameters.append(model->getModulesActivityString());
    parameters.append(QString::number(model->getMilage()));
    parameters.append(QString::number(model->getLight()));
    parameters.append(QString::number(model->getAlsnFreqTarget()));
    parameters.append(QString::number(model->getAlsnFreqFact()));
    parameters.append(QString::number(model->getAutolockTypeTarget()));
    parameters.append(QString::number(model->getAutolockTypeFact()));
    parameters.append(model->getTime());
    parameters.append(model->getDate());
    parameters.append(QString::number(model->getIsRegistrationTapeActive()));
    parameters.append(QString::number(model->getDriveModeTarget()));
    parameters.append(QString::number(model->getDriveModeFact()));
    parameters.append(QString::number(model->getIronWheels()));
    parameters.append(QString::number(model->getIsVigilanceRequired()));
    parameters.append(QString::number(model->getIsTractionOn()));
    parameters.append(QString::number(model->getDirection()));
    parameters.append(QString::number(model->getOrdinate()));
    parameters.append(model->getNextStatinName());
    parameters.append(QString::number(model->getNextTargetKind()));
    parameters.append(model->getNextTargetName());
    parameters.append(QString::number(model->getNextTargetDistance()));
    parameters.append(QString::number(model->getSautTargetDistance()));
    parameters.append(model->getNotificationText());
    parameters.append(QString::number(model->getTrackNumber()));
    parameters.append(QString::number(model->getMachinistNumber()));
    parameters.append(QString::number(model->getTrainNumber()));
    parameters.append(QString::number(model->getWagonCount()));
    parameters.append(QString::number(model->getAxlesCount()));
    parameters.append(QString::number(model->getTrainMass()));
    parameters.append(QString::number(model->getManualOrdinateEnable()));
    parameters.append(QString::number(model->getManualOrdinate()));
    parameters.append(QString::number(model->getManualOrdinateIncreaseDirection()));
    parameters.append(QString::number(model->getAutolockSpeed()));
    parameters.append(QString::number(model->getTsvcIsOnline()));
    parameters.append(QString::number(model->getTsvcIsMachinistCheerful()));
    parameters.append(QString::number(model->getTsvcIsVigilanceRequired()));
    parameters.append(QString::number(model->getTsvcIsPreAlarmActive()));
    // save parameters end
    return parameters.join(_separator) + "\n";
}
