#ifndef IILLUMINATIONMANAGER_H
#define IILLUMINATIONMANAGER_H

class IIlluminationManager
{
public:
    IIlluminationManager() { }

    virtual double illumination() = 0;
    virtual void setIllumination(double value) = 0;
};

#endif // IILLUMINATIONMANAGER_H
