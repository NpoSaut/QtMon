#ifndef CONSOLESTATEVIEWMODELCONTROLLER_H
#define CONSOLESTATEVIEWMODELCONTROLLER_H

#include "viewmodels/systemstateviewmodel.h"
#include "qtDoodahLib/ThreadWithWorker.h"

class ConsoleStateViewModelController : public QObject
{
    Q_OBJECT
public:
    ConsoleStateViewModelController(ViewModels::SystemStateViewModel *model, QObject *parent = 0);

    void start ();

private slots:
    void readLine (QString s);

private:
    ViewModels::SystemStateViewModel *model;
    ThreadWithWorker workerThread;
    QTextStream out;
};

namespace ConsoleStateViewModelControllerInternals
{

class Reader : public IThreadWorker
{
    Q_OBJECT
public:
    explicit Reader ();
    virtual void run ();

signals:
    void newLine (QString );
};

}

#endif // CONSOLESTATEVIEWMODELCONTROLLER_H
