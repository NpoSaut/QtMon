#include "stateserializer.h"

void StateSerializer::DeserializeFrom(ViewModels::SystemStateViewModel *model, QTextStream *stream)
{
    QString line = stream->readLine();
    Deserialize(model, line);
}

void StateSerializer::Deserialize(ViewModels::SystemStateViewModel *model, const QString stateLine)
{
    QStringList parameters = stateLine.split(_separator);
    // load parameters start : SystemStateViewModel
    model->setSpeed(parameters[0].toDouble());
    model->setSpeedIsValid(parameters[1].toInt());
    model->setIsInMotion(parameters[2].toInt());
    model->setSpeedRestriction(parameters[3].toInt());
    model->setTargetSpeed(parameters[4].toInt());
    model->setAcceleration(parameters[5].toDouble());
    model->setDesignSpeed(parameters[6].toInt());
    model->setPressureTC(parameters[7]);
    model->setPressureTM(parameters[8]);
    model->setPressureUR(parameters[9]);
    model->setBreakingFactor(parameters[10].toFloat());
    model->setLongitude(parameters[11].toDouble());
    model->setLatitude(parameters[12].toDouble());
    model->setGpsValid(parameters[13].toInt());
    model->setSystemWarningLevel(parameters[14].toInt());
    model->setFullSetWarningLevel(parameters[15].toInt());
    model->setIsPressureOk(parameters[16].toInt());
    model->setIsEpvReady(parameters[17].toInt());
    model->setIsEpvReleased(parameters[18].toInt());
    model->setModulesActivityString(parameters[19]);
    model->setSautIsOutNotifier(parameters[20].toInt());
    model->setIsTractionShutdown(parameters[21].toInt());
    model->setIsSlipping(parameters[22].toInt());
    model->setMilage(parameters[23].toInt());
    model->setAlsnFreqTarget(parameters[24].toInt());
    model->setAlsnFreqFact(parameters[25].toInt());
    model->setAutolockTypeTarget(parameters[26].toInt());
    model->setAutolockTypeFact(parameters[27].toInt());
    model->setTime(parameters[28]);
    model->setDate(parameters[29]);
    model->setIsRegistrationTapeActive(parameters[30].toInt());
    model->setDriveModeTarget(parameters[31].toInt());
    model->setDriveModeFact(parameters[32].toInt());
    model->setIronWheels(parameters[33].toInt());
    model->setIsVigilanceRequired(parameters[34].toInt());
    model->setIsTractionOn(parameters[35].toInt());
    model->setDirection(parameters[36].toInt());
    model->setOrdinate(parameters[37].toInt());
    model->setNextStatinName(parameters[38]);
    model->setNextTargetKind(parameters[39].toInt());
    model->setNextTargetName(parameters[40]);
    model->setNextTargetDistance(parameters[41].toInt());
    model->setSautTargetDistance(parameters[42].toInt());
    model->setNotificationText(parameters[43]);
    model->setTrackNumber(parameters[44].toInt());
    model->setMachinistNumber(parameters[45].toInt());
    model->setTrainNumber(parameters[46].toInt());
    model->setWagonCount(parameters[47].toInt());
    model->setAxlesCount(parameters[48].toInt());
    model->setTrainMass(parameters[49].toInt());
    model->setManualOrdinateEnable(parameters[50].toInt());
    model->setManualOrdinate(parameters[51].toInt());
    model->setManualOrdinateIncreaseDirection(parameters[52].toInt());
    model->setAutolockSpeed(parameters[53].toInt());
    model->setTsvcIsOnline(parameters[54].toInt());
    model->setTsvcIsMachinistCheerful(parameters[55].toInt());
    model->setTsvcIsVigilanceRequired(parameters[56].toInt());
    model->setTsvcIsPreAlarmActive(parameters[57].toInt());
    // load parameters end : SystemStateViewModel
}

void StateSerializer::SerializeTo(const ViewModels::SystemStateViewModel *model, QTextStream *stream)
{
    *stream << Serialize(model);
}

const QString StateSerializer::Serialize(const ViewModels::SystemStateViewModel *model)
{
    QStringList parameters;
    // save parameters start : SystemStateViewModel
    parameters.append(QString::number(model->getSpeed()));
    parameters.append(QString::number(model->getSpeedIsValid()));
    parameters.append(QString::number(model->getIsInMotion()));
    parameters.append(QString::number(model->getSpeedRestriction()));
    parameters.append(QString::number(model->getTargetSpeed()));
    parameters.append(QString::number(model->getAcceleration()));
    parameters.append(QString::number(model->getDesignSpeed()));
    parameters.append(model->getPressureTC());
    parameters.append(model->getPressureTM());
    parameters.append(model->getPressureUR());
    parameters.append(QString::number(model->getBreakingFactor()));
    parameters.append(QString::number(model->getLongitude()));
    parameters.append(QString::number(model->getLatitude()));
    parameters.append(QString::number(model->getGpsValid()));
    parameters.append(QString::number(model->getSystemWarningLevel()));
    parameters.append(QString::number(model->getFullSetWarningLevel()));
    parameters.append(QString::number(model->getIsPressureOk()));
    parameters.append(QString::number(model->getIsEpvReady()));
    parameters.append(QString::number(model->getIsEpvReleased()));
    parameters.append(model->getModulesActivityString());
    parameters.append(QString::number(model->getSautIsOutNotifier()));
    parameters.append(QString::number(model->getIsTractionShutdown()));
    parameters.append(QString::number(model->getIsSlipping()));
    parameters.append(QString::number(model->getMilage()));
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
    // save parameters end : SystemStateViewModel
    return parameters.join(_separator) + "\r\n";
}
