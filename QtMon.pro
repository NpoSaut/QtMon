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
    electroincmap.cpp \
    emap/kilometerpost.cpp \
    emap/routesection.cpp \
    emap/rail.cpp \
    emap/railobject.cpp \
    emap/emaptarget.cpp \
    iodrv/emapcanemitter.cpp\
    levithan.cpp \
    sound/speakingthread.cpp \
    sound/phrase.cpp \
    main.cpp \
    qtBlokLib/sysdiagnostics.cpp \
    qtBlokLib/modulesactivity.cpp \
    qtBlokLib/iodrv.cpp \
    qtBlokLib/endecs.cpp \
    qtBlokLib/cookies.cpp

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
    electroincmap.h \
    emap/kilometerpost.h \
    emap/routesection.h \
    emap/almanac.h \
    emap/rail.h \
    emap/railobject.h \
    emap/emaptarget.h \
    iodrv/emapcanemitter.h\
    levithan.h \
    sound/speakingthread.h \
    sound/phrase.h \
    qtBlokLib/sysdiagnostics.h \
    qtBlokLib/modulesactivity.h \
    qtBlokLib/iodrvmain.h \
    qtBlokLib/iodrv.h \
    qtBlokLib/endecs.h \
    qtBlokLib/cookies.h

CONFIG += console

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += QT_NO_CAST_FROM_ASCII

#unix:!macx:!symbian|win32: LIBS += -lQtSerialPort
