TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt
QT += quick
QT += widgets
QT += testlib qml
CONFIG   += C++14

INCLUDEPATH += ../test/ \
    ../App/

SOURCES += \
 ../App/daysimulator.cpp \
    daysimulator_test.cpp \
    Main_TestAll.cpp

HEADERS += \
../App/daysimulator.h


#include(deployment.pri)
#qtcAddDeployment()


LIBS += -lgtest -pthread -lgtest_main -lgcov --coverage
