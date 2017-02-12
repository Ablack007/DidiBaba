#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QJsonObject>

class Controller : public QObject
{
    Q_OBJECT
public:

    void handleJsonRequest(QJsonObject& jsonReq,QJsonObject& jsonResp);

protected:

    QJsonObject jsonReq;
    QJsonObject jsonResp;
};

#endif // CONTROLLER_H
