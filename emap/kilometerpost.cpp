#include "kilometerpost.h"

#include "math.h"

#define MATH_PI 3.1415926535897932384626433832795
#define EARTH_RADIUS 6371000

// Представление километрового столба
KilometerPost::KilometerPost()
{
}

double KilometerPost::distanceTo(double to_lat, double to_lon)
{
    return distanceBetween(lat, lon, to_lat, to_lon);
}

double KilometerPost::estimateDistanceTo(KilometerPost p2)
{
    return estimateDistanceTo(p2.lat, p2.lon);
}

double KilometerPost::estimateDistanceTo(double to_lat, double to_lon)
{
    return estimateDistances(lat, lon, to_lat, to_lon);
}

double KilometerPost::radian(double gradus)
{
    return gradus * MATH_PI / 180;
}

// Структура, описывающая формат хранение электронного столба
struct GreenPost
{
    unsigned int ordinate            :8*3;
    unsigned int position            :2;
    unsigned int alsnFreq            :4;
    unsigned int                     :1;
    unsigned int ordinateDirection   :1;
    unsigned int latitudeCode        :8*4;
    unsigned int longitudeCode       :8*4;
    unsigned int trackAddress        :8*3;
};
const int GreenPostSize = 15;

KilometerPost KilometerPost::loadFrom(const QByteArray& data, int offset, int index)
{
    GreenPost gpost;
    for (int i = 0; i < GreenPostSize; i ++)
    {
        *((char *) &gpost + i) = *(data.data () + offset + GreenPostSize * index + i);
    }

    KilometerPost kp;
    kp.id = index;
    kp.ordinate = gpost.ordinate;
    kp.lat = gpost.latitudeCode  * 10e-9 * 180 / MATH_PI;
    kp.lon = gpost.longitudeCode * 10e-9 * 180 / MATH_PI;
    *((int *) &kp.position) = gpost.position;
    kp.direction = gpost.ordinateDirection == 0 ? kid_increase : kid_decrease;
    kp.position = kp.position;

    return kp;
}


double KilometerPost::distanceBetween(KilometerPost p1, KilometerPost p2)
{
    return distanceBetween(p1.lat, p1.lon, p2.lat, p2.lon);
}
double KilometerPost::distanceBetween(double lat1, double lon1, double lat2, double lon2)
{
    return EARTH_RADIUS * 2 * asin(pow(estimateDistances(lat1, lon1, lat2, lon2), 0.5));
}


double KilometerPost::estimateDistances(KilometerPost p1, KilometerPost p2)
{
    return estimateDistances(p1.lat, p1.lon, p2.lat, p2.lon);
}

double KilometerPost::estimateDistances(double lat1, double lon1, double lat2, double lon2)
{
    return pow(sin(radian(lat2 - lat1) / 2), 2) + cos(radian(lat1)) * cos(radian(lat2)) * pow(sin(radian(lon2 - lon1) / 2), 2);
}

double KilometerPost::metersToEstimation(double meters)
{
    return sin(pow(meters / (2 * EARTH_RADIUS), 2));
}
