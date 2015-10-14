#include "ConsoleStateViewModelController.h"

#include <unistd.h>
#include <QDebug>

using namespace ConsoleStateViewModelControllerInternals;

ConsoleStateViewModelController::ConsoleStateViewModelController(ViewModels::SystemStateViewModel *model, QObject *parent) :
    QObject (parent),
    model (model),
    workerThread (new Reader(), this),
    out (stdout)
{
    Reader *reader = (Reader *)workerThread.worker;
    QObject::connect(reader, SIGNAL(newLine(QString)), this, SLOT(readLine(QString)));
}

void ConsoleStateViewModelController::start()
{
    workerThread.start();
}

void ConsoleStateViewModelController::readLine(QString s)
{
    QStringList cmd = s.split(" ");

    if (cmd.at(0) == "s")
    {
        model->setSpeed( cmd.at(1).toInt() );
        model->setSpeedIsValid(true);
        out << "Speed: " << model->getSpeed() << endl;
    }
    else if (cmd.at(0) == "r")
    {
        model->setSpeedRestriction( cmd.at(1).toInt() );
        out << "Speed restriction: " << model->getSpeedRestriction() << endl;
    }
    else if (cmd.at(0) == "g")
    {
        if (cmd.size() == 3)
        {
            model->setLongitude( cmd.at(1).toDouble() );
            model->setLatitude( cmd.at(2).toDouble() );
        }
        out << "Longitude: " << model->getLongitude()
            << "; Lattitude: " << model->getLatitude() << endl;
    }
    else if (cmd.at(0) == "gg")
    {
        if (cmd.size() == 3)
        {
            model->setLongitude(model->getLongitude() + cmd.at(1).toDouble() );
            model->setLatitude(model->getLatitude() + cmd.at(2).toDouble() );
        }
        out << "Longitude: " << model->getLongitude()
            << "; Lattitude: " << model->getLatitude() << endl;
    }
    else if (cmd.at(0) == "c")
    {
        model->trafficLights()->setCode( Trafficlight(cmd.at(1).toInt()) );
        out << "Liht: " << model->trafficLights()->code() << endl;
    }
    else if (cmd.at(0) == "a")
    {
        model->setAlsnFreqTarget( cmd.at(1).toInt() );
        out << "AlsnFreqTarget: " << model->getAlsnFreqTarget() << endl;
    }
    else if (cmd.at(0) == "epv")
    {
        model->setIsEpvReady( cmd.at(1) == "1" );
        out << "IsEpvReady: " << model->getIsEpvReady() << endl;
    }
    else if (cmd.at(0) == "b")
    {
        model->setIsEpvReleased( cmd.at(1) == "1" );
        out << "IsEpvReady: " << model->getIsEpvReleased() << endl;
    }
    else if (cmd.at(0) == "dm")
    {
        model->setDriveModeFact( cmd.at(1).toInt() );
        out << "DriveModeFact: " << model->getDriveModeFact() << endl;
    }
    else if (cmd.at(0) == "tdm")
    {
        model->setDriveModeTarget( cmd.at(1).toInt() );
        out << "DriveModeTarget: " << model->getDriveModeTarget() << endl;
    }
    else if (cmd.at(0) == "iw")
    {
        model->setIronWheels( cmd.at(1) == "1" );
        out << "Iron Wheels: " << model->getIronWheels() << endl;
    }
    // Тяга
    else if (cmd.at(0) == "tr")
    {
        model->setIsTractionOn( cmd.at(1) == "1" );
        out << "Traction is: " << model->getIsTractionOn() << endl;
    }
    // Направление движения
    else if (cmd.at(0) == "dir")
    {
        model->setDirection( cmd.at(1).toInt() );
        out << "Now Direction is: " << model->getDirection() << endl;
    }
    // ТСКБМ: на связи
    else if (cmd.at(0) == "tso")
    {
        model->setTsvcIsOnline( cmd.at(1) == "1" );
        out << "Now TSVC online is: " << model->getTsvcIsOnline() << endl;
    }
    // ТСКБМ: Машинист Бодр
    else if (cmd.at(0) == "tsc")
    {
        model->setTsvcIsMachinistCheerful( cmd.at(1) == "1" );
        out << "Now is Machinist Cheerful is: " << model->getTsvcIsMachinistCheerful() << endl;
    }
    // ТСКБМ: на связи
    else if (cmd.at(0) == "tsv")
    {
        model->setTsvcIsVigilanceRequired( cmd.at(1) == "1" );
        out << "Now TSVC Vigilance Required is: " << model->getTsvcIsVigilanceRequired() << endl;
    }
    // ТСКБМ: на связи
    else if (cmd.at(0) == "tsa")
    {
        model->setTsvcIsPreAlarmActive( cmd.at(1) == "1" );
        out << "Now TSVC Pre-Alarm is: " << model->getTsvcIsPreAlarmActive() << endl;
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
    }
}


Reader::Reader()
    : IThreadWorker()
{ }

void Reader::run()
{
    qDebug() << "Starting reading console...";
    QTextStream in(stdin);
    forever
    {
        if (in.atEnd())
            usleep (1000);
        else
            emit newLine(in.readLine());

    }
}
