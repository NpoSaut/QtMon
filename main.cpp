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
#include "qtBlokLib/parser.h"
#include "qtBlokLib/elmapforwardtarget.h"
#include "qtBlokLib/iodrv.h"
#include "qtBlokLib/cookies.h"
#ifdef LIB_SOCKET_CAN
#include "qtCanLib/socketcan.h"
#endif
#include "qtCanLib/dummycan.h"


#include "notificator.h"
#include "displaystatesender.h"
#include "keyretranslator.h"
#include "drivemodehandler.h"
#include "pressureselector.h"
#include "trafficlightadaptor.h"
#include "gpio/gpioproducer.h"
#include "ledtrafficlight.h"
#include "ledvigilance.h"
#include "alsnfreqhandler.h"
#include "autolockhandler.h"
#include "records/stateplayer.h"
#include "records/staterecorder.h"

#include "textmanagerviewmodel.h"
#include "interaction/keyboards/cankeyboard.h"
#include "interaction/keyboards/qmlkeyboard.h"
#include "interaction/keyboards/compositekeyboard.h"
#include "interaction/storymanager.h"
#include "interaction/textmanager.h"
#include "interaction/commandmanager.h"
#include "interaction/commands/configurecommand.h"
#include "interaction/commands/modulesactivitycommand.h"
#include "interaction/keyboardmanager.h"

SystemStateViewModel *systemState ;
TextManagerViewModel *textManagerViewModel;
Interaction::Keyboards::QmlKeyboard *qmlKeyboard;
Levithan* levithan;
Notificator* notificator;
DisplayStateSander* displayStateSander;
KeyRetranslator *keyRetranslator;

iodrv* iodriver;
DrivemodeHandler *drivemodeHandler;
PressureSelector *pressureSelector;
TrafficlightAdaptor *trafficlightAdaptor;
GpioProducer *gpioProducer;
LedTrafficlight *ledTrafficlight;
LedVigilance *ledVigilance;
AlsnFreqHandler *alsnFreqHandler;
AutolockHandler *autolockHandler;

Can *can;
Parser *blokMessages;
Cookies *cookies;
ElmapForwardTarget *elmapForwardTarget;

Interaction::Keyboard *keyboard;
Interaction::StoryManager *storyManager;
Interaction::TextManager *textManager;
Interaction::CommandManager *commandManager;
Interaction::KeyboardManager *keyboardManager;

// PASSIVE MODE FLAG
bool passiveMode = false;

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
            systemState->setLight( Trafficlight(cmd.at(1).toInt()) );
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
        else if (cmd.at(0) == "vig")
        {
            systemState->setIsVigilanceRequired( cmd.at(1) == "1" );
            out << "Now Vigilance is Required" << endl;
        }
        // ТСКБМ: на связи
        else if (cmd.at(0) == "tso")
        {
            systemState->setTsvcIsOnline( cmd.at(1) == "1" );
            out << "Now TSVC online is: " << systemState->getTsvcIsOnline() << endl;
        }
        // ТСКБМ: Машинист Бодр
        else if (cmd.at(0) == "tsc")
        {
            systemState->setTsvcIsMachinistCheerful( cmd.at(1) == "1" );
            out << "Now is Machinist Cheerful is: " << systemState->getTsvcIsMachinistCheerful() << endl;
        }
        // ТСКБМ: на связи
        else if (cmd.at(0) == "tsv")
        {
            systemState->setTsvcIsVigilanceRequired( cmd.at(1) == "1" );
            out << "Now TSVC Vigilance Required is: " << systemState->getTsvcIsVigilanceRequired() << endl;
        }
        // ТСКБМ: на связи
        else if (cmd.at(0) == "tsa")
        {
            systemState->setTsvcIsPreAlarmActive( cmd.at(1) == "1" );
            out << "Now TSVC Pre-Alarm is: " << systemState->getTsvcIsPreAlarmActive() << endl;
        }
        // Фактическая частота АЛСН
        else if (cmd.at(0) == "f")
        {
            systemState->setAlsnFreqFact( cmd.at(1).toInt() );
            out << "Now ALSN Freq Fact is: " << systemState->getAlsnFreqFact() << endl;
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
            out << "tso {1/0} ТСКБМ: Связь с ТСКБМ" << endl;
            out << "tsc {1/0} ТСКБМ: Машинист бодр" << endl;
            out << "tsv {1/0} ТСКБМ: Требуется подтверждение бодрости" << endl;
            out << "tsa {1/0} ТСКБМ: Предварительная сигнализация" << endl;
            out << "f {25/50/75} Фактическая частота АЛСН" << endl;
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
    qmlRegisterType<TextManagerViewModel>("views", 1, 0, "TextManagerViewModel");
    qmlRegisterType<Interaction::Keyboards::QmlKeyboard>("views", 1, 0, "QmlKeyboard");

    QmlApplicationViewer viewer;

    QFont sansFont("URW Gothic L");
//    sansFont.setStyleStrategy(QFont::NoAntialias);
    app->setFont(sansFont);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QtMon/main.qml"));
#ifdef ON_DEVICE
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif

    QObject *object = viewer.rootObject();
    systemState = object->findChild<SystemStateViewModel*>("stateView");
    textManagerViewModel = object->findChild<TextManagerViewModel*>("textManager");
    qmlKeyboard = object->findChild<Interaction::Keyboards::QmlKeyboard*>("keyboardProxy");

    levithan = new Levithan(systemState);

    // Кассета
    if ( app->arguments().contains(QString("--play")) )
    {
        can = new DummyCan();

        StatePlayer *player = new StatePlayer("states.txt", systemState);
        player->start();
    }
    else
    {
#ifdef LIB_SOCKET_CAN
        can = new SocketCan();
#else
        can = new DummyCan();
#endif
        if (passiveMode)
            can = new CanSilent (can);

        if ( app->arguments().contains(QString("--record")) )
        {
            StateRecorder *recorder = new StateRecorder("states.txt", systemState);
            recorder->start();
        }
    }

    blokMessages = new Parser(can);
    iodriver = new iodrv(can);
    cookies = new Cookies(can);
    elmapForwardTarget = new ElmapForwardTarget(can);
    notificator = new Notificator(blokMessages);
    displayStateSander = new DisplayStateSander(blokMessages, can);
    keyRetranslator = new KeyRetranslator(can);
    gpioProducer =
#ifdef Q_OS_LINUX
        new GpioProducer (GpioProducer::LINUX);
#endif
#ifdef Q_OS_WIN
        new GpioProducer (GpioProducer::DUMMY);
#endif


    // Создание и подключение «обработчиков»
    // -> Отбработчик нажатия РМП <-
    drivemodeHandler = new DrivemodePassHandler(blokMessages);
    QObject::connect(systemState, SIGNAL(ChangeDrivemodeButtonPressed()), drivemodeHandler, SLOT(drivemodeChangeButtonPressed()));
    QObject::connect(drivemodeHandler, SIGNAL(targetDrivemodeChanged(int)), systemState, SLOT(setDriveModeTarget(int)));
    QObject::connect(drivemodeHandler, SIGNAL(actualDrivemodeChanged(int)), systemState, SLOT(setDriveModeFact(int)));

    // Ретрансляция кнопок
    keyRetranslator->connect(&blokMessages->consoleKey1, SIGNAL(keyPressed(ConsoleKey::ConsKey)), SLOT(catchKeyPress(ConsoleKey::ConsKey)));
    keyRetranslator->connect(&blokMessages->consoleKey1, SIGNAL(keyReleased(ConsoleKey::ConsKey)), SLOT(catchKeyReleased(ConsoleKey::ConsKey)));

    // Переносить ли эти события из iodrv в обработчики
    QObject::connect(&blokMessages->vdsState, SIGNAL(ironWheelsChagned(bool)), systemState, SLOT(setIronWheels(bool)));

    // Для отладки
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeedFromEarth(double)));
    QObject::connect(iodriver, SIGNAL(signal_speed_sky(double)), systemState, SLOT(setSpeedFromSky(double)));

    //Скорость и ограничения
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeed(double)));
//    QObject::connect(iodriver, SIGNAL(signal_is_on_rails(bool)), systemState, SLOT(setSpeedIsValid(bool))); // HACK для трактора
    systemState->setSpeedIsValid (true);
    QObject::connect(iodriver, SIGNAL(signal_speed_limit(int)), systemState, SLOT(setSpeedRestriction(int)));
    QObject::connect(iodriver, SIGNAL(signal_target_speed(int)), systemState, SLOT(setTargetSpeed(int)));
    QObject::connect(iodriver, SIGNAL(signal_acceleration(double)), systemState, SLOT(setAcceleration(double)));
    //Состояние системы
    QObject::connect(&blokMessages->mcoState, SIGNAL(epvReadyChanged(bool)), systemState, SLOT(setIsEpvReady(bool)));
    QObject::connect(&blokMessages->mcoState, SIGNAL(epvReleasedChanged(bool)), systemState, SLOT(setIsEpvReleased(bool)));
    QObject::connect (iodriver, SIGNAL(signal_modules_activity(QString)), systemState, SLOT(setModulesActivityString(QString)));

    // Уведомления
    QObject::connect (notificator, SIGNAL(notificationTextChanged(QString)), systemState, SLOT(setNotificationText(QString)));

    //Одометр
    QObject::connect(iodriver, SIGNAL(signal_passed_distance(int)), systemState, SLOT(setMilage(int)));

    //Светофоры:
    // огонь
    trafficlightAdaptor = new TrafficLightOnOffAdaptor();
    QObject::connect (&blokMessages->mcoState, SIGNAL(epvReadyChanged(bool)), (TrafficLightOnOffAdaptor*)trafficlightAdaptor, SLOT(setOnState(bool)));
    QObject::connect (&blokMessages->mcoState, SIGNAL(trafficlightChanged(Trafficlight)), trafficlightAdaptor, SLOT(proccessNewTrafficlight(Trafficlight)));
    QObject::connect(trafficlightAdaptor, SIGNAL(trafficlightCodeChanged(int)), systemState, SLOT(setLight(int)));
    ledTrafficlight = new LedTrafficlight (gpioProducer);
    QObject::connect(trafficlightAdaptor, SIGNAL(trafficlightChanged(int)), ledTrafficlight, SLOT(lightTrafficlight(int)));
    QObject::connect(trafficlightAdaptor, SIGNAL(trafficlightUpStateChanged(bool)), ledTrafficlight, SLOT(setLightUp(bool)));
    // частота
    alsnFreqHandler = new AlsnFreqPassHandler (blokMessages);
    QObject::connect(alsnFreqHandler, SIGNAL(actualAlsnFreqChanged(int)), systemState, SLOT(setAlsnFreqFact(int)));
    QObject::connect (alsnFreqHandler, SIGNAL(targetAlsnFreqChanged(int)), systemState, SLOT(setAlsnFreqTarget(int)));
    QObject::connect(systemState, SIGNAL(AlsnFreqTargetChanged(int)), alsnFreqHandler, SLOT(proccessNewTargetAlsnFreq(int)));

    // бдительность
    QObject::connect(iodriver, SIGNAL(signal_vigilance(bool)), systemState, SLOT(setIsVigilanceRequired(bool)));
    ledVigilance = new LedVigilance (gpioProducer);
    QObject::connect(systemState, SIGNAL(IsVigilanceRequiredChanged(bool)), ledVigilance, SLOT(doBlinking(bool)));

    QObject::connect(iodriver, SIGNAL(signal_movement_direction(int)), systemState, SLOT(setDirection(int)));
    QObject::connect(iodriver, SIGNAL(signal_reg_tape_avl(bool)), systemState, SLOT(setIsRegistrationTapeActive(bool)));

    // Автоблокировка АБ
    autolockHandler = new AutolockHandler (can, blokMessages);
    QObject::connect(autolockHandler, SIGNAL(actualAutolockModeChanged(int)), systemState, SLOT(setAutolockTypeFact(int)));
    QObject::connect (autolockHandler, SIGNAL(targetAutlockModeChanged(int)), systemState, SLOT(setAutolockTypeTarget(int)));
    QObject::connect(systemState, SIGNAL(AutolockTypeTargetChanged(int)), autolockHandler, SLOT(setTargetMode(int)));
    QObject::connect (systemState, SIGNAL(AutolockSpeedChanged(int)), autolockHandler, SLOT(setWhiteSpeed(int)));

    // Давление
    pressureSelector = new PressureSelector (PressureSelector::MPA, false, blokMessages);
    QObject::connect (pressureSelector, SIGNAL(tcPressureChagned(QString)), systemState, SLOT(setPressureTC(QString)));
    QObject::connect (pressureSelector, SIGNAL(tmPressureChanged(QString)), systemState, SLOT(setPressureTM(QString)));
    QObject::connect (pressureSelector, SIGNAL(urPressureChanged(QString)), systemState, SLOT(setPressureUR(QString)));

    // GPS
    QObject::connect(&blokMessages->mmAltLong, SIGNAL(latitudeChanged(double)), systemState, SLOT(setLatitude(double)));
    QObject::connect(&blokMessages->mmAltLong, SIGNAL(longitudeChanged(double)), systemState, SLOT(setLongitude(double)));
    QObject::connect(&blokMessages->mmAltLong, SIGNAL(validChanged(bool)), systemState, SLOT(setGpsValid(bool)));
    QObject::connect(iodriver, SIGNAL(signal_time(QString)), systemState, SLOT(setTime(QString)));
    QObject::connect(iodriver, SIGNAL(signal_date(QString)), systemState, SLOT(setDate(QString)));

    QObject::connect(&blokMessages->mcoState, SIGNAL(tractionChanged(bool)), systemState, SLOT(setIsTractionOn(bool)));

    QObject::connect(systemState, SIGNAL(DisableRedButtonPressed()), iodriver, SLOT(slot_vk_key_down()));
    QObject::connect(systemState, SIGNAL(DisableRedButtonReleased()), iodriver, SLOT(slot_vk_key_up()));

    // Ввод параметров
    QObject::connect (systemState, SIGNAL(TrackNumberChanged(int)), &cookies->trackNumberInMph, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(TrackNumberChanged(int)), &cookies->trackNumbetNotSaved, SLOT(setVaule(int)));
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

    // Ручной ввод начальной координаты
    QObject::connect (systemState, SIGNAL(ManualOrdinateChanged(int)), &cookies->startOrdinate, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(ManualOrdinateIncreaseDirectionChanged(int)), &cookies->ordinateIncreaseDirection, SLOT(setVaule(int)));
//    QObject::connect (&cookies->startOrdinate, SIGNAL(onChange(int)), systemState, SLOT(setManualOrdinate(int)));
    QObject::connect (&cookies->ordinateIncreaseDirection, SIGNAL(onChange(int)), systemState, SLOT(setManualOrdinateIncreaseDirection(int)));

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
    cookies->startOrdinate.requestValue ();
    cookies->ordinateIncreaseDirection.requestValue ();
    // Для регистрации
    cookies->speedLimitGreen.requestValue ();
    cookies->speedLimitRedYellow.requestValue ();
    cookies->speedLimitWhite.requestValue ();

    // Электронная карта
    QObject::connect (elmapForwardTarget, SIGNAL(nameChanged(QString)), systemState, SLOT(setNextTargetName(QString)));
    QObject::connect (elmapForwardTarget, SIGNAL(distanceChanged(int)), systemState, SLOT(setNextTargetDistance(int)));
    QObject::connect (elmapForwardTarget, SIGNAL(kindChanged(int)), systemState, SLOT(setNextTargetKind(int)));
    QObject::connect (&blokMessages->mmCoord, SIGNAL(railWayCoordinateChanged(int)), systemState, SLOT(setOrdinate(int)));
    QObject::connect (&blokMessages->mmStation, SIGNAL(stationNameChanged(QString)), systemState, SLOT(setNextStatinName(QString)));

    // САУТ
    QObject::connect (&blokMessages->sautState, SIGNAL(distanceToTargetChanged(int)), systemState, SLOT(setSautTargetDistance(int)));
    QObject::connect (&blokMessages->sautState, SIGNAL(brakeFactorChanged(float)), systemState, SLOT(setBreakingFactor(float)));

    // Звуки
    QObject::connect (systemState, SIGNAL(LightChanged(int)), levithan, SLOT(sayLightIndex(int)));
    QObject::connect (systemState, SIGNAL(SpeedWarningFlash()), levithan, SLOT(beepHigh()));
    QObject::connect (systemState, SIGNAL(ButtonPressed()), levithan, SLOT(beepHigh()));
    QObject::connect (systemState, SIGNAL(ConfirmButtonPressed()), levithan, SLOT(beep()));
    QObject::connect (systemState, SIGNAL(TsvcIsVigilanceRequiredChanged(bool)), levithan, SLOT(proccessNewVigilanceRequired(bool)));
    QObject::connect (systemState, SIGNAL(TsvcIsPreAlarmActiveChanged(bool)), levithan, SLOT(proccessNewPreAlarmActive(bool)));
    QObject::connect (systemState, SIGNAL(IsEpvReadyChanged(bool)), levithan, SLOT(proccessNewEpvReady(bool)));
    QObject::connect (systemState, SIGNAL(WarningLedFlash()), levithan, SLOT(beepVigilance()));

    // Взаимодествие с пользователем через команды
    keyboard = new Interaction::Keyboards::CompositeKeyboard ({qmlKeyboard, new Interaction::Keyboards::CanKeyboard (&blokMessages->consoleKey1)});
    storyManager = new Interaction::StoryManager ();
    textManager = new Interaction::TextManager (keyboard);
    textManagerViewModel->assign(textManager);
    commandManager = new Interaction::CommandManager (storyManager, {
                                                          new Interaction::Commands::ConfigureCommand (textManager),
                                                          new Interaction::Commands::ModulesActivityCommand (&blokMessages->mcoState, textManager),
                                                      });
    keyboardManager = new Interaction::KeyboardManager (keyboard, storyManager, commandManager, textManager );

    QtConcurrent::run(getParamsFromConsole);

    return app->exec();
}
