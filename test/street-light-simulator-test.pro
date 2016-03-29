TEMPLATE = app
#CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt
QT += testlib qml
CONFIG   += C++11

INCLUDEPATH += ../test/

SOURCES += \
    daysimulator_test.cpp \
    Main_TestAll.cpp

#include(deployment.pri)
#qtcAddDeployment()


LIBS += -lgtest -pthread -lgtest_main
