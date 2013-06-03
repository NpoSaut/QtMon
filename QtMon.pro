# Add more folders to ship with the application, here
folder_01.source = qml/QtMon
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    systemstateviewmodel.cpp \
    iodrv/endecs.cpp \
    iodrv/sktcan.cpp \
    iodrv/iodrv.cpp \
    electroincmap.cpp \
    emap/kilometerpost.cpp \
    emap/routesection.cpp \
    emap/rail.cpp \
    emap/railobject.cpp \
    emap/emaptarget.cpp \
    iodrv/emapcanemitter.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES +=

OTHER_FILES += \
    properties.xml

HEADERS += \
    systemstateviewmodel.h \
    iodrv/sktcan.h \
    iodrv/endecs.h \
    iodrv/iodrvmain.h \
    iodrv/iodrv.h \
    electroincmap.h \
    emap/kilometerpost.h \
    emap/routesection.h \
    emap/almanac.h \
    emap/rail.h \
    emap/railobject.h \
    packing.h \
    emap/emaptarget.h \
    iodrv/emapcanemitter.h

CONFIG += console

QMAKE_CXXFLAGS += -std=c++0x

#DEFINES += QT_NO_CAST_FROM_ASCII

#unix:!macx:!symbian|win32: LIBS += -lQtSerialPort
