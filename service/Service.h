#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>

class Service : public QObject
{
    Q_OBJECT

private:
    QString errorText;

public:
    QString getErrorText();
    void setErrorText(QString errorText);
};

#endif // SERVICE_H
