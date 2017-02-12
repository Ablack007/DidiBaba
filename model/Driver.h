#ifndef DRIVER_H
#define DRIVER_H

#include "Model.h"



class Driver : public Model
{
public:
    //driver status
    enum DRIVER_STATUS{
        DS_ACCEPTABLE = 1,      //driver is ready to working (default after trans)
        DS_WORKING = 3,         //driver has accept order

        DS_REST = 10,           //driver is resting (default after login or logout)
        DS_FREEZE = 11,         //driver was frozen by system
    };

    //base info
    int did;
    QString username;
    QString password;
    QString phone;
    QString plate;  //che pai hao ma

    //dynamic info
    int status;
    double lng;     //jing du
    double lat;     //wei du


public:
    Driver(Driver&&);
    Driver();

    QByteArray getGeohash();
    Driver getById(int did);

    bool insertToRedis();

    //update per 2 second
    bool updateToRedis();
    bool deleteFromRedis(int did);

    QVector<int> getAllDriversIdFromRedis();
};

#endif // DRIVER_H
