#ifndef CONFIGURECONTEXT_H
#define CONFIGURECONTEXT_H

class ConfigureContext : public Context
{
public:
    ConfigureContext();
    int trainCategory;
    int summerTime;
    int locomotiveKind;
    int locomotiveNumber;
    int diameter1;
    int diameter2;
    int impulsesPerCycle;
    int configuration;
    int speedWhite;
    int speedGreen;
    int speedYellow;
    int sectionLength;
};

#endif // CONFIGURECONTEXT_H
