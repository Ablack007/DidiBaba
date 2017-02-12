#include "testdriver.h"

#include "Global.h"
#include "controller/DriverController.h"

TestDriver::TestDriver()
{
    //testRegiesterDriver();
    //testLogin();
    testGetNearbyDrivers();
}


void TestDriver::testRegiesterDriver(){
    qDebug() << "TestDriver::TestRegiesterDriver:";


    QJsonObject req , res;
    req.insert("cmd",HC_CMD_D_REG);
    req.insert("username","driver3");
    req.insert("password", "123456");
    req.insert("phone", "110");
    req.insert("plate","SB120");

    Controller controller;
    controller.handleJsonRequest(req,res);

    qDebug() << "code:" << res.value("code").toString();
    qDebug() << "result:" << res.value("result").toString();
}


void TestDriver::testLogin(){
    qDebug() << "TestDriver::testLogin:";

    QJsonObject req , res;
    req.insert("cmd",HC_CMD_D_LOGIN);
    req.insert("username","driver3");
    req.insert("password", "123456");

    Controller controller;
    controller.handleJsonRequest(req,res);

    qDebug() << "code:" << res.value("code").toString();
    qDebug() << "result:" << res.value("result").toString();

    qDebug() << "did:" << res.value("did").toInt();
    qDebug() << "username:" << res.value("username").toString();
    qDebug() << "phone:" << res.value("phone").toString();
    qDebug() << "plate:" << res.value("plate").toString();

}


void TestDriver::testUpdateCurrentStatus(){

}

#include "model/Driver.h"
void TestDriver::testGetNearbyDrivers(){
    Driver driver;
    QVector<int> v = driver.getAllDriversIdFromRedis();

    qDebug() <<"driver ids";
    for(int i = 0 ; i < v.size() ; i++){
        qDebug() << v.at(i);
    }
}


void TestDriver::testSetActivate(){

}


void TestDriver::testGetUserInfo(){

}
