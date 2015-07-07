#ifndef BRIGHTNESSVIEWMODEL_H
#define BRIGHTNESSVIEWMODEL_H

#include <QObject>
#include "illumination/interfaces/IIlluminationManager.h"

namespace ViewModels
{

class BrightnessViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    IIlluminationManager *_illuminationManager;

public:
    explicit BrightnessViewModel(QObject *parent = 0);
    void associateManager(IIlluminationManager *illuminationManager);
    int brightness() const;

signals:
    void brightnessChanged(int arg);

public slots:
    void setBrightness(int value);

};

}

#endif // BRIGHTNESSVIEWMODEL_H
