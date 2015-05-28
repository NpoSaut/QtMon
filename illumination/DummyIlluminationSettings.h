#ifndef DUMMYILLUMINATIONSETTINGS_H
#define DUMMYILLUMINATIONSETTINGS_H

#include "IIlluminationSettings.h"

class DummyIlluminationSettings : public IIlluminationSettings
{
public:
    DummyIlluminationSettings();
    double getIlluminationValue() { return 1.0; }
    void storeIlluminationValue(double value) { }
};

#endif // DUMMYILLUMINATIONSETTINGS_H
