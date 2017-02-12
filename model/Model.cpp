#include "Model.h"
#include "QSqlError"
#include <QPluginLoader>

QSqlDatabase Model::getMysqlDatabase(){

    static int init = 0;
    static QSqlDatabase mysqlDb;

    if(init == 0){
        qDebug() << "init mysql database";

        mysqlDb = QSqlDatabase::addDatabase(HC_DB_TYPE);

        mysqlDb.setHostName(HC_DB_HOST);
        mysqlDb.setPort(HC_DB_PORT);
        mysqlDb.setUserName(HC_DB_USER);
        mysqlDb.setPassword(HC_DB_PASS);
        mysqlDb.setDatabaseName(HC_DB_NAME);
        if(mysqlDb.open()){
            init = 1;
            qDebug() << "db open success";

        }else{
            qDebug() << "error : db open failed:" << mysqlDb.lastError().text();
        }
    }

    return mysqlDb;
}

redisContext* Model::getRedisDatabase(){

    static int init = 0;
    static redisContext* c = NULL;

    if(init == 0){
        qDebug() << "init redis database";
        c= redisConnect(HC_DB_REDIS_HOST,HC_DB_REDIS_PORT);
        if (c->err)
        {
            redisFree(c);
            qDebug() << "Connect to redisServer faile";
            return NULL;
        }
        qDebug() << "Connect to redisServer Success";
        init = 1;
    }
    return c;
}
