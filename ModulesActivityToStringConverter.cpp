#include "ModulesActivityToStringConverter.h"

ModulesActivityToStringConverter::ModulesActivityToStringConverter(QObject *parent) :
    QObject(parent)
{
}

void ModulesActivityToStringConverter::processActivity(ModulesActivity activity)
{
    emit activityChanged(activity.toString());
}
