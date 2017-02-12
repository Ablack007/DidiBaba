#include "HCServer.h"

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include "controller/DriverController.h"
#include "controller/PassengerController.h"
#include <QDebug>

HCServer::HCServer(QObject *parent) : QObject(parent)
{
    qDebug() << "server start ....";
    httpServer = new HttpServer();
    connect(httpServer,&HttpServer::requestReady,this,&HCServer::slotRequestReady);
    httpServer->listen(QHostAddress::Any,HC_SERVER_PORT);

}

HCServer::~HCServer(){

    delete httpServer;
}

void HCServer::slotRequestReady(Tufao::HttpServerRequest &request,Tufao::HttpServerResponse &response){

    //当收到请求结束信号时
    connect(&request,&HttpServerRequest::end,[&](){

        QByteArray requestBody = request.readBody();
        QByteArray responseBody = handleRequest(requestBody);

        response.writeHead(HttpResponseStatus::OK);
        response.end(responseBody);



    });
}


QJsonObject HCServer::unkownCMD(){

    QJsonObject respObj;

    respObj.insert("cmd",QJsonValue("unkown_cmd"));
    respObj.insert("code",QJsonValue(false));
    respObj.insert("msg",QJsonValue("bad request"));
    respObj.insert("result",QJsonValue(""));

    return respObj;
}


/**
 * 处理客户端发来的请求报文。期望客户端发来的是JSON格式报文
 * 分发路由
 */
QByteArray HCServer::handleRequest(QByteArray &requestBody){

    QJsonObject jsonResp;
    //解析requestBody
    QJsonDocument reqDoc = QJsonDocument::fromJson(requestBody);
    if(reqDoc.isNull()){
        jsonResp = unkownCMD();
        return QJsonDocument(jsonResp).toJson();
    }

    //将QJsonDocument转为QJsonObject
    QJsonObject jsonReq = reqDoc.object();
    //提取cmd

    Controller controller;
    controller.handleJsonRequest(jsonReq,jsonResp);

    return QJsonDocument(jsonResp).toJson();
}
