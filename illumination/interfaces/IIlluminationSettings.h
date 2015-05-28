#ifndef IILLUMINATIONSETTINGS_H
#define IILLUMINATIONSETTINGS_H

class IIlluminationSettings
{
public:
    IIlluminationSettings();
    virtual double getIlluminationValue() = 0;
    virtual void storeIlluminationValue(double value) = 0;
};

#endif // IILLUMINATIONSETTINGS_H
