#ifndef CANILLUMINATIONSETTER_H
#define CANILLUMINATIONSETTER_H

#include <QObject>
#include "interfaces/IIlluminationManager.h"
#include "qtBlokLib/parser.h"

class CanIlluminationSetter : public QObject
{
    Q_OBJECT
public:
    explicit CanIlluminationSetter(IIlluminationManager *manager, Parser *parser, QObject *parent = 0);

private slots:
    void onIlluminationSet (int value);

private:
    IIlluminationManager *manager;
};

#endif // CANILLUMINATIONSETTER_H
