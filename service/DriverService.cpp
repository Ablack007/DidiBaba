#include "DriverService.h"
#include <QSqlError>
#include <QVector>
#include <QSqlTableModel>
#include "model/Driver.h"


bool DriverService::regiester(QString &username,QString &password, QString phone , QString plate){

    if(username.isEmpty() || password.isEmpty() || phone.isEmpty() || plate.isEmpty()){
        this->setErrorText("not enough arguments");
        return false;
    }

    QString sql = QString("insert into driver (username, password ,phone ,plate) values ('%1', '%2' , '%3' ,'%4')")
            .arg(username, password,phone , plate);

    Driver driver;
    QSqlQuery query = driver.getMysqlDatabase().exec(sql);
    QSqlError error = query.lastError();

    if(error.type() != QSqlError::NoError)
    {
        this->setErrorText(error.text());
        return false;
    }

    return true;
}

Driver DriverService::login(QString &username, QString &password){

    //verify user
    int did = verify(username,password);
    if(did == 0){
        Driver driver;
        driver.did = 0;
        return driver;
    }

    Driver d;
    Driver driver = d.getById(did);
    if(driver.did == 0){
        return driver;
    }

    //add user info to redis
    driver.insertToRedis();

    return driver;
}

int DriverService::verify(QString &username,QString &password){

    if(username.isEmpty() || password.isEmpty() ){
        this->setErrorText("not enough arguments");
        return 0;
    }

    QString sql = QString("select id from driver where username = '" + username + "' and password = '" + password + "';" );

    Driver driver;
    QSqlQuery query = driver.getMysqlDatabase().exec(sql);
    QSqlError error = query.lastError();

    if(error.type() != QSqlError::NoError){
        this->setErrorText("verify:" + error.text());
        return 0;
    }

    int did;
    if(query.next()){
        did = query.value("id").toInt();
    }
    else{
        this->setErrorText("verify : no this driver");
        return 0;
    }
    return did;
}


bool DriverService::updateDriverStatus(int did, int status){
    Driver d;
    Driver driver = d.getById(did);
    if(driver.did == 0){
        return false;
    }

    driver.status = status;
    if(!driver.updateToRedis()){
        return false;
    }
    return true;
}

bool DriverService::updateLocation(int did , double lng ,double lat){
    return true;
}

QVector<Driver> DriverService::getNearbyDrivers(double lng ,double lat){
    QVector<Driver> drivers;
    return drivers;
}

