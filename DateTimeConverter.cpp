#include "DateTimeConverter.h"

DateTimeConverter::DateTimeConverter(QObject *parent) :
    QObject(parent)
{
}

void DateTimeConverter::processDateTime(QDateTime dt)
{
    emit dateChanged (printDate (dt.date()));
    emit timeChanged (printTime (dt.time()));
}

QString DateTimeConverter::printDate(QDate d)
{
    QString monthString[12] = {"января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};
    return QString("%1 %2 %3")
                    .arg(d.day(), 2, 10, QChar('0'))
                    .arg(monthString[d.month()-1])
                    .arg(d.year(), 2, 10, QChar('0'));
}

QString DateTimeConverter::printTime(QTime t)
{
    return QString("%1:%2:%3")
                    .arg(t.hour(), 2, 10, QChar('0'))
                    .arg(t.minute(), 2, 10, QChar('0'))
                    .arg(t.second(), 2, 10, QChar('0'));
}
