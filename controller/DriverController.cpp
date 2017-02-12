#include "controller/DriverController.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>
#include <QDebug>

#include "Global.h"
#include "service/DriverService.h"
#include "model/Driver.h"


void DriverController::regiester(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    QString username = jsonReq.value("username").toString();
    QString password = jsonReq.value("password").toString();
    QString phone = jsonReq.value("phone").toString();
    QString plate = jsonReq.value("plate").toString();

    // change password to MD5 128bit = 16bytes
    QByteArray bb;
    bb = QCryptographicHash::hash (password.toUtf8(), QCryptographicHash::Md5 );
    QString passwordMd5 = bb.toHex(); // md5 is 32bytes

    //call service
    DriverService service;

    if(!service.regiester(username,passwordMd5,phone,plate)){
        jsonResp.insert("code", QString(HC_ERROR));
        jsonResp.insert("result",service.getErrorText());
        return;
    }

    jsonResp.insert("code", QString(HC_SUCCESS));
}


void DriverController::login(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    QString username = jsonReq.value("username").toString();
    QString password = jsonReq.value("password").toString();

    // change password to MD5 128bit = 16bytes
    QByteArray bb;
    bb = QCryptographicHash::hash (password.toUtf8(), QCryptographicHash::Md5 );
    QString passwordMd5 = bb.toHex(); // md5 is 32bytes

    //call service
    DriverService service;

    Driver driver = service.login(username,passwordMd5);
    if(driver.did == 0){
        jsonResp.insert("code", QString(HC_ERROR));
        jsonResp.insert("result",service.getErrorText());
        return;
    }

    //
    jsonResp.insert("code", HC_SUCCESS);
    jsonResp.insert("did", driver.did);
    jsonResp.insert("username",driver.username);
    jsonResp.insert("phone",driver.phone);
    jsonResp.insert("plate",driver.plate);
}

void DriverController::updateLocation(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    int did = jsonReq.value("did").toInt();
    double lng = jsonReq.value("lng").toDouble();
    double lat = jsonReq.value("lat").toDouble();

    //call service
    DriverService service;

    if(!service.updateLocation(did,lng,lat)){
        jsonResp.insert("code", QString(HC_ERROR));
        return;
    }

    jsonResp.insert("code", QString(HC_SUCCESS));
}

void DriverController::getNearbyDrivers(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    double lng = jsonReq.value("lng").toDouble();
    double lat = jsonReq.value("lat").toDouble();

    //call service
    DriverService service;

    QVector<Driver> drivers = service.getNearbyDrivers(lng,lat);

    QJsonArray array;
    for(int i = 0 ; i < drivers.size(); ++i){
        QJsonObject obj;
        obj.insert("lng",drivers.at(i).lng);
        obj.insert("lat",drivers.at(i).lat);
        array.push_back(obj);
    }
    jsonResp.insert("drivers",array);
    jsonResp.insert("code", QString(HC_SUCCESS));
}

void DriverController::setActivate(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    int did = jsonReq.value("did").toInt();
    int status = jsonReq.value("status").toInt();

    //call service
    DriverService service;
    if(!service.updateDriverStatus(did,status)){
        jsonResp.insert("code", QString(HC_ERROR));
        return;
    }

    jsonResp.insert("code", QString(HC_SUCCESS));
}

void DriverController::getUserInfo(QJsonObject &jsonReq , QJsonObject &jsonResp){

    //get argument from json object
    int did = jsonReq.value("did").toInt();

    Driver d;
    Driver driver = d.getById(did);
    if(driver.did == 0){
        jsonResp.insert(QString(HC_CMD_D_REG), QString(HC_ERROR));
        return;
    }

    jsonResp.insert("code", HC_SUCCESS);
    jsonResp.insert("did", driver.did);
    jsonResp.insert("username",driver.username);
    jsonResp.insert("phone",driver.phone);
    jsonResp.insert("plate",driver.plate);
}
