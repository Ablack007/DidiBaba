#ifndef UTIL_H
#define UTIL_H
#include <QByteArray>


class Util
{

public:
    static QByteArray getGeohash(double lng, double lat, int bits = 20);

private:

    static char* getGeohash(double lng, double lat, char *buf, int bits);
};

#endif // UTIL_H
