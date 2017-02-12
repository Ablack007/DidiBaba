#ifndef HCSERVER_H
#define HCSERVER_H

#include <QObject>

#include <tufao-1/Tufao/HttpServer>
#include <tufao-1/Tufao/HttpServerRequest>
#include <tufao-1/Tufao/HttpServerResponse>

#include "Global.h"

using namespace Tufao;

class HCServer : public QObject
{
    Q_OBJECT
public:
    explicit HCServer(QObject *parent = 0);
    ~HCServer();

signals:

public slots:
    void slotRequestReady(Tufao::HttpServerRequest &request,Tufao::HttpServerResponse &response);

private:
    HttpServer *httpServer = NULL; //服务器实例
    QByteArray handleRequest(QByteArray &);//处理客户端发来的请求

    //未知命令
    QJsonObject unkownCMD();


};

#endif // HCSERVER_H
