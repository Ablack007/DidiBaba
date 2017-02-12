#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T17:22:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuduDaChe
TEMPLATE = app

FORMS    +=

#CONFIG += C++11 TUFAO1
LIBS += -ltufao1 -lhiredis -L /usr/local/lib
QT += network

DISTFILES += \
    README.md

HEADERS += \
    controller/Controller.h \
    controller/DriverController.h \
    controller/OrderController.h \
    controller/PassengerController.h \
    model/Driver.h \
    model/Model.h \
    model/Order.h \
    model/Passenger.h \
    service/DriverService.h \
    service/OrderService.h \
    service/PassengerService.h \
    Global.h \
    HCServer.h \
    test/testdriver.h \
    service/Service.h \
    Util.h

SOURCES += \
    controller/Controller.cpp \
    controller/DriverController.cpp \
    controller/OrderController.cpp \
    controller/PassengerController.cpp \
    model/Driver.cpp \
    model/Model.cpp \
    model/Order.cpp \
    model/Passenger.cpp \
    service/DriverService.cpp \
    service/OrderService.cpp \
    service/PassengerService.cpp \
    HCServer.cpp \
    main.cpp \
    test/testdriver.cpp \
    service/Service.cpp \
    Util.cpp
