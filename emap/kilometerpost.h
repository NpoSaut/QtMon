#ifndef KILOMETERPOST_H
#define KILOMETERPOST_H

#include <map>

#include <QByteArray>


#include "almanac.h"
#include "rail.h"

namespace Navigation
{

enum KilometerPostPosition { kpp_start = 1, kpp_middle = 0, kpp_end = 2 };
enum KilometerIncreaseDirectoin { kid_increase = 1, kid_decrease = -1 };

class KilometerPost
{
public:
    KilometerPost();

    static KilometerPost *loadFrom(const QByteArray& data, int offset, int index);

    double lat;
    double lon;
    double ordinate;
    int sectionId;
    KilometerPostPosition position;
    KilometerIncreaseDirectoin direction;
    std::map<int, Rail *> rails;

    double distanceTo(double to_lat, double to_lon);
    double estimateDistanceTo(KilometerPost p2);
    double estimateDistanceTo(double to_lat, double to_lon);

    static double distanceBetween(double lat1, double lon1, double lat2, double lon2);
    static double distanceBetween(KilometerPost p1, KilometerPost p2);
    static double estimateDistances(KilometerPost p1, KilometerPost p2);
    static double estimateDistances(double lat1, double lon1, double lat2, double lon2);
    static double metersToEstimation(double meters);
    static double radian(double gradus);

    inline bool operator == (const KilometerPost &p)    { return id == p.id; }
    inline bool operator != (const KilometerPost &p)    { return !(*this == p); }

private:
    int id;
};

}

#endif // KILOMETERPOST_H
