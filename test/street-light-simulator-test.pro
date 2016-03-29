TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt
CONFIG += coverage
QT += quick
QT += widgets
QT += testlib qml
CONFIG += c++14

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0
QMAKE_LFLAGS += -fprofile-arcs -ftest-coverage -O0 -lgcov --coverage

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
