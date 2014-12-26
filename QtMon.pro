# Add more folders to ship with the application, here
folder_01.source = qml/QtMon
folder_01.target = qml
folder_02.source = phrases
folder_02.target =
DEPLOYMENTFOLDERS = folder_01 folder_02

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
    qtCanLib/canframe.cpp \
    qtCanLib/socketcan/sktcan.cpp \
    qtCanLib/socketcan.cpp \
    qtDoodahLib/queues.cpp \
    qtCanLib/socketcan/cansendqueue.cpp \
    levithan.cpp \
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
    trafficlightadaptor.cpp \
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
    interaction/activities/versionrequestactivity.cpp

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
    qtCanLib/canframe.h \
    qtCanLib/can.h \
    qtDoodahLib/queues.h \
    qtCanLib/socketcan/sktcan.h \
    qtCanLib/socketcan/cansendqueue.h \
    levithan.h \
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
    qtCanLib/socketcan.h \
    qtCanLib/dummycan.h \
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
    trafficlightadaptor.h \
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
    interaction/activities/versionrequestactivity.h

CONFIG += console

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += QT_NO_CAST_FROM_ASCII

#unix:!macx:!symbian|win32: LIBS += -lQtSerialPort

# Для работы нужны:
# DEFINES+=CPP11 DEFINES+=WITH_CAN DEFINES+=ON_DEVICE

