#ifndef TRAFFICLIGHTVIEWMODEL_H
#define TRAFFICLIGHTVIEWMODEL_H

#include <QObject>

class TrafficLightViewModel : public QObject
{
    Q_OBJECT
    int m_code;

    int m_lightsMask;

public:
    explicit TrafficLightViewModel(QObject *parent = 0);

    Q_PROPERTY(int code READ code WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(int lightsMask READ lightsMask NOTIFY lightsMaskChanged)

    int code() const { return m_code; }
    int lightsMask() const { return m_lightsMask; }

signals:

    void codeChanged(int arg);
    void lightsMaskChanged(int arg);

public slots:

    void setCode(int arg)
    {
        if (m_code != arg) {
            m_code = arg;
            emit codeChanged(arg);
        }
    }

private slots:

    void process();

private:

    void setLightsMask(int arg)
    {
        if (m_lightsMask != arg) {
            m_lightsMask = arg;
            emit lightsMaskChanged(arg);
        }
    }
};

#endif // TRAFFICLIGHTVIEWMODEL_H
