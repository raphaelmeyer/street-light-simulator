#include "daysimulator.h"
#include "stateexchanger.h"
#include "rainsimulator.h"
#include "carsimulator.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

static QString getServiceName(const QStringList &arguments)
{
  QCommandLineParser parser;

  parser.addHelpOption();

  const QString defaultServiceName{"ch.bbv.streetlight"};
  QCommandLineOption serviceName{"service", "register with the provided service name instead of " + defaultServiceName, "name", defaultServiceName};
  parser.addOption(serviceName);

  parser.process(arguments);

  return parser.value(serviceName);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    const auto ServiceName = getServiceName(app.arguments());
    QQmlApplicationEngine engine;

    qmlRegisterType<DaySimulator>("com.bbv.StreetLightSimulator", 1, 0, "DaySimulator");

    StateExchanger stateexchanger(ServiceName);
    if(!stateexchanger.initialize())
        qWarning() << "Could not initialize D-Bus connection";

    RainSimulator rainSimulator;
    DaySimulator daySimulator;
    CarSimulator carSimulator;
    std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
    timer->setInterval(1000);
    timer->setSingleShot(false);
    timer->start();
    std::shared_ptr<QTimer> fastTimer = std::make_shared<QTimer>();
    fastTimer->setInterval(100);
    fastTimer->setSingleShot(false);
    fastTimer->start();


    rainSimulator.setTimer(timer);
    daySimulator.setTimer(timer);
    carSimulator.setTimer(timer);
    //connect(timer, SIGNAL(timeout()), )

    engine.rootContext()->setContextProperty("cppBrightness", stateexchanger.brightness().get());
    engine.rootContext()->setContextProperty("cppLuminosity", stateexchanger.luminosity().get());
    engine.rootContext()->setContextProperty("cppMoisture", stateexchanger.moisture().get());
    engine.rootContext()->setContextProperty("cppWarning", stateexchanger.warning().get());
    engine.rootContext()->setContextProperty("cppProximity", stateexchanger.proximity().get());
    engine.rootContext()->setContextProperty("cppRain", &rainSimulator);
    engine.rootContext()->setContextProperty("cppCar", &carSimulator);
    engine.rootContext()->setContextProperty("cppDay", &daySimulator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* world = engine.rootObjects().first()->findChild<QObject*>(QString("world"));
    if(world!=nullptr)
    {
        QObject::connect(timer.get(),SIGNAL(timeout()), world, SLOT(calculateCelestialPositions()));
        QObject::connect(timer.get(),SIGNAL(timeout()), world, SLOT(calculateBrightness()));
        QObject::connect(fastTimer.get(),SIGNAL(timeout()), world, SLOT(updateCarProximity()));
       // QObject::connect(carSimulator, SIGNAL(carApproaching()),world, SLOT(simulateCar()));
    }
    else
    {
        qDebug() << "Couldn't find gui";
    }

    return app.exec();
}
