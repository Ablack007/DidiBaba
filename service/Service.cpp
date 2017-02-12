#include "Service.h"

QString Service::getErrorText(){
    return this->errorText;
}

void Service::setErrorText(QString errorText){
    this->errorText = errorText;
}
