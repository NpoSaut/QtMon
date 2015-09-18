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
    model->setSpeedRestriction(parameters[2].toInt());
    model->setTargetSpeed(parameters[3].toInt());
    model->setAcceleration(parameters[4].toDouble());
    model->setDesignSpeed(parameters[5].toInt());
    model->setPressureTC(parameters[6]);
    model->setPressureTM(parameters[7]);
    model->setPressureUR(parameters[8]);
    model->setBreakingFactor(parameters[9].toFloat());
    model->setLongitude(parameters[10].toDouble());
    model->setLatitude(parameters[11].toDouble());
    model->setGpsValid(parameters[12].toInt());
    model->setSystemWarningLevel(parameters[13].toInt());
    model->setFullSetWarningLevel(parameters[14].toInt());
    model->setIsPressureOk(parameters[15].toInt());
    model->setIsEpvReady(parameters[16].toInt());
    model->setIsEpvReleased(parameters[17].toInt());
    model->setModulesActivityString(parameters[18]);
    model->setSautIsOutNotifier(parameters[19].toInt());
    model->setMilage(parameters[20].toInt());
    model->setAlsnFreqTarget(parameters[21].toInt());
    model->setAlsnFreqFact(parameters[22].toInt());
    model->setAutolockTypeTarget(parameters[23].toInt());
    model->setAutolockTypeFact(parameters[24].toInt());
    model->setTime(parameters[25]);
    model->setDate(parameters[26]);
    model->setIsRegistrationTapeActive(parameters[27].toInt());
    model->setDriveModeTarget(parameters[28].toInt());
    model->setDriveModeFact(parameters[29].toInt());
    model->setIronWheels(parameters[30].toInt());
    model->setIsVigilanceRequired(parameters[31].toInt());
    model->setIsTractionOn(parameters[32].toInt());
    model->setDirection(parameters[33].toInt());
    model->setOrdinate(parameters[34].toInt());
    model->setNextStatinName(parameters[35]);
    model->setNextTargetKind(parameters[36].toInt());
    model->setNextTargetName(parameters[37]);
    model->setNextTargetDistance(parameters[38].toInt());
    model->setSautTargetDistance(parameters[39].toInt());
    model->setNotificationText(parameters[40]);
    model->setTrackNumber(parameters[41].toInt());
    model->setMachinistNumber(parameters[42].toInt());
    model->setTrainNumber(parameters[43].toInt());
    model->setWagonCount(parameters[44].toInt());
    model->setAxlesCount(parameters[45].toInt());
    model->setTrainMass(parameters[46].toInt());
    model->setManualOrdinateEnable(parameters[47].toInt());
    model->setManualOrdinate(parameters[48].toInt());
    model->setManualOrdinateIncreaseDirection(parameters[49].toInt());
    model->setAutolockSpeed(parameters[50].toInt());
    model->setTsvcIsOnline(parameters[51].toInt());
    model->setTsvcIsMachinistCheerful(parameters[52].toInt());
    model->setTsvcIsVigilanceRequired(parameters[53].toInt());
    model->setTsvcIsPreAlarmActive(parameters[54].toInt());
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
