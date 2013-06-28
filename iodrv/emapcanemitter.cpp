#if defined WITH_CAN

#include "lowlevel.h"
#include "emapcanemitter.h"

#include <QDebug>

using namespace std;
using namespace Navigation;

EMapCanEmitter::EMapCanEmitter(QObject *parent) :
    QObject(parent),
    timer(parent), // Частота выдача в can объекта. Должна быть 100 мс, но из-за проблем со временем 50 -TiME-
    sendingObjects(), receivedObjects(),
    step (0), targetNumber(0), targetDistance(0)
{
    timer.setInterval (50);
    timer.start ();
    QObject::connect (&timer, SIGNAL(timeout()), this, SLOT(engine()));

    // Получение данных о текущей цели из ЦО
    QObject::connect (&canDev, SIGNAL(receiveNewMessage(CanFrame)), this, SLOT(getTargetDistanceFromMcoState(CanFrame)));
    QObject::connect (&canDev, SIGNAL(receiveNewMessage(CanFrame)), this, SLOT(getTargetNumberFromMcoLimits(CanFrame)));
}

EMapCanEmitter::CanMessageData EMapCanEmitter::encodeEMapTarget(const EMapTarget& t, int targetNumber)
{
    CanMessageData canMessage;

    canMessage.errors = 0;
    canMessage.number = targetNumber;
    canMessage.type = t.object->getType ();
    canMessage.xLow = t.x & 0xFF;
    canMessage.xHight = t.x >> 8;
    canMessage.radioChanel = t.object->isRadioChannel ();
    canMessage.station = 0; // ??? Откуда взять
    canMessage.alsEn = t.object->isAlsEn ();
    canMessage.lengthLowByte = char (t.object->getLength ());
    canMessage.lengthHighByte = char (t.object->getLength ()>> 8);
    canMessage.alsnFreqCode = t.object->getAlsnFreq ();
    canMessage.alsEnNewTable = 0; // ??? Откуда взять
    canMessage.pullforthForFreightTrain =  t.object->isPullforthForFreightTrain ();
    canMessage.pullforthForPassengerTrain = t.object->isPullforthForPassengerTrain ();
    canMessage.conditionallyAllow = t.object->isConditionallyAllowForFreightTrain ();
    canMessage.targetSpeed = char (t.object->getSpeedRestriction ());
    canMessage.targetSpeedHightBit = char (t.object->getSpeedRestriction ()>> 8);

    return canMessage;
}

void EMapCanEmitter::engine()
{
    CanFrame canFrame (0x43E8, std::vector<unsigned char>(8)); // MM_STATE
    if (step < sendingObjects.size ())
    {
        CanMessageData canMessage = encodeEMapTarget(sendingObjects[step], step);
        canFrame.setData (std::vector<unsigned char>((unsigned char *)(&canMessage), (unsigned char *)(&canMessage) + 8) );
    }
    else
    {
        std::vector<unsigned char> data (8);
        data[0] = 0;
        data[1] = step; // Пустой объект
        canFrame.setData (data);
    }
    canDev.transmitMessage (canFrame);

    if (++step == 10)
    {
        step = 0;

//        // Вывод названия ближайщей цели
//        if ( targetNumber < sendingObjects.size () )
//            canDev.transmitMessage (
//                        CanFrame (0xC068,
//                                  std::vector<unsigned char> ( sendingObjects[targetNumber].object->getName().toAscii().data(),
//                                                               sendingObjects[targetNumber].object->getName().toAscii().data() + 8) )
//                                     );

        // Обновление списка целей
        mutex.lock ();
        sendingObjects = receivedObjects;
        mutex.unlock ();
    }
}

void EMapCanEmitter::getTargetDistanceFromMcoState(CanFrame canFrame)
{
    if ( canFrame.getDescriptor () == 0x0A08 )
    {
        unsigned newTargetDistance = (unsigned(canFrame.getData ()[3] & 0x1F) << 8) + canFrame.getData ()[4];
        if ( newTargetDistance != targetDistance )
        {
            targetDistance = newTargetDistance;
            emit targetDistanceChanged (targetDistance);
        }
    }
}

void EMapCanEmitter::getTargetNumberFromMcoLimits(CanFrame canFrame)
{
    if ( canFrame.getDescriptor () == 0x048 )
    {
        unsigned newTargetNumber = canFrame.getData ()[6] >> 4;
        if ( newTargetNumber != targetNumber )
        {
            targetNumber = newTargetNumber;
            if ( targetNumber < sendingObjects.size () )
            {
                emit targetNameChanged (sendingObjects[targetNumber].object->getName());
                emit targetTypeChanged (sendingObjects[targetNumber].object->getType());
            }
            else
            {
                emit targetNameChanged ("");
                emit targetTypeChanged (0);
            }
        }
    }
}

void EMapCanEmitter::setObjectsList(const vector<EMapTarget> objects)
{
    receivedObjects = objects;
}

void EMapCanEmitter::setOrdinate(int ordinate)
{
    canDev.transmitMessage (
                CanFrame (0xC0A3, // MM_COORD
                          ByteArray<3> (ordinate).msbFirst() )
                            );
}

#endif
