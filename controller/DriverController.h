#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include <QJsonObject>
#include "Controller.h"


class DriverController : public Controller
{
    Q_OBJECT

public:
    /*
     * regiester driver info
     *
     * cmd:
     *  HC_CMD_D_REG
     *
     * request:
     *  "username":"xxx"
     *  "password":"xxx"
     *  "phone":"xxx"
     *  "plate":"xxx"  car number
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     */
    void regiester(QJsonObject &jsonReq , QJsonObject &jsonResp);

    /*
     * driver login
     *
     * cmd:
     *  HC_CMD_D_LOGIN
     *
     * request:
     *  "username":"xxx"
     *  "password":"xxx"
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     *  "did":11        driver id
     *  "username":"xxx"
     *  "phone":"xxx"
     */
    void login(QJsonObject &jsonReq , QJsonObject &jsonResp);

    /*
     * update driver's location while driver is activate.
     *
     * cmd:
     *  HC_CMD_D_UPDATELOCATION
     *
     * argument:
     *  "did":11
     *  "lng":"xxx"     driver longitude
     *  "lat":"xxx"     driver latitude
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     */
    void updateLocation(QJsonObject &jsonReq , QJsonObject &jsonResp);

    /*
     * 获取指定范围内所有司机基本信息
     *
     * cmd:
     *  HC_CMD_NEARBYDRIVERS
     *
     * argument:
     *  "lng":"xxx"     passenger longitude
     *  "lat":"xxx"     passenger latitude
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     *  "drivers":
     *      "lng":"xxx","lat":"xxx"
     *      "lng":"xxx","lat":"xxx"
     *      "lng":"xxx","lat":"xxx"
     *
     */
    void getNearbyDrivers(QJsonObject &jsonReq , QJsonObject &jsonResp);

    /*
     * 设置司机可接单 or rest
     *
     * cmd:
     *  HC_CMD_D_UPDATESTATUS
     *
     * argument:
     *  "did":11
     *  "status":HC_DS_ACCEPTABLE/HC_DS_REST
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     */
    void setActivate(QJsonObject &jsonReq , QJsonObject &jsonResp);

    /*
     * 获取司机基本信息（给乘客看）
     * 获取司机详细信息（给司机客户端看）
     *
     * cmd:
     *  HC_CMD_D_INFO
     *
     * argument:
     *  "did":11
     *
     * response:
     *  "code":HC_SUCCESS/HC_ERROR
     *  "reason":"xxx"
     *  "info":
     *      "did":11
     *      "username":"xxx"
     *      "phone":"xxx"
     *      "plate":"xxx"
     */
    void getUserInfo(QJsonObject &jsonReq , QJsonObject &jsonResp);

};

#endif // DRIVERCONTROLLER_H
