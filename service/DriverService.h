#ifndef DRIVERSERVICE_H
#define DRIVERSERVICE_H

#include <QString>
#include <model/Driver.h>
#include <service/Service.h>

class DriverService :public Service
{

public:
    /*
     * regiester driver info
     */
    bool regiester(QString &username,QString &password, QString phone , QString plate);

    /*
     * driver login
     */
    Driver login(QString &username,QString &password);

    /*
     * verify if is valid driver
     */
    int verify(QString &username,QString &password);


    /*
     * update driver status
     */
    bool updateDriverStatus(int did, int status);

    /*
     * update current driver location info
     */
    bool updateLocation(int did , double lng ,double lat);


    /*
     * 获取指定范围内所有司机基本信息
     */
    QVector<Driver> getNearbyDrivers(double lng ,double lat);

};

#endif // DRIVERSERVICE_H
