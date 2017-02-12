#include <QCoreApplication>
#include "QDebug"

#include "HCServer.h"

/*
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    HCServer* hcServer = new HCServer();
    if(hcServer){
        qDebug() << "服务器已启动.监听端口:9090";
    }
    else{
        qDebug() << "服务器 start error";
    }

    return a.exec();
}
*/

#include "test/testdriver.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    TestDriver td;

    return a.exec();
}
