#include <QApplication>
#include <QtConcurrentRun>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QtConcurrentRun>
#include <QFontDatabase>
#include <QDirIterator>
#include <qmlapplicationviewer.h>

#include "viewmodels/systemstateviewmodel.h"
#include "viewmodels/modulesactivityviewmodel.h"
#include "sound/Levithan.h"
#include "sound/WolfsonLevithan.h"
#include "sound/CanLevithan.h"

#include "cDoodahLib/masqarade.h"
#ifdef WIN32
    HANDLE winConsoleandler;
#endif

#include "qtCanLib/DummyCan.h"
#include "qtCanLib/AsyncCan.h"
#include "qtCanLib/drivers/DummyCan/DummyCanReceiverFactory.h"
#include "qtCanLib/drivers/DummyCan/DummyCanSenderFactory.h"
#ifdef LIB_LINUX_SOCKET_CAN_DRIVER
#include "qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanReceiverFactory.h"
#include "qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSenderFactory.h"
#endif
#ifdef LIB_APPI_CAN_DRIVER
#include "qtCanLib/drivers/AppiCan/LibusbDeviceFactory.h"
#include "qtCanLib/drivers/AppiCan/AppiCanReceiverFactory.h"
#include "qtCanLib/drivers/AppiCan/AppiCanSenderFactory.h"
#include "qtCanLib/drivers/AppiCan/AppiBlockCan1.h"
#endif
#include "qtBlokLib/parser.h"
#include "qtBlokLib/elmapforwardtarget.h"
#include "qtBlokLib/iodrv.h"
#include "qtBlokLib/cookies.h"

#include "notificator.h"
#include "displaystatesender.h"
#include "SysKeySender.h"
#include "drivemodehandler.h"
#include "pressureselector.h"
#include "ledvigilance.h"
#include "gpio/gpioproducer.h"
#include "LedTrafficlightView.h"
#include "alsnfreqhandler.h"
#include "autolockhandler.h"
#include "records/stateplayer.h"
#include "records/staterecorder.h"
#include "HardcodedVersion.h"
#include "configuration/CookieConfiguration.h"
#include "DateTimeConverter.h"

#include "viewmodels/textmanagerviewmodel.h"
#include "interaction/keyboards/cankeyboard.h"
#include "interaction/keyboards/qmlkeyboard.h"
#include "interaction/keyboards/compositekeyboard.h"
#include "interaction/KeyboardState.h"
#include "interaction/storymanager.h"
#include "interaction/textmanager.h"
#include "interaction/commandmanager.h"
#include "interaction/commands/activedpsindicationcommand.h"
#include "interaction/commands/activehalfsetidicationcommand.h"
#include "interaction/commands/configurecommand.h"
#include "interaction/commands/manualcoordinatecommand.h"
#include "interaction/commands/modulesactivitycommand.h"
#include "interaction/commands/tripconfigurationcommand.h"
#include "interaction/commands/versionrequestcommand.h"
#include "interaction/commands/versionrequestcommandfactory.h"
#include "interaction/commands/ChangeBrightnessCommand.h"
#include "interaction/commands/InputTrackNumberCommand.h"
#include "interaction/keyboardmanager.h"

#include "illumination/Edisson.h"
#include "illumination/implementations/DebugAnalogDevice.h"
#include "illumination/implementations/LinuxBacklightAnalogDeviceFactory.h"
#include "illumination/implementations/DummyIlluminationSettings.h"
#include "illumination/implementations/LinearIntensityConverter.h"
#include "illumination/implementations/ExponentialIntensityConverter.h"
#include "illumination/implementations/WeightedCompositeIlluminationDevice.h"
#include "illumination/implementations/IlluminationDevice.h"
#include "illumination/implementations/CanBilLcdIlluminationAnalogDevice.h"
#include "illumination/CanIlluminationSetter.h"
#include "viewmodels/brightnessviewmodel.h"

#include "spi/ISpiDev.h"
#ifdef LIB_LINUX_SPIDEV
#include "spi/LinuxSpiDev.h"
#endif
#include "spi/Max100500.h"
#include "Max100500TrafficlightView.h"

ViewModels::SystemStateViewModel *systemState ;
ViewModels::TextManagerViewModel *textManagerViewModel;
Interaction::Keyboards::QmlKeyboard *qmlKeyboard;
Levithan* levithan;
Notificator* notificator;
DisplayStateSender* displayStateSender;
SysKeySender *sysKeySender;

iodrv* iodriver;
DrivemodeHandler *drivemodeHandler;
PressureSelector *pressureSelector;
LedVigilance *ledVigilance;
GpioProducer *gpioProducer;
LedTrafficlightView *ledTrafficlightView;
Max100500TrafficlightView *max100500TrafficlightView;
AlsnFreqHandler *alsnFreqHandler;
AutolockHandler *autolockHandler;

ICan *can;
Parser *blokMessages;
Cookies *cookies;
ElmapForwardTarget *elmapForwardTarget;
HardcodedVersion *hardcodedVersion;
IConfiguration *configuration;

Interaction::Keyboard *keyboard;
Interaction::KeyboardState *keyboardState;
Interaction::StoryManager *storyManager;
Interaction::TextManager *textManager;
Interaction::CommandManager *commandManager;
Interaction::KeyboardManager *keyboardManager;

IIlluminationManager *illuminationManager;
ViewModels::BrightnessViewModel *brightnessViewModel;

ISpiDev *spiDev;
Max100500 *max100500;

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
            systemState->trafficLights()->setCode( Trafficlight(cmd.at(1).toInt()) );
            out << "Liht: " << systemState->trafficLights()->code() << endl;
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

    // Загребаем все шрифты из папки "шрифты"
    QDirIterator it("fonts", QStringList() << "*.ttf", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QFontDatabase::addApplicationFont(it.next());
    }

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);

    qmlRegisterType<ViewModels::SystemStateViewModel>("views", 1, 0, "SystemStateView");
    qmlRegisterType<ViewModels::TextManagerViewModel>("views", 1, 0, "TextManagerViewModel");
    qmlRegisterType<ViewModels::ModulesActivityViewModel>("views", 1, 0, "ModulesActivityViewModel");
    qmlRegisterType<ViewModels::BrightnessViewModel>("views", 1, 0, "BrightnessViewModel");
    qmlRegisterType<Interaction::Keyboards::QmlKeyboard>("views", 1, 0, "QmlKeyboard");
    qmlRegisterType<TrafficLightViewModel>("views", 1, 0, "TrafficLightViewModel");

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
    systemState = object->findChild<ViewModels::SystemStateViewModel*>("stateView");
    textManagerViewModel = object->findChild<ViewModels::TextManagerViewModel*>("textManager");
    qmlKeyboard = object->findChild<Interaction::Keyboards::QmlKeyboard*>("keyboardProxy");
    brightnessViewModel = object->findChild<ViewModels::BrightnessViewModel*>("brightnessViewModel");

    // Создание CAN
    QThread canThread;
    if ( app->arguments().contains(QString("--play")) ) // Кассета
    {
        can = new DummyCan();

        StatePlayer *player = new StatePlayer("states.txt", systemState);
        player->start();
    }
    else
    {
        IBlockedReceiverFactory *receiverFactory;
        IBlockedSenderFactory *senderFactory;
#ifdef LIB_LINUX_SOCKET_CAN_DRIVER
        receiverFactory = new LinuxSocketCanReceiverFactory ("can0");
        senderFactory   = new LinuxSocketCanSenderFactory ("can0");
#elif defined (LIB_APPI_CAN_DRIVER)
        auto *appiCan = new AppiBlockCan1 (new LibusbDeviceFactory (1));
        receiverFactory = new AppiCanReceiverFactory (appiCan);
        senderFactory = new AppiCanSenderFactory (appiCan);
#else
        receiverFactory = new DummyCanReceiverFactory ();
        senderFactory   = new DummyCanSenderFactory ();
#endif
        auto asyncCan = new AsyncCan (receiverFactory, senderFactory);
        QObject::connect(&canThread, SIGNAL(started()), asyncCan, SLOT(start()));
        can = asyncCan;

        if ( app->arguments().contains(QString("--record")) )
        {
            StateRecorder *recorder = new StateRecorder("states.txt", systemState);
            recorder->start();
        }
    }
    can->moveToThread(&canThread);
    canThread.start();

    blokMessages = new Parser(can);
    iodriver = new iodrv(can);
    cookies = new Cookies(can);

    elmapForwardTarget = new ElmapForwardTarget(can);
    notificator = new Notificator(blokMessages);

    gpioProducer =
#ifdef Q_OS_LINUX
        new GpioProducer (GpioProducer::LINUX);
#endif
#ifdef Q_OS_WIN
        new GpioProducer (GpioProducer::DUMMY);
#endif

    // Конфигурация
    configuration = new CookieConfiguration (&cookies->monitorKhConfiguration);
    QObject::connect(configuration, SIGNAL(breakAssistRequiredChanged(bool)), notificator, SLOT(setHandbrakeHintRequired(bool)));
    configuration->update();

    // Выдаёт версию по AUX_RESOURCE
    hardcodedVersion = new HardcodedVersion(3, 3, can);
    QObject::connect (&blokMessages->sysDiagnostics, SIGNAL(versionRequested(SysDiagnostics::AuxModule)), hardcodedVersion, SLOT(onVersionRequest(SysDiagnostics::AuxModule)));

    // Создание и подключение «обработчиков»
    // -> Отбработчик нажатия РМП <-
    drivemodeHandler = new DrivemodePassHandler(blokMessages);
    QObject::connect(systemState, SIGNAL(ChangeDrivemodeButtonPressed()), drivemodeHandler, SLOT(drivemodeChangeButtonPressed()));
    QObject::connect(drivemodeHandler, SIGNAL(targetDrivemodeChanged(int)), systemState, SLOT(setDriveModeTarget(int)));
    QObject::connect(drivemodeHandler, SIGNAL(actualDrivemodeChanged(int)), systemState, SLOT(setDriveModeFact(int)));

    // Переносить ли эти события из iodrv в обработчики
    QObject::connect(&blokMessages->vdsState, SIGNAL(ironWheelsChagned(bool)), systemState, SLOT(setIronWheels(bool)));

    //Скорость и ограничения
    QObject::connect(iodriver, SIGNAL(signal_speed_earth(double)), systemState, SLOT(setSpeed(double)));
//    QObject::connect(iodriver, SIGNAL(signal_is_on_rails(bool)), systemState, SLOT(setSpeedIsValid(bool))); // HACK для трактора
    systemState->setSpeedIsValid (true); // HACK для Патриота
    QObject::connect(&blokMessages->mcoState, SIGNAL(speedRestrictionChanged(int)), systemState, SLOT(setSpeedRestriction(int)));
    QObject::connect(&blokMessages->mcoState, SIGNAL(targetSpeedChanged(int)), systemState, SLOT(setTargetSpeed(int)));
    QObject::connect(iodriver, SIGNAL(signal_acceleration(double)), systemState, SLOT(setAcceleration(double)));
    //Состояние системы
    QObject::connect(&blokMessages->mcoState, SIGNAL(epvReadyChanged(bool)), systemState, SLOT(setIsEpvReady(bool)));
    QObject::connect(&blokMessages->mcoState, SIGNAL(epvReleasedChanged(bool)), systemState, SLOT(setIsEpvReleased(bool)));
    QObject::connect(&blokMessages->mcoState, SIGNAL(modulesActivityChanged(ModulesActivity)), systemState, SLOT(setModulesActivityObject(ModulesActivity)));
    QObject::connect(&blokMessages->sautState, SIGNAL(brakeFactorChanged(float)), systemState, SLOT(setBreakingFactor(float)));

    // Уведомления
    QObject::connect (notificator, SIGNAL(notificationTextChanged(QString)), systemState, SLOT(setNotificationText(QString)));

    //Одометр
    QObject::connect(iodriver, SIGNAL(signal_passed_distance(int)), systemState, SLOT(setMilage(int)));

    //Светофоры:
    // огонь
    QObject::connect (&blokMessages->mcoState, SIGNAL(trafficlightChanged(Trafficlight)), systemState->trafficLights(), SLOT(setCode(Trafficlight)));
    ledTrafficlightView = new LedTrafficlightView(systemState->trafficLights(), gpioProducer);
#ifdef LIB_LINUX_SPIDEV
    spiDev = new LinuxSpiDev ("/dev/spidev0.0", 1000000, 8);
    max100500 = new Max100500 (spiDev);
    max100500TrafficlightView = new Max100500TrafficlightView(systemState->trafficLights(), max100500);
#endif
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
    DateTimeConverter dateTimeConverter;
    QObject::connect(&blokMessages->ipdDate, SIGNAL(dateTimeChanged(QDateTime)), &dateTimeConverter, SLOT(processDateTime(QDateTime)));
    QObject::connect(&dateTimeConverter, SIGNAL(dateChanged(QString)), systemState, SLOT(setDate(QString)));
    QObject::connect(&dateTimeConverter, SIGNAL(timeChanged(QString)), systemState, SLOT(setTime(QString)));

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
    QObject::connect (&cookies->trackNumberInMph, SIGNAL(updated(int,bool)), systemState, SLOT(setTrackNumber(int)));
    QObject::connect (&cookies->machinistNumber, SIGNAL(updated(int,bool)), systemState, SLOT(setMachinistNumber(int)));
    QObject::connect (&cookies->trainNumber, SIGNAL(updated(int,bool)), systemState, SLOT(setTrainNumber(int)));
    QObject::connect (&cookies->lengthInWheels, SIGNAL(updated(int,bool)), systemState, SLOT(setAxlesCount(int)));
    QObject::connect (&cookies->lengthInWagons, SIGNAL(updated(int,bool)), systemState, SLOT(setWagonCount(int)));
    QObject::connect (&cookies->mass, SIGNAL(updated(int,bool)), systemState, SLOT(setTrainMass(int)));

    QObject::connect (&cookies->designSpeed, SIGNAL(updated(int,bool)), systemState, SLOT(setDesignSpeed(int,bool)));

    // Ручной ввод начальной координаты
    QObject::connect (systemState, SIGNAL(ManualOrdinateChanged(int)), &cookies->startOrdinate, SLOT(setVaule(int)));
    QObject::connect (systemState, SIGNAL(ManualOrdinateIncreaseDirectionChanged(int)), &cookies->ordinateIncreaseDirection, SLOT(setVaule(int)));
//    QObject::connect (&cookies->startOrdinate, SIGNAL(updated(int,bool)), systemState, SLOT(setManualOrdinate(int)));
    QObject::connect (&cookies->ordinateIncreaseDirection, SIGNAL(updated(int,bool)), systemState, SLOT(setManualOrdinateIncreaseDirection(int)));

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
    levithan = new CanLevithan(can);
    QObject::connect (systemState->trafficLights(), SIGNAL(codeChanged(Trafficlight)), levithan, SLOT(sayLightIndex(Trafficlight)));
    QObject::connect (systemState, SIGNAL(SpeedWarningFlash()), levithan, SLOT(beepHigh()));
    QObject::connect (systemState, SIGNAL(ButtonPressed()), levithan, SLOT(beepHigh()));
    QObject::connect (systemState, SIGNAL(ConfirmButtonPressed()), levithan, SLOT(beep()));
    QObject::connect (systemState, SIGNAL(TsvcIsVigilanceRequiredChanged(bool)), levithan, SLOT(proccessNewVigilanceRequired(bool)));
    QObject::connect (systemState, SIGNAL(TsvcIsPreAlarmActiveChanged(bool)), levithan, SLOT(proccessNewPreAlarmActive(bool)));
    QObject::connect (systemState, SIGNAL(IsEpvReadyChanged(bool)), levithan, SLOT(proccessNewEpvReady(bool)));
    QObject::connect (systemState, SIGNAL(WarningLedFlash()), levithan, SLOT(beepVigilance()));
    QObject::connect (systemState, SIGNAL(IsVigilanceRequiredChanged(bool)), levithan, SLOT(proccessVigilanceRequired(bool)));

    // Клавиатуры и кнопки
    keyboard = new Interaction::Keyboards::CompositeKeyboard ({qmlKeyboard, new Interaction::Keyboards::CanKeyboard (&blokMessages->consoleKey1)});
    keyboardState = new Interaction::KeyboardState (keyboard);
    displayStateSender = new DisplayStateSender(keyboardState, can);
    QObject::connect(drivemodeHandler, SIGNAL(targetDrivemodeChanged(int)), displayStateSender, SLOT(setDriveMode(int)));
    sysKeySender = new SysKeySender(keyboard, can);

    // Управление яркостью
    IIntensityConverter *intensityConverter = new ExponentialIntensityConverter(10, 0.4*255, 255);
    IIntensityConverter *to7IntensityConverter = new LinearIntensityConverter(7);
    LinuxBacklightAnalogDeviceFactory linuxBacklightFactory;
    QVector<WeightedCompositeIlluminationDevice::Leaf *> lightControllers =
    {
#ifdef ON_DEVICE
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(intensityConverter, linuxBacklightFactory.produce(0))),
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(intensityConverter, linuxBacklightFactory.produce(1))),
#else
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(intensityConverter, new DebugAnalogDevice("Display"))),
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(intensityConverter, new DebugAnalogDevice("Lights"))),
#endif
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(to7IntensityConverter, new CanBilLcdIlluminationAnalogDevice(can, 1))),
        new WeightedCompositeIlluminationDevice::Leaf(1.0, new IlluminationDevice(to7IntensityConverter, displayStateSender))
    };
    illuminationManager = new Edisson(new WeightedCompositeIlluminationDevice(lightControllers),
                                      new DummyIlluminationSettings());
    if (brightnessViewModel)
        brightnessViewModel->associateManager(illuminationManager);
    CanIlluminationSetter *canIlluminationSetter = new CanIlluminationSetter(illuminationManager, blokMessages);
    canIlluminationSetter;

    // Взаимодествие с пользователем через команды
    keyboard = new Interaction::Keyboards::CompositeKeyboard ({qmlKeyboard, new Interaction::Keyboards::CanKeyboard (&blokMessages->consoleKey1)});
    QObject::connect(keyboard, SIGNAL(keyDown(Key)), levithan, SLOT(beepHigh()));
    storyManager = new Interaction::StoryManager ();
    textManager = new Interaction::TextManager (keyboard);
    textManagerViewModel->assign(textManager);
    Interaction::Commands::VersionRequestCommandFactory vrcf (can, blokMessages, textManager);
    commandManager = new Interaction::CommandManager (storyManager, {
                                                          new Interaction::Commands::ConfigureCommand (cookies, textManager),
                                                          new Interaction::Commands::ManualcoordinateCommand (cookies, textManager),
                                                          new Interaction::Commands::ModulesActivityCommand (&blokMessages->mcoState, textManager),
                                                          new Interaction::Commands::TripConfigurationCommand (cookies, textManager),
                                                          // Запрос версий
                                                          vrcf.produceCommand(0,    "Монитор", SysDiagnostics::BIL, {AuxResource::BIL_A}),
                                                          vrcf.produceCommand(261,  "ЦО", SysDiagnostics::CO, {AuxResource::MCO_A, AuxResource::MCO_B}),
                                                          vrcf.produceCommand(517,  "ЭК", SysDiagnostics::MM, {AuxResource::MM}),
                                                          vrcf.produceCommand(773,  "МП-АЛС", SysDiagnostics::MP_ALS, {AuxResource::MP1_A, AuxResource::MP1_B}),
                                                          vrcf.produceCommand(1029, "ИПД", SysDiagnostics::IPD, {AuxResource::IPD_A, AuxResource::IPD_B}),
                                                          vrcf.produceCommand(1541, "РК", SysDiagnostics::RC, {AuxResource::RC_A, AuxResource::RC_B}),
                                                          vrcf.produceCommand(2053, "ВС-САУТ", SysDiagnostics::SAUT, {AuxResource::SAUT_A, AuxResource::SAUT_B}),
                                                          vrcf.produceCommand(2309, "ТСКБМ-К", SysDiagnostics::TSKBM_K, {AuxResource::TSKBM_K_A, AuxResource::TSKBM_K_B}),
                                                          vrcf.produceCommand(2821, "Шлюз", SysDiagnostics::SHLUZ, {AuxResource::GT_A, AuxResource::GT_B}),
                                                          vrcf.produceCommand(3589, "БС-СН", SysDiagnostics::BS_SN, {AuxResource::AMR}),
                                                          vrcf.produceCommand(3845, "ТСКБМ-П", SysDiagnostics::TSKBM_P, {AuxResource::TSKBM_P_A, AuxResource::TSKBM_P_B}),
                                                          vrcf.produceCommand(4084, "ВДС", SysDiagnostics::VDS, {AuxResource::VDS_A, AuxResource::VDS_B}),
                                                          vrcf.produceCommand(4101, "БС-ДПС", SysDiagnostics::BS_DPS, {AuxResource::BS_DPS_A, AuxResource::BS_DPS_B}),
                                                          vrcf.produceCommand(4357, "ПТК", SysDiagnostics::PTK, {AuxResource::SAUT_PTK_A, AuxResource::SAUT_PTK_B}),
                                                          vrcf.produceCommand(4823, "Вывод", SysDiagnostics::OUTPUT, {AuxResource::OUTPUT_A, AuxResource::OUTPUT_B}),
                                                          vrcf.produceCommand(4869, "МВВ", SysDiagnostics::MVV, {AuxResource::MV_A, AuxResource::MV_B}),
                                                          vrcf.produceCommand(5125, "МСС", SysDiagnostics::MCC, {AuxResource::BIL2_A, AuxResource::BIL2_B}), // Не смогли найти для МСС. Везде использются AUX_RESOURCE_BIL. А мы ещё и запрашиваем вместо МСС монитор.
                                                          // Работа с комплектами ЦО
                                                          new Interaction::Commands::ActiveHalfsetIdicationCommand(&blokMessages->mcoState, textManager),
                                                          //
                                                          new Interaction::Commands::ActiveDpsIndicationCommand(&blokMessages->ipdState, textManager),
                                                      });

    QMap<Interaction::Keyboard::Key, Interaction::Command*> hotkeys;
    hotkeys[Interaction::Keyboard::Key::BRIGHTNESS] = new Interaction::Commands::ChangeBrightnessCommand(illuminationManager, textManager);
    hotkeys[Interaction::Keyboard::Key::P] = new Interaction::Commands::InputTrackNumberCommand(cookies, textManager);
    keyboardManager = new Interaction::KeyboardManager (keyboard, storyManager, commandManager, textManager, &hotkeys );

    QtConcurrent::run(getParamsFromConsole);

    return app->exec();
}
