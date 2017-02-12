#ifndef PASSENGERCONTROLLER_H
#define PASSENGERCONTROLLER_H

#include <QObject>
#include "Controller.h"

class PassengerController : public Controller
{
    Q_OBJECT
public:
    /*
     * regiester passenger info
     */
    QJsonObject regiester();

    /*
     * passenger login
     */
    QJsonObject login();

    /*
     * 获取passenger基本信息（给driver看）
     * 获取passenger详细信息（给passenger客户端看）
     */
    QJsonObject getUserInfo();
};

#endif // PASSENGERCONTROLLER_H
