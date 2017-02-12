#include "Util.h"
#include "stdint.h"
#include <QByteArray>

#define BASE32 "0123456789bcdefghjkmnpqrstuvwxyz"

char* Util::getGeohash(double lng, double lat, char *buf, int bits)
{
    uint64_t lngLatBits = 0;

    double lngMin = -180;
    double lngMax = 180;
    double latMin = -90;
    double latMax = 90;

    for(int i=0; i<bits; ++i)
    {
        lngLatBits<<=1;

        double lngMid = (lngMax + lngMin)/2;
        if(lng > lngMid)
        {
            lngLatBits += 1;
            lngMin = lngMid;
        }
        else
        {
            lngMax = lngMid;
        }

        lngLatBits <<=1;

        double latMid = (latMax + latMin)/2;
        if(lat > latMid)
        {
            lngLatBits += 1;
            latMin = latMid;
        }
        else
        {
            latMax = latMid;
        }
    }

    // 11010 10010 10010 10010 10101 11011 00100 11000
    // a     b     c     1     2     x     2     3    \0
    int i;
    for(i=0;i <8; ++i)
    {
        uint32_t index = lngLatBits >> (35-i*5);
        index &= 31;
        buf[i] = BASE32[index];
    }

    buf[i] = 0;
    return buf;
}


QByteArray Util::getGeohash(double lng, double lat, int bits)
{
    char buf[10]; // 8位的长度经度是偏差是19米，8位长度对应的bits是20，40位整数
    getGeohash(lng, lat, buf, bits);
    return QByteArray(buf);
}
