#include "daysimulator.h"
#include "stateexchanger.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<DaySimulator>("com.bbv.StreetLightSimulator", 1, 0, "DaySimulator");

    StateExchanger stateexchanger;
    if(!stateexchanger.initialize())
        qWarning() << "Could not initialize D-Bus connection";

    engine.rootContext()->setContextProperty("cppBrightness", stateexchanger.brightness().get());
    engine.rootContext()->setContextProperty("cppLuminosity", stateexchanger.luminosity().get());


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
