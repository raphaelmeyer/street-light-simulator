#include "daysimulator.h"
#include "stateexchanger.h"
#include "rainsimulator.h"

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

    RainSimulator rainSimulator;
    DaySimulator daySimulator;
    std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();


    rainSimulator.setTimer(timer);
    daySimulator.setTimer(timer);
    //connect(timer, SIGNAL(timeout()), )

    engine.rootContext()->setContextProperty("cppBrightness", stateexchanger.brightness().get());
    engine.rootContext()->setContextProperty("cppLuminosity", stateexchanger.luminosity().get());
    engine.rootContext()->setContextProperty("cppMoisture", stateexchanger.moisture().get());
    engine.rootContext()->setContextProperty("cppWarning", stateexchanger.warning().get());
    engine.rootContext()->setContextProperty("cppRain", &rainSimulator);
    engine.rootContext()->setContextProperty("cppDay", &daySimulator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* world = engine.rootObjects().first()->findChild<QObject*>(QString("world"));
    if(world!=nullptr)
        QObject::connect(timer.get(),SIGNAL(timeout()), world, SLOT(calculateCelestialPositions()));
    else
        qDebug() << "Couldn't find gui";

    return app.exec();
}
