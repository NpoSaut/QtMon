#include "rail.h"

using namespace Navigation;

Rail *Rail::loadFrom(QByteArray rawData, int offset, int index)
{
    Rail *rail = new Rail();
    RawRailData data = *((RawRailData *) (rawData.data () + offset + index * RawRailDataSize));
    rail->number = data.number;

    if (rail->number > 0 && data.childObjectsAddress != 0xffffff) // признак существования пути
    {
        for (int i = 0; i < data.childObjectsCount; i ++)
        {
            RailObject *object = RailObject::loadFrom (rawData, data.childObjectsAddress, i);
            object->setParentRoad (rail);
            rail->objects.push_back (object);
        }
        rail->existence = true;
    }

    rail->direction = getDirectoin(rail->number);

    return rail;
}

KilometerIncreaseDirectoin Rail::getDirectoin(int railNumber)
{
    return (KilometerIncreaseDirectoin)( (railNumber % 2 == 0 ? -1 : 1) * (railNumber < 16 ? 1 : -1) );
}
