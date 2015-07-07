#include "systemstateviewmodel.h"

namespace ViewModels
{

SystemStateViewModel::SystemStateViewModel(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
{
    // fileds init start
    speedValue = 0;
    speedIsValidValue = false;
    speedRestrictionValue = 40;
    targetSpeedValue = 55;
    accelerationValue = 0;
    designSpeedValue = 40;
    pressureTCValue = "0.00";
    pressureTMValue = "0.00";
    pressureURValue = "0.00";
    breakingFactorValue = 0;
    longitudeValue = 60.4688;
    latitudeValue = 56.88397;
    gpsValidValue = false;
    systemWarningLevelValue = 0;
    fullSetWarningLevelValue = 0;
    isPressureOkValue = true;
    isEpvReadyValue = true;
    isEpvReleasedValue = false;
    modulesActivityStringValue = "------------";
    milageValue = 0;
    lightValue = -2;
    alsnFreqTargetValue = -1;
    alsnFreqFactValue = -1;
    autolockTypeTargetValue = -1;
    autolockTypeFactValue = -1;
    timeValue = "-:-";
    dateValue = "- / - / -";
    isRegistrationTapeActiveValue = false;
    driveModeTargetValue = -1;
    driveModeFactValue = -1;
    ironWheelsValue = true;
    isVigilanceRequiredValue = true;
    isTractionOnValue = false;
    directionValue = 0;
    ordinateValue = 0;
    nextStatinNameValue = "---";
    nextTargetKindValue = -1;
    nextTargetNameValue = "";
    nextTargetDistanceValue = 0;
    sautTargetDistanceValue = 0;
    notificationTextValue = "";
    trackNumberValue = 0;
    machinistNumberValue = 0;
    trainNumberValue = 0;
    wagonCountValue = 1;
    axlesCountValue = 4;
    trainMassValue = 0;
    manualOrdinateEnableValue = false;
    manualOrdinateValue = 1100;
    manualOrdinateIncreaseDirectionValue = 1;
    autolockSpeedValue = 40;
    tsvcIsOnlineValue = false;
    tsvcIsMachinistCheerfulValue = false;
    tsvcIsVigilanceRequiredValue = false;
    tsvcIsPreAlarmActiveValue = false;
    // fileds init end

    QObject::connect(this, SIGNAL(ModulesActivityObjectChanged(ModulesActivity)), this, SLOT(convertModulesActivityObjectToString(ModulesActivity)));
}

void SystemStateViewModel::setDesignSpeed(int value, bool valid)
{
    setDesignSpeed(valid ? value : 150);
}

// -- start: Properties Getters and Setters --
// Текущая скорость
double SystemStateViewModel::getSpeed() const
{
    return speedValue;
}
void SystemStateViewModel::setSpeed(const double value)
{
    if (speedValue != value)
    {
        speedValue = value;
        emit SpeedChanged(value);
    }
}

// Корректность скорости
bool SystemStateViewModel::getSpeedIsValid() const
{
    return speedIsValidValue;
}
void SystemStateViewModel::setSpeedIsValid(const bool value)
{
    if (speedIsValidValue != value)
    {
        speedIsValidValue = value;
        emit SpeedIsValidChanged(value);
    }
}

// Ограничение скорости
int SystemStateViewModel::getSpeedRestriction() const
{
    return speedRestrictionValue;
}
void SystemStateViewModel::setSpeedRestriction(const int value)
{
    if (speedRestrictionValue != value)
    {
        speedRestrictionValue = value;
        emit SpeedRestrictionChanged(value);
    }
}

// Целевая скорость
int SystemStateViewModel::getTargetSpeed() const
{
    return targetSpeedValue;
}
void SystemStateViewModel::setTargetSpeed(const int value)
{
    if (targetSpeedValue != value)
    {
        targetSpeedValue = value;
        emit TargetSpeedChanged(value);
    }
}

// Ускорение
double SystemStateViewModel::getAcceleration() const
{
    return accelerationValue;
}
void SystemStateViewModel::setAcceleration(const double value)
{
    if (accelerationValue != value)
    {
        accelerationValue = value;
        emit AccelerationChanged(value);
    }
}

// Конструктивная скорость
int SystemStateViewModel::getDesignSpeed() const
{
    return designSpeedValue;
}
void SystemStateViewModel::setDesignSpeed(const int value)
{
    if (designSpeedValue != value)
    {
        designSpeedValue = value;
        emit DesignSpeedChanged(value);
    }
}

// Давление ТЦ
QString SystemStateViewModel::getPressureTC() const
{
    return pressureTCValue;
}
void SystemStateViewModel::setPressureTC(const QString value)
{
    if (pressureTCValue != value)
    {
        pressureTCValue = value;
        emit PressureTCChanged(value);
    }
}

// Давление ТМ
QString SystemStateViewModel::getPressureTM() const
{
    return pressureTMValue;
}
void SystemStateViewModel::setPressureTM(const QString value)
{
    if (pressureTMValue != value)
    {
        pressureTMValue = value;
        emit PressureTMChanged(value);
    }
}

// Давление УР
QString SystemStateViewModel::getPressureUR() const
{
    return pressureURValue;
}
void SystemStateViewModel::setPressureUR(const QString value)
{
    if (pressureURValue != value)
    {
        pressureURValue = value;
        emit PressureURChanged(value);
    }
}

// Коэффициент торможения
float SystemStateViewModel::getBreakingFactor() const
{
    return breakingFactorValue;
}
void SystemStateViewModel::setBreakingFactor(const float value)
{
    if (breakingFactorValue != value)
    {
        breakingFactorValue = value;
        emit BreakingFactorChanged(value);
    }
}

double SystemStateViewModel::getLongitude() const
{
    return longitudeValue;
}
void SystemStateViewModel::setLongitude(const double value)
{
    if (longitudeValue != value)
    {
        longitudeValue = value;
        emit LongitudeChanged(value);
    }
}

double SystemStateViewModel::getLatitude() const
{
    return latitudeValue;
}
void SystemStateViewModel::setLatitude(const double value)
{
    if (latitudeValue != value)
    {
        latitudeValue = value;
        emit LatitudeChanged(value);
    }
}

bool SystemStateViewModel::getGpsValid() const
{
    return gpsValidValue;
}
void SystemStateViewModel::setGpsValid(const bool value)
{
    if (gpsValidValue != value)
    {
        gpsValidValue = value;
        emit gpsValidChanged(value);
    }
}

// Общий уровень предупреждений
int SystemStateViewModel::getSystemWarningLevel() const
{
    return systemWarningLevelValue;
}
void SystemStateViewModel::setSystemWarningLevel(const int value)
{
    if (systemWarningLevelValue != value)
    {
        systemWarningLevelValue = value;
        emit SystemWarningLevelChanged(value);
    }
}

// Укомплектованность конфигурации
int SystemStateViewModel::getFullSetWarningLevel() const
{
    return fullSetWarningLevelValue;
}
void SystemStateViewModel::setFullSetWarningLevel(const int value)
{
    if (fullSetWarningLevelValue != value)
    {
        fullSetWarningLevelValue = value;
        emit FullSetWarningLevelChanged(value);
    }
}

// Давление в норме
bool SystemStateViewModel::getIsPressureOk() const
{
    return isPressureOkValue;
}
void SystemStateViewModel::setIsPressureOk(const bool value)
{
    if (isPressureOkValue != value)
    {
        isPressureOkValue = value;
        emit IsPressureOkChanged(value);
    }
}

// Готовность ЭПК
bool SystemStateViewModel::getIsEpvReady() const
{
    return isEpvReadyValue;
}
void SystemStateViewModel::setIsEpvReady(const bool value)
{
    if (isEpvReadyValue != value)
    {
        isEpvReadyValue = value;
        emit IsEpvReadyChanged(value);
    }
}

// Признак срыва ЭПК
bool SystemStateViewModel::getIsEpvReleased() const
{
    return isEpvReleasedValue;
}
void SystemStateViewModel::setIsEpvReleased(const bool value)
{
    if (isEpvReleasedValue != value)
    {
        isEpvReleasedValue = value;
        emit IsEpvReleasedChanged(value);
    }
}

// Строка с активностью модулей
QString SystemStateViewModel::getModulesActivityString() const
{
    return modulesActivityStringValue;
}
void SystemStateViewModel::setModulesActivityString(const QString value)
{
    if (modulesActivityStringValue != value)
    {
        modulesActivityStringValue = value;
        emit ModulesActivityStringChanged(value);
    }
}

// Проиденное расстояние
int SystemStateViewModel::getMilage() const
{
    return milageValue;
}
void SystemStateViewModel::setMilage(const int value)
{
    if (milageValue != value)
    {
        milageValue = value;
        emit MilageChanged(value);
    }
}

// Код сигнала светофора (0 - К, 1 - КЖ, ...)
int SystemStateViewModel::getLight() const
{
    return lightValue;
}
void SystemStateViewModel::setLight(const int value)
{
    if (lightValue != value)
    {
        lightValue = value;
        emit LightChanged(value);
    }
}

// Целевая Частота АЛСН
int SystemStateViewModel::getAlsnFreqTarget() const
{
    return alsnFreqTargetValue;
}
void SystemStateViewModel::setAlsnFreqTarget(const int value)
{
    if (alsnFreqTargetValue != value)
    {
        alsnFreqTargetValue = value;
        emit AlsnFreqTargetChanged(value);
    }
}

// Фактическая Частота АЛСН
int SystemStateViewModel::getAlsnFreqFact() const
{
    return alsnFreqFactValue;
}
void SystemStateViewModel::setAlsnFreqFact(const int value)
{
    if (alsnFreqFactValue != value)
    {
        alsnFreqFactValue = value;
        emit AlsnFreqFactChanged(value);
    }
}

// Целевой тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
int SystemStateViewModel::getAutolockTypeTarget() const
{
    return autolockTypeTargetValue;
}
void SystemStateViewModel::setAutolockTypeTarget(const int value)
{
    if (autolockTypeTargetValue != value)
    {
        autolockTypeTargetValue = value;
        emit AutolockTypeTargetChanged(value);
    }
}

// Фактический тип автоблокировки. 0 - АБ, 1 - ПАБ, 2 - ЗАБ.
int SystemStateViewModel::getAutolockTypeFact() const
{
    return autolockTypeFactValue;
}
void SystemStateViewModel::setAutolockTypeFact(const int value)
{
    if (autolockTypeFactValue != value)
    {
        autolockTypeFactValue = value;
        emit AutolockTypeFactChanged(value);
    }
}

// Время
QString SystemStateViewModel::getTime() const
{
    return timeValue;
}
void SystemStateViewModel::setTime(const QString value)
{
    if (timeValue != value)
    {
        timeValue = value;
        emit TimeChanged(value);
    }
}

// Дата
QString SystemStateViewModel::getDate() const
{
    return dateValue;
}
void SystemStateViewModel::setDate(const QString value)
{
    if (dateValue != value)
    {
        dateValue = value;
        emit DateChanged(value);
    }
}

// Наличие кассеты регистрации
bool SystemStateViewModel::getIsRegistrationTapeActive() const
{
    return isRegistrationTapeActiveValue;
}
void SystemStateViewModel::setIsRegistrationTapeActive(const bool value)
{
    if (isRegistrationTapeActiveValue != value)
    {
        isRegistrationTapeActiveValue = value;
        emit IsRegistrationTapeActiveChanged(value);
    }
}

// Целевой Режим движения
int SystemStateViewModel::getDriveModeTarget() const
{
    return driveModeTargetValue;
}
void SystemStateViewModel::setDriveModeTarget(const int value)
{
    if (driveModeTargetValue != value)
    {
        driveModeTargetValue = value;
        emit driveModeTargetChanged(value);
    }
}

// Фактический Режим движения (0 = П (поездной), 1 = М (маневровый), 2 = Р, 3 = Д)
int SystemStateViewModel::getDriveModeFact() const
{
    return driveModeFactValue;
}
void SystemStateViewModel::setDriveModeFact(const int value)
{
    if (driveModeFactValue != value)
    {
        driveModeFactValue = value;
        emit driveModeFactChanged(value);
    }
}

bool SystemStateViewModel::getIronWheels() const
{
    return ironWheelsValue;
}
void SystemStateViewModel::setIronWheels(const bool value)
{
    if (ironWheelsValue != value)
    {
        ironWheelsValue = value;
        emit IronWheelsChanged(value);
    }
}

// Необходимость подтверждения бдительности
bool SystemStateViewModel::getIsVigilanceRequired() const
{
    return isVigilanceRequiredValue;
}
void SystemStateViewModel::setIsVigilanceRequired(const bool value)
{
    if (isVigilanceRequiredValue != value)
    {
        isVigilanceRequiredValue = value;
        emit IsVigilanceRequiredChanged(value);
    }
}

// Тяга включена
bool SystemStateViewModel::getIsTractionOn() const
{
    return isTractionOnValue;
}
void SystemStateViewModel::setIsTractionOn(const bool value)
{
    if (isTractionOnValue != value)
    {
        isTractionOnValue = value;
        emit IsTractionOnChanged(value);
    }
}

// Режим движения (-1 = назад, 0 = стоим, +1 = вперёд)
int SystemStateViewModel::getDirection() const
{
    return directionValue;
}
void SystemStateViewModel::setDirection(const int value)
{
    if (directionValue != value)
    {
        directionValue = value;
        emit DirectionChanged(value);
    }
}

// Текущая ордината
int SystemStateViewModel::getOrdinate() const
{
    return ordinateValue;
}
void SystemStateViewModel::setOrdinate(const int value)
{
    if (ordinateValue != value)
    {
        ordinateValue = value;
        emit OrdinateChanged(value);
    }
}

// Название ближайшей станции
QString SystemStateViewModel::getNextStatinName() const
{
    return nextStatinNameValue;
}
void SystemStateViewModel::setNextStatinName(const QString value)
{
    if (nextStatinNameValue != value)
    {
        nextStatinNameValue = value;
        emit NextStatinNameChanged(value);
    }
}

// Тип ближайшей цели
int SystemStateViewModel::getNextTargetKind() const
{
    return nextTargetKindValue;
}
void SystemStateViewModel::setNextTargetKind(const int value)
{
    if (nextTargetKindValue != value)
    {
        nextTargetKindValue = value;
        emit NextTargetKindChanged(value);
    }
}

// Название ближайшей цели
QString SystemStateViewModel::getNextTargetName() const
{
    return nextTargetNameValue;
}
void SystemStateViewModel::setNextTargetName(const QString value)
{
    if (nextTargetNameValue != value)
    {
        nextTargetNameValue = value;
        emit NextTargetNameChanged(value);
    }
}

// Расстояние до ближайшей цели
int SystemStateViewModel::getNextTargetDistance() const
{
    return nextTargetDistanceValue;
}
void SystemStateViewModel::setNextTargetDistance(const int value)
{
    if (nextTargetDistanceValue != value)
    {
        nextTargetDistanceValue = value;
        emit NextTargetDistanceChanged(value);
    }
}

// Расстояние до цели САУТ
int SystemStateViewModel::getSautTargetDistance() const
{
    return sautTargetDistanceValue;
}
void SystemStateViewModel::setSautTargetDistance(const int value)
{
    if (sautTargetDistanceValue != value)
    {
        sautTargetDistanceValue = value;
        emit SautTargetDistanceChanged(value);
    }
}

// Текст высокоприоритетного сообщения
QString SystemStateViewModel::getNotificationText() const
{
    return notificationTextValue;
}
void SystemStateViewModel::setNotificationText(const QString value)
{
    if (notificationTextValue != value)
    {
        notificationTextValue = value;
        emit NotificationTextChanged(value);
    }
}

// Номер пути
int SystemStateViewModel::getTrackNumber() const
{
    return trackNumberValue;
}
void SystemStateViewModel::setTrackNumber(const int value)
{
    if (trackNumberValue != value)
    {
        trackNumberValue = value;
        emit TrackNumberChanged(value);
    }
}

// Номер машиниста
int SystemStateViewModel::getMachinistNumber() const
{
    return machinistNumberValue;
}
void SystemStateViewModel::setMachinistNumber(const int value)
{
    if (machinistNumberValue != value)
    {
        machinistNumberValue = value;
        emit MachinistNumberChanged(value);
    }
}

// Номер поезда
int SystemStateViewModel::getTrainNumber() const
{
    return trainNumberValue;
}
void SystemStateViewModel::setTrainNumber(const int value)
{
    if (trainNumberValue != value)
    {
        trainNumberValue = value;
        emit TrainNumberChanged(value);
    }
}

// Длина поезда в условных вагонах
int SystemStateViewModel::getWagonCount() const
{
    return wagonCountValue;
}
void SystemStateViewModel::setWagonCount(const int value)
{
    if (wagonCountValue != value)
    {
        wagonCountValue = value;
        emit WagonCountChanged(value);
    }
}

// Длина поезда в осях
int SystemStateViewModel::getAxlesCount() const
{
    return axlesCountValue;
}
void SystemStateViewModel::setAxlesCount(const int value)
{
    if (axlesCountValue != value)
    {
        axlesCountValue = value;
        emit AxlesCountChanged(value);
    }
}

// Масса поезда
int SystemStateViewModel::getTrainMass() const
{
    return trainMassValue;
}
void SystemStateViewModel::setTrainMass(const int value)
{
    if (trainMassValue != value)
    {
        trainMassValue = value;
        emit TrainMassChanged(value);
    }
}

// Разрешение ручного ввода начальной ординаты. К сожалению, не используется. Смотрим на номер пути.
bool SystemStateViewModel::getManualOrdinateEnable() const
{
    return manualOrdinateEnableValue;
}
void SystemStateViewModel::setManualOrdinateEnable(const bool value)
{
    if (manualOrdinateEnableValue != value)
    {
        manualOrdinateEnableValue = value;
        emit ManualOrdinateEnableChanged(value);
    }
}

// Начальная ордината в ручном режиме
int SystemStateViewModel::getManualOrdinate() const
{
    return manualOrdinateValue;
}
void SystemStateViewModel::setManualOrdinate(const int value)
{
    if (manualOrdinateValue != value)
    {
        manualOrdinateValue = value;
        emit ManualOrdinateChanged(value);
    }
}

// Увеличение ординаты в ручном режиме. 1 - вперёд, 0 - назад.
int SystemStateViewModel::getManualOrdinateIncreaseDirection() const
{
    return manualOrdinateIncreaseDirectionValue;
}
void SystemStateViewModel::setManualOrdinateIncreaseDirection(const int value)
{
    if (manualOrdinateIncreaseDirectionValue != value)
    {
        manualOrdinateIncreaseDirectionValue = value;
        emit ManualOrdinateIncreaseDirectionChanged(value);
    }
}

// Скорость на белый при ЗАБ
int SystemStateViewModel::getAutolockSpeed() const
{
    return autolockSpeedValue;
}
void SystemStateViewModel::setAutolockSpeed(const int value)
{
    if (autolockSpeedValue != value)
    {
        autolockSpeedValue = value;
        emit AutolockSpeedChanged(value);
    }
}

// ТСКБМ подключена
bool SystemStateViewModel::getTsvcIsOnline() const
{
    return tsvcIsOnlineValue;
}
void SystemStateViewModel::setTsvcIsOnline(const bool value)
{
    if (tsvcIsOnlineValue != value)
    {
        tsvcIsOnlineValue = value;
        emit TsvcIsOnlineChanged(value);
    }
}

// ТСКБМ: машинист бодр
bool SystemStateViewModel::getTsvcIsMachinistCheerful() const
{
    return tsvcIsMachinistCheerfulValue;
}
void SystemStateViewModel::setTsvcIsMachinistCheerful(const bool value)
{
    if (tsvcIsMachinistCheerfulValue != value)
    {
        tsvcIsMachinistCheerfulValue = value;
        emit TsvcIsMachinistCheerfulChanged(value);
    }
}

// ТСКБМ требует подтверждения бдительности
bool SystemStateViewModel::getTsvcIsVigilanceRequired() const
{
    return tsvcIsVigilanceRequiredValue;
}
void SystemStateViewModel::setTsvcIsVigilanceRequired(const bool value)
{
    if (tsvcIsVigilanceRequiredValue != value)
    {
        tsvcIsVigilanceRequiredValue = value;
        emit TsvcIsVigilanceRequiredChanged(value);
    }
}

// Предварительная сигнализация ТСКБМ активна
bool SystemStateViewModel::getTsvcIsPreAlarmActive() const
{
    return tsvcIsPreAlarmActiveValue;
}

void SystemStateViewModel::setTsvcIsPreAlarmActive(const bool value)
{
    if (tsvcIsPreAlarmActiveValue != value)
    {
        tsvcIsPreAlarmActiveValue = value;
        emit TsvcIsPreAlarmActiveChanged(value);
    }
}

// -- end: Properties Getters and Setters --

ModulesActivity SystemStateViewModel::getModulesActivityObject() const
{
    return modulesActivityObjectValue;
}

void SystemStateViewModel::setModulesActivityObject(const ModulesActivity ma)
{
    if (modulesActivityObjectValue != ma)
    {
        modulesActivityObjectValue = ma;
        emit ModulesActivityObjectChanged(ma);
    }
}

void SystemStateViewModel::convertModulesActivityObjectToString(ModulesActivity ma)
{
    setModulesActivityString(ma.toString());
}

}




