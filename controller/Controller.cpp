#include "Controller.h"
#include "Global.h"

#include "DriverController.h"
#include "PassengerController.h"


#define CONN_CMD_HANDLER(cmd,classname,handler) \
    case cmd:\
    { \
        classname contoller; \
        contoller.handler(jsonReq,jsonResp); \
        break; \
    }

//处理客户端发来的请求
void Controller::handleJsonRequest(QJsonObject &jsonReq , QJsonObject &jsonResp){

    qint32 cmd = jsonReq.value("cmd").toInt();

    switch (cmd) {
        CONN_CMD_HANDLER(HC_CMD_D_REG,DriverController,regiester);
        CONN_CMD_HANDLER(HC_CMD_D_LOGIN,DriverController,login);
    default:
        //jsonResp.insert("code",QJsonValue(false));
        //jsonResp.insert("result",QJsonValue("bad request"));
        qDebug() << "bad request...";
        break;
    }
}
