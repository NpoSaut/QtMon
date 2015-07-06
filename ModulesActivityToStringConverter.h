#ifndef MODULESACTIVITYTOSTRINGCONVERTER_H
#define MODULESACTIVITYTOSTRINGCONVERTER_H

#include <QObject>
#include <QString>

#include "qtBlokLib/modulesactivity.h"

class ModulesActivityToStringConverter : public QObject
{
    Q_OBJECT
public:
    explicit ModulesActivityToStringConverter(QObject *parent = 0);

signals:
    void activityChanged (QString);

public slots:
    void processActivity (ModulesActivity activity);
};

#endif // MODULESACTIVITYTOSTRINGCONVERTER_H
