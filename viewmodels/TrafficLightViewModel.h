#ifndef TRAFFICLIGHTVIEWMODEL_H
#define TRAFFICLIGHTVIEWMODEL_H

#include <QObject>
#include <QTimer>

class TrafficLightViewModel : public QObject
{
    Q_OBJECT
    int _code;
    int _lights;
    int _mask;
    int _blink;
    int _number;
    QTimer *_timer;

public:
    explicit TrafficLightViewModel(QObject *parent = 0);

    Q_PROPERTY(int code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(int lights READ lights NOTIFY lightsMaskChanged)
    Q_PROPERTY(int number READ number NOTIFY numberChanged)

    int code() const { return _code; }
    int number() const { return _number; }
    int lights();

signals:
    void codeChanged(int arg);
    void lightsMaskChanged(int arg);
    void numberChanged(int arg);

public slots:
    void setCode(int arg)
    {
        if (_code != arg) {
            _code = arg;
            emit codeChanged(arg);
        }
    }

private slots:
    void processCode();
    void tick();

private:
    void refresh();
};

#endif // TRAFFICLIGHTVIEWMODEL_H
