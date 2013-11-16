#include <iostream>
#include <math.h>

#include <QApplication>
#include <QtConcurrentRun>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QtConcurrentRun>
#include <qmlapplicationviewer.h>

#include "systemstateviewmodel.h"
#include "levithan.h"

#include "cDoodahLib/masqarade.h"
#ifdef WIN32
    HANDLE winConsoleandler;
#endif

#include "qtCanLib/can.h"
#include "qtBlokLib/sysdiagnostics.h"
#include "qtBlokLib/parser.h"
#include "qtBlokLib/elmapforwardtarget.h"
#include "qtBlokLib/iodrv.h"
#include "qtBlokLib/cookies.h"
#ifdef WITH_CAN
#include "qtCanLib/socketcan.h"
#else
#include "qtCanLib/dummycan.h"
#endif

#include "notificator.h"


SystemStateViewModel *systemState ;
Levithan* levithan;
Notificator* notificator;

iodrv* iodriver;
rmp_key_handler* rmp_key_hdlr;

Can *can;
SysDiagnostics *monitorSysDiagnostics;
Parser *blokMessages;
Cookies *cookies;
ElmapForwardTarget *elmapForwardTarget;

void getParamsFromConsole ()
{
    qDebug() << "Starting reading console...";

    QString str;
    QTextStream in(stdin);
    QTextStream out(stdout);

    while (true)
    {
        str = in.readLine();
        QStringList cmd = str.split(" ");

        if (cmd.at(0) == "s")
        {
            systemState->setSpeed( cmd.at(1).toInt() );
            systemState->setSpeedIsValid(true);
            out << "Speed: " << systemState->getSpeed() << endl;
        }
        else if (cmd.at(0) == "r")
        {
            systemState->setSpeedRestriction( cmd.at(1).toInt() );
            out << "Speed restriction: " << systemState->getSpeedRestriction() << endl;
        }
        else if (cmd.at(0) == "g")
        {
            if (cmd.size() == 3)
            {
                systemState->setLongitude( cmd.at(1).toDouble() );
                systemState->setLatitude( cmd.at(2).toDouble() );
            }
            out << "Longitude: " << systemState->getLongitude()
                << "; Lattitude: " << systemState->getLatitude() << endl;
        }
        else if (cmd.at(0) == "gg")
        {
            if (cmd.size() == 3)
            {
                systemState->setLongitude(systemState->getLongitude() + cmd.at(1).toDouble() );
                systemState->setLatitude(systemState->getLatitude() + cmd.at(2).toDouble() );
            }
            out << "Longitude: " << systemState->getLongitude()
                << "; Lattitude: " << systemState->getLatitude() << endl;
        }
        else if (cmd.at(0) == "c")
        {
            systemState->setLight( cmd.at(1).toInt() );
            out << "Liht: " << systemState->getLight() << endl;
        }
        else if (cmd.at(0) == "a")
        {
            systemState->setAlsnFreqTarget( cmd.at(1).toInt() );
            out << "AlsnFreqTarget: " << systemState->getAlsnFreqTarget() << endl;
        }
        else if (cmd.at(0) == "epv")
        {
            systemState->setIsEpvReady( cmd.at(1) == "1" );
            out << "IsEpvReady: " << systemState->getIsEpvReady() << endl;
        }
        else if (cmd.at(0) == "b")
        {
            systemState->setIsEpvReleased( cmd.at(1) == "1" );
            out << "IsEpvReady: " << systemState->getIsEpvReleased() << endl;
        }
        else if (cmd.at(0) == "dm")
        {
            systemState->setDriveModeFact( cmd.at(1).toInt() );
            out << "DriveModeFact: " << systemState->getDriveModeFact() << endl;
        }
        else if (cmd.at(0) == "tdm")
        {
            systemState->setDriveModeTarget( cmd.at(1).toInt() );
            out << "DriveModeTarget: " << systemState->getDriveModeTarget() << endl;
        }
        else if (cmd.at(0) == "iw")
        {
            systemState->setIronWheels( cmd.at(1) == "1" );
            out << "Iron Wheels: " << systemState->getIronWheels() << endl;
        }
        // Тяга
        else if (cmd.at(0) == "tr")
        {
            systemState->setIsTractionOn( cmd.at(1) == "1" );
            out << "Traction is: " << systemState->getIsTractionOn() << endl;
        }
        // Направление движения
        else if (cmd.at(0) == "dir")
        {
            systemState->setDirection( cmd.at(1).toInt() );
            out << "Now Direction is: " << systemState->getDirection() << endl;
        }
        else if (cmd.at(0) == "nt")
        {
            systemState->setNotificationText( cmd.at(1) );
            out << "Now Notification Text is: " << systemState->getNotificationText() << endl;
        }
        else
        {
            out << "! unknown command. Try this:" << endl;
            out << "tdm {0/1/2/3/4} Целевой режим движения: П/М/Р/Д/Т" << endl;
            out << "dm {0/1/2/3/4} Фактический режим движения: П/М/Р/Д/Т" << endl;
            out << "epb {1/0} Ключ ЭПК: вкл/выкл" << endl;
            out << "b {1/0} Экстренное торможение: вкл/выкл" << endl;
            out << "iw {1/0} IronWheels" << endl;
            out << "tr {1/0} Тяга: вкл/выкл" << endl;
            out << "dir {1/-1/0} Направление движения: вперёд/назад/стоим" << endl;
            out << "nt {text} Текст извещения" << endl;
        }
    }
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
#ifdef WIN32
    // Masqarade
    winConsoleandler = GetStdHandle(STD_OUTPUT_HANDLE);
    system("chcp 65001");
#endif
    CPRINTF(CL_VIOLET_L, "ДОБРЫЙ ДЕНЬ\n");

    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);

    qmlRegisterType<SystemStateViewModel>("views", 1, 0, "SystemStateView");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QtMon/main.qml"));
#ifdef ON_DEVICE
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif

    QObject *object = viewer.rootObject();
    systemState = object->findChild<SystemStateViewModel*>("stateView");
    levithan = new Levithan();

#ifdef WITH_CAN
    can = new SocketCan();
#else
    can = new DummyCan();
#endif

    monitorSysDiagnostics = new SysDiagnostics(can);
    blokMessages = new Parser(can);
    iodriver = new iodrv(can);
    cookies = new Cookies(can);
    elmapForwardTarget = new ElmapForwardTarget(can);
    notificator = new Notificator(blokMessages);

    // Создание и подключение «обработчиков»
    // -> Отбработчик нажатия РМП <-
    rmp_key_hdlr = new rmp_key_handler();

    // Передача сообщения в новый CAN-класс


    QObject::connect(systemState, SIGNAL(ChangeDrivemodeButtonPressed()), rmp_key_hdlr, SLOT(rmp_key_pressed()));
    QObject::connect(iodriver, SIGNAL(signal_ssps_mode(int)), rmp_key_hdlr, SLOT(ssps_mode_received(int)));
    QObject::connect(iodriver, SIGNAL(signal_driving_mode(int)), rmp_key_hdlr, SLOT(driving_mode_received(int)));

    QObject::connect(rmp_key_hdlr, SIGNAL(target_driving_mode_changed(int)), systemState, SLOT(setDriveModeTarget(int)));
    QObject::connect(rmp_key_hdlr, SIGNAL(actual_driving_mode_changed(int)), systemState, SLOT(setDriveModeFact(int)));
    QObject::connect(rmp_key_hdlr, SIGNAL(rmp_key_pressed_send()), iodriver, SLOT(slot_rmp_key_down()));
//    QObject::connect(rmp_key_hdlr, SIGNAL(rmp_key_pressed_send()), iodriver, SLOT(slot_rmp_key_down()));
    // <- Отбработчик нажатия РМП ->

    // Переносить ли эти события из iodrv в обработчики
    QObject::connect(iodriver, SIGNAL(signal_iron_wheels(bool)), systemState, SLOT(setIronWheels(bool)));

    // Для отладки
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeedFromEarth(double)));
    QObject::connect(iodriver, SIGNAL(signal_speed_sky(double)), systemState, SLOT(setSpeedFromSky(double)));

    //Скорость и ограничения
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeed(double)));
    QObject::connect(iodriver, SIGNAL(signal_is_on_rails(bool)), systemState, SLOT(setSpeedIsValid(bool))); // HACK для трактора
    QObject::connect(iodriver, SIGNAL(signal_speed_limit(int)), systemState, SLOT(setSpeedRestriction(int)));
    QObject::connect(iodriver, SIGNAL(signal_target_speed(int)), systemState, SLOT(setTargetSpeed(int)));
    QObject::connect(iodriver, SIGNAL(signal_acceleration(double)), systemState, SLOT(setAcceleration(double)));
    //Состояние системы
    QObject::connect(iodriver, SIGNAL(signal_epv_key(bool)), systemState, SLOT(setIsEpvReady(bool)));
    QObject::connect(iodriver, SIGNAL(signal_epv_released(bool)), systemState, SLOT(setIsEpvReleased(bool)));
    QObject::connect (iodriver, SIGNAL(signal_modules_activity(QString)), systemState, SLOT(setModulesActivityString(QString)));

    // Уведомления
    QObject::connect (notificator, SIGNAL(notificationTextChanged(QString)), systemState, SLOT(setNotificationText(QString)));

    //Одометр
    QObject::connect(iodriver, SIGNAL(signal_passed_distance(int)), systemState, SLOT(setMilage(int)));
    //Светофоры
    QObject::connect(iodriver, SIGNAL(signal_trafficlight_light(int)), systemState, SLOT(setLight(int)));
    QObject::connect(iodriver, SIGNAL(signal_trafficlight_freq(int)), systemState, SLOT(setAlsnFreqFact(int)));
    QObject::connect(iodriver, SIGNAL(signal_trafficlight_freq_target(int)), systemState, SLOT(setAlsnFreqTarget(int)));
    QObject::connect(systemState, SIGNAL(AlsnFreqTargetChanged(int)), iodriver, SLOT(slot_trafficlight_freq_target(int)));

    QObject::connect(iodriver, SIGNAL(signal_vigilance(bool)), systemState, SLOT(setIsVigilanceRequired(bool)));
    QObject::connect(iodriver, SIGNAL(signal_movement_direction(int)), systemState, SLOT(setDirection(int)));
    QObject::connect(iodriver, SIGNAL(signal_reg_tape_avl(bool)), systemState, SLOT(setIsRegistrationTapeActive(bool)));

    QObject::connect(iodriver, SIGNAL(signal_autolock_type(int)), systemState, SLOT(setAutolockTypeFact(int)));
    QObject::connect(systemState, SIGNAL(AutolockTypeTargetChanged(int)), iodriver, SLOT(slot_autolock_type_target_changed(int)));
//    QObject::connect(systemState, SIGNAL(AutolockTypeTargetChanged()), iodriver, SLOT(slot_autolock_type_target_changed()));

    QObject::connect(iodriver, SIGNAL(signal_pressure_tc(QString)), systemState, SLOT(setPressureTC(QString)));
    QObject::connect(iodriver, SIGNAL(signal_pressure_tm(QString)), systemState, SLOT(setPressureTM(QString)));

    QObject::connect(iodriver, SIGNAL(signal_lat(double)), systemState, SLOT(setLatitude(double)));
    QObject::connect(iodriver, SIGNAL(signal_lon(double)), systemState, SLOT(setLongitude(double)));
    QObject::connect(iodriver, SIGNAL(signal_time(QString)), systemState, SLOT(setTime(QString)));
    QObject::connect(iodriver, SIGNAL(signal_date(QString)), systemState, SLOT(setDate(QString)));

    QObject::connect(iodriver, SIGNAL(signal_traction(bool)), systemState, SLOT(setIsTractionOn(bool)));

    QObject::connect(systemState, SIGNAL(DisableRedButtonPressed()), iodriver, SLOT(slot_vk_key_down()));
    QObject::connect(systemState, SIGNAL(DisableRedButtonReleased()), iodriver, SLOT(slot_vk_key_up()));

    // Автоблокировка
    QObject::connect(iodriver, SIGNAL(signal_autolock_type_target(int)), systemState, SLOT(setAutolockTypeTarget(int)));

    // Ввод параметров
    QObject::connect (systemState, SIGNAL(TrackNumberChanged(int)), &cookies->trackNumberInMph, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(MachinistNumberChanged(int)), &cookies->machinistNumber, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(TrainNumberChanged(int)), &cookies->trainNumber, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(AxlesCountChanged(int)), &cookies->lengthInWheels, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(WagonCountChanged(int)), &cookies->lengthInWagons, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(TrainMassChanged(int)), &cookies->mass, SLOT(setVaule(int)));
    // Чтение параметров
    QObject::connect (&cookies->trackNumberInMph, SIGNAL(onChange(int)), systemState, SLOT(setTrackNumber(int)));
    QObject::connect (&cookies->machinistNumber, SIGNAL(onChange(int)), systemState, SLOT(setMachinistNumber(int)));
    QObject::connect (&cookies->trainNumber, SIGNAL(onChange(int)), systemState, SLOT(setTrainNumber(int)));
    QObject::connect (&cookies->lengthInWheels, SIGNAL(onChange(int)), systemState, SLOT(setAxlesCount(int)));
    QObject::connect (&cookies->lengthInWagons, SIGNAL(onChange(int)), systemState, SLOT(setWagonCount(int)));
    QObject::connect (&cookies->mass, SIGNAL(onChange(int)), systemState, SLOT(setTrainMass(int)));

    QObject::connect (&cookies->designSpeed, SIGNAL(onChange(int)), systemState, SLOT(setDesignSpeed(int)));


//    QObject::connect(systemState, SIGNAL(DisableRedButtonPressed()), iodriver, SLOT(slot_vk_key_down()));
//    QObject::connect(systemState, SIGNAL(DisableRedButtonReleased()), iodriver, SLOT(slot_vk_key_up()));

#ifdef WITH_SERIAL
    // Если компилируем с поддержкой COM-порта, то берём GPS-данные из NMEA
    iodriver->start(gps_data_source_gps);
#else
    // Иначе, берём данные из CAN (если это вообще работает :-/ )
    iodriver->start(gps_data_source_can);
#endif

    cookies->trackNumberInMph.requestValue ();
    cookies->machinistNumber.requestValue ();
    cookies->trainNumber.requestValue ();
    cookies->lengthInWheels.requestValue ();
    cookies->lengthInWagons.requestValue ();
    cookies->mass.requestValue ();
    cookies->designSpeed.requestValue ();

    // Электронная карта
    QObject::connect (elmapForwardTarget, SIGNAL(nameChanged(QString)), systemState, SLOT(setNextTargetName(QString)));
    QObject::connect (elmapForwardTarget, SIGNAL(distanceChanged(int)), systemState, SLOT(setNextTargetDistance(int)));
    QObject::connect (elmapForwardTarget, SIGNAL(kindChanged(int)), systemState, SLOT(setNextTargetKind(int)));
    QObject::connect (&blokMessages->mmCoord, SIGNAL(railWayCoordinateChanged(int)), systemState, SLOT(setOrdinate(int)));

    QtConcurrent::run(getParamsFromConsole);

    QObject::connect (systemState, SIGNAL(LightChanged(int)), levithan, SLOT(SayLightIndex(int)));

    QObject::connect (systemState, SIGNAL(SpeedWarningFlash()), levithan, SLOT(BeepHigh()));

    QObject::connect (systemState, SIGNAL(ButtonPressed()), levithan, SLOT(BeepHigh()));
    QObject::connect (systemState, SIGNAL(ConfirmButtonPressed()), levithan, SLOT(Beep()));


    return app->exec();
}
