#ifndef TEXTNOTIFICATIONMODEL_H
#define TEXTNOTIFICATIONMODEL_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "systemstateviewmodel.h"

namespace ViewModels {

class TextNotificationModel : public QObject
{
    Q_OBJECT
public:
    explicit TextNotificationModel(SystemStateViewModel *stateViewModel, QObject *parent = 0);

    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool handbrakeHintRequired READ isHandbrakeHintRequired WRITE setHandbrakeHintRequired NOTIFY handbrakeHintRequiredChanged)

    QString getText() const;
    bool isHandbrakeHintRequired() const;

signals:
    void textChanged(QString arg);
    void handbrakeHintRequiredChanged(bool arg);

public slots:
    void setText(QString arg);
    void setHandbrakeHintRequired(bool arg);

private slots:
    void show ();
    void setHandbrakeHint ();

private:
    SystemStateViewModel *_stateViewModel;
    QString _text;
    QTimer _handbrakeHintTimeout;
    bool _handbrakeHintRequired;
    bool _handbrakeHint;
};

}

#endif // TEXTNOTIFICATIONMODEL_H
