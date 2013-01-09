#include <QApplication>
#include "qmlapplicationviewer.h"
#include "systemstateviewmodel.h"
#include "qtconcurrentrun.h"
#include <QTextStream>

#ifdef WITH_CAN
#include "sktcanl/src/sktcanl.h"
#endif

#include <iostream>

SystemStateViewModel *systemState ;

void getSpeed (double* speed)
{
    systemState->setSpeed( int(*speed) );
}

void getSpeedLimits (int* val)
{
    systemState->setSpeedRestriction(*val);
}

void getLights (int* code)
{
    systemState->setLight(*code);
}

void getAlsn (int* code)
{
    if (*code == 0)
        systemState->setAlsnFreq(50);
    else if (*code == 1)
        systemState->setAlsnFreq(75);
    else if (*code == 2)
        systemState->setAlsnFreq(50);
    else if (*code == 3)
        systemState->setAlsnFreq(25);
}

void getMilage (int* val)
{
    systemState->setMilage( (*val)/1000 );
}

void getGps (double* lat, double* lon)
{
    systemState->setLongitude(*lon);
    systemState->setLatitude(*lat);
}

void getDateTime (int* h, int* m, int* s)
{
    QString date = QString("%1:%2:%3").arg(*h).arg(*m).arg(*s);
    systemState->setTime(date);
}

#ifdef WITH_CAN
//extern void aFunction();
//QFuture<void> future = QtConcurrent::run(aFunction);
void getParamsFromCan ()
{
    sktcanl_init();
    sktcanl_set_callbacks(getSpeed, getSpeedLimits, NULL, NULL, getLights, getAlsn, getMilage, NULL, NULL, getGps, getDateTime);

    while (true)
    {
        sktcanl_read_can_msg();
    }
}
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
        else if (cmd.at(0) == "map")
        {
            systemState->setPropertyView(false);
            out << "PropertyView mode: " << systemState->getPropertyView() << endl;
        }
        else if (cmd.at(0) == "property")
        {
            systemState->setPropertyView(true);
            out << "PropertyView mode: " << systemState->getPropertyView() << endl;
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
            systemState->setAlsnFreq( cmd.at(1).toInt() );
            out << "AlsnFreq: " << systemState->getAlsnFreq() << endl;
        }
        else
        {
            out << "! unknown command. Try this: s r map property g" << endl;
        }
    }
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

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
    QtConcurrent::run(getParamsFromCan);
#else
    QtConcurrent::run(getParamsFromConsole);
#endif

    return app->exec();
}
