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
#include "viewmodels/TextNotificationModel.h"
#include "ConsoleStateViewModelController.h"
#include "sound/KxSoundController.h"
#include "sound/WolfsonLevithan.h"
#include "sound/ToCanLevithan.h"
#include "sound/PhraseNumberLevithan.h"
#include "sound/QSoundMouthFactory.h"
#include "sound/ExternalToolMouthFactory.h"

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

#include "displaystatesender.h"
#include "SysKeySender.h"
#include "drivemodehandler.h"
#include "pressureselector.h"
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
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/QtMon/main.qml"));
#ifdef ON_DEVICE
    viewer.showFullScreen();
#else
    viewer.showExpanded();
#endif

    QObject *object = viewer.rootObject();
    ViewModels::SystemStateViewModel *systemState = object->findChild<ViewModels::SystemStateViewModel*>("stateView");
    ViewModels::TextManagerViewModel *textManagerViewModel = object->findChild<ViewModels::TextManagerViewModel*>("textManager");
    Interaction::Keyboards::QmlKeyboard *qmlKeyboard = object->findChild<Interaction::Keyboards::QmlKeyboard*>("keyboardProxy");
    ViewModels::BrightnessViewModel *brightnessViewModel = object->findChild<ViewModels::BrightnessViewModel*>("brightnessViewModel");
    ViewModels::TextNotificationModel *textNotificationViewModel = new ViewModels::TextNotificationModel (systemState);

    // Создание CAN
    QThread canThread;
    ICan *can;
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

    Parser *blokMessages = new Parser(can);
    iodrv* iodriver = new iodrv(can);
    Cookies *cookies = new Cookies(can);

    ElmapForwardTarget *elmapForwardTarget = new ElmapForwardTarget(can);


    GpioProducer *gpioProducer =
#ifdef Q_OS_LINUX
        new GpioProducer (GpioProducer::LINUX);
#endif
#ifdef Q_OS_WIN
        new GpioProducer (GpioProducer::DUMMY);
#endif

    // Конфигурация
    IConfiguration *configuration = new CookieConfiguration (&cookies->monitorKhConfiguration);
    QObject::connect(configuration, SIGNAL(breakAssistRequiredChanged(bool)), textNotificationViewModel, SLOT(setHandbrakeHintRequired(bool)));
    configuration->update();

    // Выдаёт версию по AUX_RESOURCE
    HardcodedVersion *hardcodedVersion = new HardcodedVersion(3, 3, can);
    QObject::connect (&blokMessages->sysDiagnostics, SIGNAL(versionRequested(SysDiagnostics::AuxModule)), hardcodedVersion, SLOT(onVersionRequest(SysDiagnostics::AuxModule)));

    // Создание и подключение «обработчиков»
    // -> Отбработчик нажатия РМП <-
    DrivemodeHandler *drivemodeHandler = new DrivemodeSettingHandler(blokMessages, can);
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
    QObject::connect(&blokMessages->mcoLimits, SIGNAL(tractionShutdownCommandChanged(bool)), systemState, SLOT(setIsTractionShutdown(bool)));
    QObject::connect(&blokMessages->mcoLimits, SIGNAL(slippingChanged(bool)), systemState, SLOT(setIsSlipping(bool)));
    QObject::connect(&blokMessages->ipdState, SIGNAL(inMotionChanged(bool)), systemState, SLOT(setIsInMotion(bool)));

    // Уведомления
    QObject::connect (textNotificationViewModel, SIGNAL(textChanged(QString)), systemState, SLOT(setNotificationText(QString)));

    //Одометр
    QObject::connect(iodriver, SIGNAL(signal_passed_distance(int)), systemState, SLOT(setMilage(int)));

    //Светофоры:
    // огонь
    QObject::connect (&blokMessages->mcoState, SIGNAL(trafficlightChanged(Trafficlight)), systemState->trafficLights(), SLOT(setCode(Trafficlight)));
    LedTrafficlightView *ledTrafficlightView = new LedTrafficlightView(systemState->trafficLights(), gpioProducer);
#ifdef LIB_LINUX_SPIDEV
    ISpiDev *spiDev = new LinuxSpiDev ("/dev/spidev0.0", 1000000, 8);
    Max100500 *max100500 = new Max100500 (spiDev);
    Max100500TrafficlightView *max100500TrafficlightView = new Max100500TrafficlightView(systemState->trafficLights(), max100500);
#endif
    // частота
    AlsnFreqHandler *alsnFreqHandler = new AlsnFreqSettingHandler (can, blokMessages);
    QObject::connect(alsnFreqHandler, SIGNAL(actualAlsnFreqChanged(int)), systemState, SLOT(setAlsnFreqFact(int)));
    QObject::connect (alsnFreqHandler, SIGNAL(targetAlsnFreqChanged(int)), systemState, SLOT(setAlsnFreqTarget(int)));
    QObject::connect(systemState, SIGNAL(AlsnFreqTargetChanged(int)), alsnFreqHandler, SLOT(proccessNewTargetAlsnFreq(int)));

    QObject::connect(iodriver, SIGNAL(signal_vigilance(bool)), systemState, SLOT(setIsVigilanceRequired(bool)));
    QObject::connect(iodriver, SIGNAL(signal_movement_direction(int)), systemState, SLOT(setDirection(int)));
    QObject::connect(iodriver, SIGNAL(signal_reg_tape_avl(bool)), systemState, SLOT(setIsRegistrationTapeActive(bool)));

    // Автоблокировка АБ
    AutolockHandler *autolockHandler = new AutolockHandler (can, blokMessages);
    QObject::connect(autolockHandler, SIGNAL(actualAutolockModeChanged(int)), systemState, SLOT(setAutolockTypeFact(int)));
    QObject::connect (autolockHandler, SIGNAL(targetAutlockModeChanged(int)), systemState, SLOT(setAutolockTypeTarget(int)));
    QObject::connect(systemState, SIGNAL(AutolockTypeTargetChanged(int)), autolockHandler, SLOT(setTargetMode(int)));
    QObject::connect (systemState, SIGNAL(AutolockSpeedChanged(int)), autolockHandler, SLOT(setWhiteSpeed(int)));

    // Давление
    PressureSelector *pressureSelector = new PressureSelector (PressureSelector::MPA, true, blokMessages);
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

    // Клавиатура
    Interaction::Keyboard *keyboard = new Interaction::Keyboards::CompositeKeyboard ({qmlKeyboard, new Interaction::Keyboards::CanKeyboard (&blokMessages->consoleKey1)});
    Interaction::KeyboardState *keyboardState = new Interaction::KeyboardState (keyboard);
    DisplayStateSender* displayStateSender = new DisplayStateSender(keyboardState, can);
    QObject::connect(drivemodeHandler, SIGNAL(targetDrivemodeChanged(int)), displayStateSender, SLOT(setDriveMode(int)));
    SysKeySender *sysKeySender = new SysKeySender(keyboard, can);

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
    IIlluminationManager *illuminationManager = new Edisson(new WeightedCompositeIlluminationDevice(lightControllers),
                                      new DummyIlluminationSettings());
    if (brightnessViewModel)
        brightnessViewModel->associateManager(illuminationManager);
    CanIlluminationSetter *canIlluminationSetter = new CanIlluminationSetter(illuminationManager, blokMessages);
    canIlluminationSetter;

    // Взаимодествие с пользователем через команды
    Interaction::StoryManager *storyManager = new Interaction::StoryManager ();
    Interaction::TextManager *textManager = new Interaction::TextManager (keyboard);
    textManagerViewModel->assign(textManager);
    Interaction::Commands::VersionRequestCommandFactory vrcf (can, blokMessages, textManager);
    Interaction::CommandManager *commandManager = new Interaction::CommandManager (storyManager, {
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
    Interaction::KeyboardManager *keyboardManager = new Interaction::KeyboardManager (keyboard, storyManager, commandManager, textManager, &hotkeys );

    // Звуки
    Sound::IMouthFactory *mouthFactory =
#ifdef _WIN32
        new Sound::ExternalToolMouthFactory("runtime-utils-win/mpg123 \"%1\"");
#else
        new Sound::ExternalToolMouthFactory("sh -x -c \"madplay -A-18 -owave:- '%1' | aplay\""); // Громкость: -18 дБ
#endif
    Sound::Speaker *speaker = new Sound::Speaker (mouthFactory);
    Sound::WolfsonLevithan levithan (speaker);
    Sound::KxSoundController kxSoundController (systemState, keyboard, &levithan);
    Sound::PhraseNumberLevithan *phraseNumberLevithan = new Sound::PhraseNumberLevithan (QDir("./phrases/bri/"), speaker);
    QObject::connect(&blokMessages->soundCommand, SIGNAL(sayPhraseNumber(int)), phraseNumberLevithan, SLOT(sayPhrase(int)));

    ConsoleStateViewModelController consoleStateViewModelController (systemState);
    consoleStateViewModelController.start();

    return app->exec();
}
