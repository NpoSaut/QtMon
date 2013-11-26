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
    systemstateviewmodel.cpp \
    levithan.cpp \
    sound/speakingthread.cpp \
    sound/phrase.cpp \
    main.cpp \
    qtBlokLib/sysdiagnostics.cpp \
    qtBlokLib/modulesactivity.cpp \
    qtBlokLib/iodrv.cpp \
    qtBlokLib/endecs.cpp \
    qtBlokLib/cookies.cpp \
    qtBlokLib/elmapforwardtarget.cpp \
    qtBlokLib/parser.cpp \
    notificator.cpp \
    qtBlokLib/parsers/canblokmessage.cpp \
    qtBlokLib/parsers/display_state.cpp \
    qtBlokLib/parsers/mm_coord.cpp \
    qtBlokLib/parsers/mco_limits.cpp \
    qtBlokLib/parsers/ipd_state.cpp \
    qtBlokLib/parsers/mco_state.cpp \
    qtBlokLib/parsers/sys_key.cpp \
    qtBlokLib/parsers/tskbm_state.cpp \
    drivemodehandler.cpp \
    qtBlokLib/parsers/vds_state.cpp \
    displaystatesender.cpp \
    qtBlokLib/parsers/uktol_dd1.cpp \
    qtBlokLib/parsers/mvd_dd.cpp \
    pressureselector.cpp \
    qtBlokLib/parsers/mp_state.cpp \
    trafficlightadaptor.cpp \
    alsnfreqhandler.cpp \
    autolockhandler.cpp \
    qtBlokLib/parsers/mm_alt_long.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES +=

OTHER_FILES += \
    properties.xml \
    !TODO.txt

HEADERS += \
    cDoodahLib/packing.h \
    cDoodahLib/masqarade.h \
    cDoodahLib/lowlevel.h \
    qtCanLib/canframe.h \
    qtCanLib/can.h \
    qtDoodahLib/queues.h \
    qtCanLib/socketcan/sktcan.h \
    qtCanLib/socketcan/cansendqueue.h \
    systemstateviewmodel.h \
    levithan.h \
    sound/speakingthread.h \
    sound/phrase.h \
    qtBlokLib/sysdiagnostics.h \
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
    qtBlokLib/parsers/mm_alt_long.h

CONFIG += console

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += QT_NO_CAST_FROM_ASCII

#unix:!macx:!symbian|win32: LIBS += -lQtSerialPort

# Для работы нужны:
# DEFINES+=CPP11 DEFINES+=WITH_CAN DEFINES+=ON_DEVICE

