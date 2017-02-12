#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "Global.h"

#include <hiredis/hiredis.h>

class Model : public QObject
{
    Q_OBJECT
public:
    static QSqlDatabase getMysqlDatabase();

    static redisContext* getRedisDatabase();

};

#endif // MODEL_H
