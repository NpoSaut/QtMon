#include <QApplication>
#include "qmlapplicationviewer.h"
#include "systemstateviewmodel.h"
#include "qtconcurrentrun.h"
#include <QTextStream>
#include <QTextCodec>

#include "masqarade.h"
#ifdef WIN32
    HANDLE winConsoleandler;
#endif

#ifdef WITH_CAN
#include "iodrv/iodrv.h"
#endif

#include "iodrv/can.h"

#include <iostream>

SystemStateViewModel *systemState ;

#ifdef WITH_CAN
iodrv* iodriver;
SpeedAgregator* speedAgregator;
rmp_key_handler* rmp_key_hdlr;
#endif

void getParamsFromConsole ()
{
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
        else if (cmd.at(0) == "wt")
        {
            systemState->setWarningText( cmd.at(1) );
            out << "Now Warning Text is: " << systemState->getWarningText() << endl;
        }
        else if (cmd.at(0) == "it")
        {
            systemState->setInfoText( cmd.at(1) );
            out << "Now Info Text is: " << systemState->getInfoText() << endl;
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
            out << "wt {text} Текст предупреждения" << endl;
            out << "it {text} Текст совета" << endl;
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

#ifdef WITH_CAN
    //QtConcurrent::run(getParamsFromCan);
    //Здесь подключаюсь я.
    iodriver = new iodrv(systemState);
    speedAgregator = new SpeedAgregator();

    // Создание и подключение «обработчиков»
    // -> Отбработчик нажатия РМП <-
    rmp_key_hdlr = new rmp_key_handler();

    // Передача сообщения в новый CAN-класс
    QObject::connect (iodriver, SIGNAL(signal_new_message(const can_frame*)), &canDev, SLOT(receiveFromIoDrv(const can_frame*)));
    QObject::connect (&canDev, SIGNAL(transmitToIoDrv(const can_frame*)), iodriver, SLOT(slot_send_message(const can_frame*)));

    QObject::connect(systemState, SIGNAL(ChangeDrivemodeButtonPressed()), rmp_key_hdlr, SLOT(rmp_key_pressed()));
    QObject::connect(iodriver, SIGNAL(signal_ssps_mode(int)), rmp_key_hdlr, SLOT(ssps_mode_received(int)));
    QObject::connect(iodriver, SIGNAL(signal_driving_mode(int)), rmp_key_hdlr, SLOT(driving_mode_received(int)));

    QObject::connect(rmp_key_hdlr, SIGNAL(target_driving_mode_changed(int)), systemState, SLOT(setDriveModeTarget(int)));
    QObject::connect(rmp_key_hdlr, SIGNAL(actual_driving_mode_changed(int)), systemState, SLOT(setDriveModeFact(int)));
    QObject::connect(rmp_key_hdlr, SIGNAL(rmp_key_pressed_send()), iodriver, SLOT(slot_rmp_key_down()));
    // <- Отбработчик нажатия РМП ->

    // Переносить ли эти события из iodrv в обработчики
    QObject::connect(iodriver, SIGNAL(signal_iron_wheels(bool)), systemState, SLOT(setIronWheels(bool)));

    // Для отладки
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeedFromEarth(double)));
    QObject::connect(iodriver, SIGNAL(signal_speed_sky(double)), systemState, SLOT(setSpeedFromSky(double)));

    //Скорость и ограничения
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), speedAgregator, SLOT(getSpeedFromEarth(double)));
    QObject::connect(iodriver, SIGNAL(signal_speed_sky(double)), speedAgregator, SLOT(getSpeedFromSky(double)));
    QObject::connect(iodriver, SIGNAL(signal_is_on_road(bool)), speedAgregator, SLOT(getIsOnRoad(bool)));
    QObject::connect(speedAgregator, SIGNAL(speedChanged(double)), systemState, SLOT(setSpeed(double)));
    QObject::connect(speedAgregator, SIGNAL(speedIsValidChanged(bool)), systemState, SLOT(setSpeedIsValid(bool)));
    QObject::connect(iodriver, SIGNAL(signal_speed_limit(int)), systemState, SLOT(setSpeedRestriction(int)));
    QObject::connect(iodriver, SIGNAL(signal_target_speed(int)), systemState, SLOT(setTargetSpeed(int)));
    QObject::connect(iodriver, SIGNAL(signal_acceleration(double)), systemState, SLOT(setAcceleration(double)));
    //Состояние системы
    QObject::connect(iodriver, SIGNAL(signal_epv_key(bool)), systemState, SLOT(setIsEpvReady(bool)));
    QObject::connect(iodriver, SIGNAL(signal_epv_released(bool)), systemState, SLOT(setIsEpvReleased(bool)));
    //Одометр
    QObject::connect(iodriver, SIGNAL(signal_passed_distance(int)), systemState, SLOT(setMilage(int)));
    //Светофоры
    QObject::connect(iodriver, SIGNAL(signal_trafficlight_light(int)), systemState, SLOT(setLight(int)));
    QObject::connect(iodriver, SIGNAL(signal_trafficlight_freq(int)), systemState, SLOT(setAlsnFreqFact(int)));

    QObject::connect(iodriver, SIGNAL(signal_vigilance(bool)), systemState, SLOT(setIsVigilanceRequired(bool)));
    QObject::connect(iodriver, SIGNAL(signal_movement_direction(int)), systemState, SLOT(setDirection(int)));
    QObject::connect(iodriver, SIGNAL(signal_reg_tape_avl(bool)), systemState, SLOT(setIsRegistrationTapeActive(bool)));

    QObject::connect(iodriver, SIGNAL(signal_autolock_type(int)), systemState, SLOT(setAutolockTypeFact(int)));
    QObject::connect(systemState, SIGNAL(AutolockTypeTargetChanged()), iodriver, SLOT(slot_autolock_type_target_changed()));

    QObject::connect(iodriver, SIGNAL(signal_pressure_tc(QString)), systemState, SLOT(setPressureTC(QString)));
    QObject::connect(iodriver, SIGNAL(signal_pressure_tm(QString)), systemState, SLOT(setPressureTM(QString)));

    QObject::connect(iodriver, SIGNAL(signal_lat(double)), systemState, SLOT(setLatitude(double)));
    QObject::connect(iodriver, SIGNAL(signal_lon(double)), systemState, SLOT(setLongitude(double)));
    QObject::connect(iodriver, SIGNAL(signal_time(QString)), systemState, SLOT(setTime(QString)));
    QObject::connect(iodriver, SIGNAL(signal_date(QString)), systemState, SLOT(setDate(QString)));

    QObject::connect(iodriver, SIGNAL(signal_traction(bool)), systemState, SLOT(setIsTractionOn(bool)));

    QObject::connect(systemState, SIGNAL(DisableRedButtonPressed()), iodriver, SLOT(slot_vk_key_down()));
    QObject::connect(systemState, SIGNAL(DisableRedButtonReleased()), iodriver, SLOT(slot_vk_key_up()));

    iodriver->start(argv[1], argv[2], (QString(argv[3]).toInt() == 0) ? gps_data_source_gps : gps_data_source_can);

#else
    QtConcurrent::run(getParamsFromConsole);
#endif

    return app->exec();
}
