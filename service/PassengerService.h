#ifndef PASSENGERSERVICE_H
#define PASSENGERSERVICE_H

#include <QObject>
#include <service/Service.h>

class PassengerService : public Service
{
    Q_OBJECT
public:

    /*
     * regiester passenger info
     */
    bool regiester(QString &username,QString &password);

    /*
     * passenger login
     */
    bool login(QString &username,QString &password);


    /*
     * 获取passenger基本信息（给driver看）
     * 获取passenger详细信息（给passenger客户端看）
     */
    bool getUserInfo();

};

#endif // PASSENGERSERVICE_H
