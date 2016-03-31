#include "daysimulator.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

        qmlRegisterType<DaySimulator>("com.bbv.StreetLightSimulator", 1, 0, "DaySimulator");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
