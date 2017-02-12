#include "Driver.h"

#include <QSqlQuery>
#include <QSqlError>
#include "Util.h"
#include <hiredis/hiredis.h>
#include <QDateTime>

Driver::Driver(Driver && driver){
    did  = driver.did;
    username = driver.username;
    password = driver.password;
    phone = driver.phone;
    plate = driver.plate;


    status = driver.status;
    lng = driver.lng;
    lat = driver.lat;
}

Driver::Driver(){

}

QByteArray Driver::getGeohash(){
    return Util::getGeohash(lat, lng);
}

Driver Driver::getById(int did){
    //get from redies


    //get from mysql
    QString sql = QString("select * from driver where id = " + QString::number(did,10) +" ; ");

    Driver driver;
    driver.did = 0;
    QSqlQuery query = driver.getMysqlDatabase().exec(sql);
    QSqlError error = query.lastError();

    if(error.type() != QSqlError::NoError){
        driver.did = 0;
        return driver;
    }

    if(query.next()){
        driver.did = did;
        driver.username = query.value("username").toString();
        driver.phone = query.value("phone").toString();
        driver.plate = query.value("plate").toString();
    }

    return driver;
}


bool Driver::insertToRedis(){
    QString comm = "hmset driver_" + QString::number(did,10)
            +" username " + this->username
            +" phone " + this->phone
            +" plate " + this->plate
            +" status " + this->status;
    QByteArray ba = comm.toLatin1();

    redisReply* r = (redisReply*)redisCommand(getRedisDatabase(), ba.data());

    if( NULL == r)
    {
        return false;
    }
    if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0))
    {
        freeReplyObject(r);
        return false;
    }
    freeReplyObject(r);

    return true;
}

bool Driver::updateToRedis(){
    QString did = QString::number(this->did,10);
    QByteArray ba;
    QString comm;
    redisReply* r;

    //get old value
    comm = "HMGET driver_" + did + "geohash";
    ba = comm.toLatin1();
    r = (redisReply*)redisCommand(getRedisDatabase(), ba.data());
    if(r->type != REDIS_REPLY_STRING){
        freeReplyObject(r);
        return false;
    }
    QString oldGeo(r->str);
    freeReplyObject(r);

    //geohash set
    //if driver.geohash not in geohash driver.geohash set   then   delete old set value   and  add new set value
    if(oldGeo != this->getGeohash()){
        comm = "SMOVE " + oldGeo + " " + this->getGeohash();
        ba = comm.toLatin1();
        r = (redisReply*)redisCommand(getRedisDatabase(), ba.data());
        if(!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)){
            freeReplyObject(r);
            return false;
        }
        freeReplyObject(r);
    }

    //driver_* hset
    qint64 currTime = QDateTime::currentMSecsSinceEpoch();

    comm = "hmset driver_" + did
            +" geohash " + this->getGeohash()
            +" lng " + this->lng
            +" lat " + this->lat;
            +" update_at " + currTime;

    ba = comm.toLatin1();
    r = (redisReply*)redisCommand(getRedisDatabase(), ba.data());

    if( NULL == r){
        return false;
    }
    if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)){
        freeReplyObject(r);
        return false;
    }
    freeReplyObject(r);

    return true;
}

QVector<int> Driver::getAllDriversIdFromRedis(){
    QVector<int> vector;

    QByteArray ba;
    QString comm;
    redisReply* r;

    comm = "KEYS gh_*";
    ba = comm.toLatin1();
    r = (redisReply*)redisCommand(getRedisDatabase(), ba.data());
    if(r->type != REDIS_REPLY_ARRAY){
        freeReplyObject(r);
        return vector;
    }
    for(int i = 0 ; i < r->elements; i++){
        redisReply * tmp = r->element[i];
        redisReply* tmpr;

        comm = "SMEMBERS " + QString(tmp->str);
        ba = comm.toLatin1();
        tmpr = (redisReply*)redisCommand(getRedisDatabase(), ba.data());
        for(int j = 0 ; j < tmpr->elements; j++){
            redisReply * tmp2 = tmpr->element[j];
            vector.push_back(QString(tmp2->str).toInt());
        }

        freeReplyObject(tmpr);
        freeReplyObject(tmp);
    }

    return vector;
}
