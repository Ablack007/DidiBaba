#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>


/*******************
 *
 * server config
 *
 *******************/

#define HC_SERVER_PORT              9090        //服务器监听端口


/***********************
 *
 * database  config
 *
 **********************/

//#define HC_DB_TYPE                  "QMYSQL"        //数据库连接类型 @http://doc.qt.io/qt-5/sql-driver.html
//#define HC_DB_NAME                  "hcar"        //数据库名
//#define HC_DB_DRIVER                "/home/xueguoliang/Qt5.7.0/5.7/gcc_64/plugins/sqldrivers/libqsqlmysql.so"

#define HC_DB_TYPE                  "QSQLITE"        //数据库连接类型 @http://doc.qt.io/qt-5/sql-driver.html
#define HC_DB_NAME                  "/home/xueguoliang/sqlite/hcar.db"        //数据库名

#define HC_DB_HOST                  "localhost"     //数据库服务器
#define HC_DB_USER                  "root"          //数据库用户名
#define HC_DB_PASS                  "root"          //数据库密码
#define HC_DB_PORT                  3306            //数据库端口

#define HC_DB_REDIS_HOST            "localhost"
#define HC_DB_REDIS_PORT            6379

/**********************
 *
 * haha
 *
 **********************/



//passenger status...


/********************
 *
 * jiaohu
 *
 ********************/
#define HC_ERROR                    "error"     //error code
#define HC_SUCCESS                  "ok"        //success code

//100+n 司机请求命令 D is Driver
#define HC_CMD_D_LOGIN              100         //司机 登录
#define HC_CMD_D_REG                101         //司机 注册
#define HC_CMD_D_UPDATELOCATION     102         //司机 更新定位
#define HC_CMD_D_UPDATESTATUS       103         //司机 update status
#define HC_CMD_D_INFO               104         //get driver information

#define HC_CMD_D_ACCEPTORDER        110         //司机 接单
#define HC_CMD_D_REJECTORDER        111         //司机 拒单
#define HC_CMD_D_START              112         //司机 开始行程
#define HC_CMD_D_END                113         //司机 结束行程

#define HC_CMD_NEARBYDRIVERS        120         //get nearby drivers

//200+n 乘客请求命令  P is passenger
#define HC_CMD_P_LOGIN              200         //乘客 登录
#define HC_CMD_P_REG                201         //乘客 注册
#define HC_CMD_P_UPDATELOCATION     202         //乘客 更新定位
#define HC_CMD_P_CALL               203         //乘客 约车
#define HC_CMD_P_CANCEL             204         //乘客 取消约车
#define HC_CMD_P_PAY                205         //乘客 付钱


#endif // GLOBAL_H
