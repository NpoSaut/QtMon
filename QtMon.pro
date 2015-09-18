# Add more folders to ship with the application, here
folder_01.source = qml/QtMon
folder_01.target = qml
folder_02.source = phrases
folder_02.target =
folder_fonts.source = fonts
DEPLOYMENTFOLDERS = folder_01 folder_02 folder_fonts

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += \
    qtDoodahLib/queues.cpp \
    sound/speakingthread.cpp \
    sound/phrase.cpp \
    main.cpp \
    qtBlokLib/modulesactivity.cpp \
    qtBlokLib/iodrv.cpp \
    qtBlokLib/endecs.cpp \
    qtBlokLib/cookies.cpp \
    qtBlokLib/elmapforwardtarget.cpp \
    qtBlokLib/parsers/aux_resource.cpp \
    qtBlokLib/parsers/canblokmessage.cpp \
    qtBlokLib/parsers/console_key.cpp \
    qtBlokLib/parsers/display_state.cpp \
    qtBlokLib/parsers/mco_limits.cpp \
    qtBlokLib/parsers/mco_mode.cpp \
    qtBlokLib/parsers/mco_state.cpp \
    qtBlokLib/parsers/mm_alt_long.cpp \
    qtBlokLib/parsers/mm_coord.cpp \
    qtBlokLib/parsers/mm_data.cpp \
    qtBlokLib/parsers/mm_station.cpp \
    qtBlokLib/parsers/mp_state.cpp \
    qtBlokLib/parsers/mvd_dd.cpp \
    qtBlokLib/parsers/saut_state.cpp \
    qtBlokLib/parsers/sys_diagnostics.cpp \
    qtBlokLib/parsers/sys_key.cpp \
    qtBlokLib/parsers/ipd_state.cpp \
    qtBlokLib/parsers/ipd_date.cpp \
    qtBlokLib/parsers/tskbm_state.cpp \
    qtBlokLib/parsers/uktol_dd1.cpp \
    qtBlokLib/parsers/vds_state.cpp \
    qtBlokLib/parser.cpp \
    notificator.cpp \
    drivemodehandler.cpp \
    displaystatesender.cpp \
    pressureselector.cpp \
    alsnfreqhandler.cpp \
    autolockhandler.cpp \
    stateserializer.cpp \
    records/staterecorder.cpp \
    records/stateplayer.cpp \
    interaction/story.cpp \
    interaction/storymanager.cpp \
    interaction/keyboardmanager.cpp \
    interaction/textmanager.cpp \
    interaction/contexts/executecommandcontext.cpp \
    interaction/activities/executecommandactivity.cpp \
    interaction/commandmanager.cpp \
    interaction/commands/configurecommand.cpp \
    interaction/keyboard.cpp \
    interaction/KeyboardState.cpp \
    interaction/keyboards/cankeyboard.cpp \
    interaction/keyboards/qmlkeyboard.cpp \
    interaction/keyboards/compositekeyboard.cpp \
    interaction/commands/modulesactivitycommand.cpp \
    interaction/activities/cookiesactiviybase.cpp \
    interaction/activities/displaymodulesactivityactivity.cpp \
    viewmodels/modulesactivityviewmodel.cpp \
    viewmodels/systemstateviewmodel.cpp \
    viewmodels/textmanagerviewmodel.cpp \
    interaction/activities/requestcookiesactivity.cpp \
    interaction/activities/submitcookiesactivity.cpp \
    interaction/activities/inputactivity.cpp \
    interaction/activities/popupactivity.cpp \
    interaction/commands/tripconfigurationcommand.cpp \
    interaction/commands/manualcoordinatecommand.cpp \
    interaction/commands/versionrequestcommand.cpp \
    interaction/activities/versionrequestactivity.cpp \
    interaction/commands/versionrequestcommandfactory.cpp \
    illumination/Edisson.cpp \
    illumination/implementations/DebugAnalogDevice.cpp \
    interaction/activities/changebrightnessactivity.cpp \
    illumination/implementations/IlluminationDevice.cpp \
    illumination/implementations/WeightedCompositeIlluminationDevice.cpp \
    illumination/implementations/FileAnalogDevice.cpp \
    illumination/implementations/LinuxBacklightAnalogDeviceFactory.cpp \
    qtBlokLib/parsers/BilLcd.cpp \
    illumination/implementations/ExponentialIntensityConverter.cpp \
    interaction/commands/activehalfsetidicationcommand.cpp \
    interaction/commands/activedpsindicationcommand.cpp \
    viewmodels/brightnessviewmodel.cpp \
    HardcodedVersion.cpp \
    configuration/CookieConfiguration.cpp \
    qtCanLib/CanFrame.cpp \
    qtCanLib/ICan.cpp \
    qtCanLib/AsyncCan.cpp \
    qtCanLib/AsyncCan/SendWorker.cpp \
    qtCanLib/AsyncCan/ReceiveWorker.cpp \
    qtDoodahLib/IThreadWorker.cpp \
    qtCanLib/AsyncCan/CanPriorityQueue.cpp \
    qtDoodahLib/ThreadWithWorker.cpp \
    qtCanLib/DummyCan.cpp \
    configuration/IConfiguration.cpp \
    configuration/BaseConfiguration.cpp \
    DateTimeConverter.cpp \
    SysKeySender.cpp \
    interaction/contexts/InputTrackNumberContext.cpp \
    interaction/activities/SubmitTrackNumberActivity.cpp \
    interaction/activities/RequestTrackNumberActivity.cpp \
    interaction/commands/InputTrackNumberCommand.cpp \
    interaction/commands/ChangeBrightnessCommand.cpp \
    sound/WolfsonLevithan.cpp \
    sound/Levithan.cpp \
    sound/CanLevithan.cpp \
    qtBlokLib/parsers/console_beep.cpp \
    illumination/CanIlluminationSetter.cpp \
    illumination/implementations/CanBilLcdIlluminationAnalogDevice.cpp \
    qtBlokLib/parsers/bil_bright_level.cpp \
    viewmodels/TrafficLightViewModel.cpp \
    gpio/debuggpio.cpp \
    gpio/gpioproducer.cpp \
    gpio/linuxgpio.cpp \
    LedTrafficlightView.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES +=

OTHER_FILES += \
    properties.xml \
    !TODO.txt \
    viewmodels/modulesacrivityviewmodel.xml \
    viewmodels/properties.xml

HEADERS += \
    cDoodahLib/packing.h \
    cDoodahLib/masqarade.h \
    cDoodahLib/lowlevel.h \
    qtDoodahLib/queues.h \
    sound/speakingthread.h \
    sound/phrase.h \
    qtBlokLib/modulesactivity.h \
    qtBlokLib/iodrvmain.h \
    qtBlokLib/iodrv.h \
    qtBlokLib/endecs.h \
    qtBlokLib/cookies.h \
    qtBlokLib/elmapforwardtarget.h \
    qtBlokLib/parser.h \
    qtBlokLib/parsers/canblokmessage.h \
    qtBlokLib/parsers/display_state.h \
    qtBlokLib/parsers/mm_coord.h \
    qtBlokLib/parsers/mco_limits.h \
    qtBlokLib/parsers/ipd_state.h \
    qtBlokLib/parsers/mco_state.h \
    qtBlokLib/parsers/sys_key.h \
    qtBlokLib/parsers/tskbm_state.h \
    notificator.h \
    displaystatesender.h \
    drivemodehandler.h \
    qtBlokLib/parsers/vds_state.h \
    qtBlokLib/parsers/drivemode.h \
    qtBlokLib/parsers/uktol_dd1.h \
    qtBlokLib/parsers/pressure.h \
    qtBlokLib/parsers/mvd_dd.h \
    pressureselector.h \
    qtBlokLib/parsers/mp_state.h \
    qtBlokLib/parsers/trafficlight.h \
    alsnfreqhandler.h \
    autolockhandler.h \
    qtBlokLib/parsers/mm_alt_long.h \
    qtBlokLib/parsers/mco_mode.h \
    qtBlokLib/parsers/autolockmode.h \
    qtBlokLib/parsers/console_key.h \
    qtBlokLib/parsers/saut_state.h \
    qtBlokLib/parsers/mm_station.h \
    stateserializer.h \
    records/staterecorder.h \
    records/stateplayer.h \
    qtBlokLib/parsers/aux_resource.h \
    qtBlokLib/parsers/ipd_date.h \
    qtBlokLib/parsers/mm_data.h \
    qtBlokLib/parsers/sys_diagnostics.h \
    interaction/activity.h \
    interaction/story.h \
    interaction/storymanager.h \
    interaction/keyboardmanager.h \
    interaction/textmanager.h \
    interaction/contexts/executecommandcontext.h \
    interaction/activities/executecommandactivity.h \
    interaction/command.h \
    interaction/commandmanager.h \
    interaction/commands/configurecommand.h \
    interaction/context.h \
    interaction/keyboard.h \
    interaction/KeyboardState.h \
    interaction/keyboards/cankeyboard.h \
    interaction/keyboards/qmlkeyboard.h \
    interaction/keyboards/compositekeyboard.h \
    interaction/commands/modulesactivitycommand.h \
    interaction/activities/displaymodulesactivityactivity.h \
    viewmodels/modulesactivityviewmodel.h \
    viewmodels/systemstateviewmodel.h \
    viewmodels/textmanagerviewmodel.h \
    interaction/contexts/cookiescontext.h \
    interaction/activities/cookiesactiviybase.h \
    interaction/activities/requestcookiesactivity.h \
    interaction/activities/submitcookiesactivity.h \
    interaction/activities/inputactivity.h \
    interaction/activities/popupactivity.h \
    interaction/commands/tripconfigurationcommand.h \
    interaction/commands/manualcoordinatecommand.h \
    interaction/commands/versionrequestcommand.h \
    interaction/contexts/versionrequestcontext.h \
    interaction/activities/versionrequestactivity.h \
    interaction/commands/versionrequestcommandfactory.h \
    illumination/Edisson.h \
    illumination/interfaces/IAnalogDevice.h \
    illumination/interfaces/IIlluminationSettings.h \
    illumination/interfaces/IIntensityConverter.h \
    illumination/implementations/DummyIlluminationSettings.h \
    illumination/implementations/LinearIntensityConverter.h \
    illumination/interfaces/IIlluminationManager.h \
    illumination/implementations/DebugAnalogDevice.h \
    interaction/contexts/changebrightnesscontext.h \
    interaction/activities/changebrightnessactivity.h \
    illumination/interfaces/IIlluminationDevice.h \
    illumination/implementations/IlluminationDevice.h \
    illumination/implementations/WeightedCompositeIlluminationDevice.h \
    illumination/implementations/FileAnalogDevice.h \
    illumination/implementations/LinuxBacklightAnalogDeviceFactory.h \
    qtBlokLib/parsers/BilLcd.h \
    illumination/implementations/ExponentialIntensityConverter.h \
    interaction/commands/activehalfsetidicationcommand.h \
    interaction/commands/activedpsindicationcommand.h \
    viewmodels/brightnessviewmodel.h \
    HardcodedVersion.h \
    configuration/IConfiguration.h \
    configuration/CookieConfiguration.h \
    qtDoodahLib/queues/IThreadSafeQueue.h \
    qtDoodahLib/queues/LinerThreadSafeQueue.h \
    qtDoodahLib/queues/PriorityThreadSafeQueue.h \
    qtCanLib/CanFrame.h \
    qtCanLib/ICan.h \
    qtCanLib/AsyncCan.h \
    qtCanLib/AsyncCan/SendWorker.h \
    qtCanLib/AsyncCan/ReceiveWorker.h \
    qtDoodahLib/IThreadWorker.h \
    qtCanLib/AsyncCan/CanPriorityQueue.h \
    qtDoodahLib/ThreadWithWorker.h \
    qtCanLib/drivers/IBlockedReceiver.h \
    qtCanLib/drivers/IBlockedReceiverFactory.h \
    qtCanLib/drivers/IBlockedSender.h \
    qtCanLib/drivers/IBlockedSenderFactory.h \
    qtCanLib/drivers/DummyCan/DummyCanReceiver.h \
    qtCanLib/drivers/DummyCan/DummyCanSender.h \
    qtCanLib/drivers/DummyCan/DummyCanReceiverFactory.h \
    qtCanLib/drivers/DummyCan/DummyCanSenderFactory.h \
    qtCanLib/DummyCan.h \
    configuration/BaseConfiguration.h \
    DateTimeConverter.h \
    SysKeySender.h \
    interaction/contexts/InputTrackNumberContext.h \
    interaction/activities/SubmitTrackNumberActivity.h \
    interaction/activities/RequestTrackNumberActivity.h \
    interaction/commands/InputTrackNumberCommand.h \
    interaction/commands/ChangeBrightnessCommand.h \
    sound/WolfsonLevithan.h \
    sound/Levithan.h \
    sound/CanLevithan.h \
    qtBlokLib/parsers/console_beep.h \
    illumination/CanIlluminationSetter.h \
    illumination/implementations/CanBilLcdIlluminationAnalogDevice.h \
    qtBlokLib/parsers/bil_bright_level.h \
    viewmodels/TrafficLightViewModel.h \
    gpio/debuggpio.h \
    gpio/dummygpio.h \
    gpio/gpio.h \
    gpio/gpioproducer.h \
    gpio/linuxgpio.h \
    LedTrafficlightView.h

LIB_LINUX_SOCKET_CAN_DRIVER {
    SOURCES +=  qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanReceiver.cpp \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanReceiverFactory.cpp \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSender.cpp \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSenderFactory.cpp \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSocketFactory.cpp \
                qtCanLib/drivers/LinuxSocketCan/cSocketCanLib/src/SocketCanLib.c

    HEADERS +=  qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanReceiver.h \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanReceiverFactory.h \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSender.h \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSenderFactory.h \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSocket.h \
                qtCanLib/drivers/LinuxSocketCan/LinuxSocketCanSocketFactory.h \
                qtCanLib/drivers/LinuxSocketCan/cSocketCanLib/src/SocketCanLib.h

    DEFINES += LIB_LINUX_SOCKET_CAN_DRIVER
}

LIB_APPI_CAN_DRIVER {
    SOURCES +=  qtCanLib/drivers/AppiCan/LibusbDevice.cpp \
                qtCanLib/drivers/AppiCan/LibusbDeviceFactory.cpp \
                qtCanLib/drivers/AppiCan/AppiCan.cpp \
                qtCanLib/drivers/AppiCan/AppiBlockCan1.cpp

    HEADERS +=  qtCanLib/drivers/AppiCan/libusb.h \
                qtCanLib/drivers/AppiCan/LibusbDevice.h \
                qtCanLib/drivers/AppiCan/LibusbDeviceFactory.h \
                qtCanLib/drivers/AppiCan/AppiCan.h \
                qtCanLib/drivers/AppiCan/AppiCanReceiverFactory.h \
                qtCanLib/drivers/AppiCan/AppiCanSenderFactory.h \
                qtCanLib/drivers/AppiCan/AppiBlockCan1.h

    LIBS    +=  -L"$$_PRO_FILE_PWD_/qtCanLib/drivers/AppiCan/" -lusb-1.0

    DEFINES += LIB_APPI_CAN_DRIVER
    DEFINES += WIN32
}

CONFIG += console

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += QT_NO_CAST_FROM_ASCII

#unix:!macx:!symbian|win32: LIBS += -lQtSerialPort

# Для работы нужны:
# DEFINES+=CPP11 DEFINES+=ON_DEVICE CONFIG+=LIB_LINUX_SOCKET_CAN_DRIVER

