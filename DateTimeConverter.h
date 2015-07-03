#ifndef DATETIMECONVERTER_H
#define DATETIMECONVERTER_H

#include <QObject>
#include <QDateTime>
#include <QString>

class DateTimeConverter : public QObject
{
    Q_OBJECT
public:
    explicit DateTimeConverter(QObject *parent = 0);

signals:
    void dateChanged (QString );
    void timeChanged (QString );

public slots:
    void processDateTime (QDateTime dt);

private:
    QString printDate (QDate d);
    QString printTime (QTime t);
};

#endif // DATETIMECONVERTER_H
