#include "stateexchanger.h"

StateExchanger::StateExchanger(QObject *parent) : QObject(parent)
{
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n");
    }
}

StateExchanger::~StateExchanger()
{
    QDBusConnection::sessionBus().unregisterService(SERVICE_NAME);
}

bool StateExchanger::initialize()
{
    brightness_ = std::make_shared<Brightness>(this);
    luminosity_ = std::make_shared<Luminosity>(this);
    moisture_ = std::make_shared<Moisture>(this);

    if(brightness_==nullptr || luminosity_==nullptr || moisture_==nullptr) {
        qDebug() << "Could not create a D-Bus object";
        return false;
    }

    if(!QDBusConnection::sessionBus().registerService(SERVICE_NAME))
    {
        qDebug() << "Could not register service";
        return false;
    }
    //QDBusConnection::sessionBus().registerObject("/ch/bbv/streetlight","ch.bbv.streetLightSimulator",this, QDBusConnection::ExportChildObjects);
    QDBusConnection::sessionBus().registerObject(PATH_NAME, this);
    //qDebug() << "Registered object";

    return true;
}
std::shared_ptr<Luminosity> StateExchanger::luminosity() const
{
    return luminosity_;
}

std::shared_ptr<Brightness> StateExchanger::brightness() const
{
    return brightness_;
}

std::shared_ptr<Moisture> StateExchanger::moisture() const
{
    return moisture_;
}


double Brightness::getScaledBrightness() const
{
    return brightness_;
}

void Brightness::setScaledBrightness(double brightness)
{
    if((brightness <= 1) && (brightness != brightness_)) {
        brightness_ = brightness;
        emit brightnessChanged(brightness_);
    }
}

double Luminosity::getScaledLuminosity() const
{
    return luminosity_;
}

void Luminosity::setScaledLuminosity(double luminosity)
{
    if((luminosity <= 1) && (luminosity != luminosity_)) {
        luminosity_ = luminosity;
        emit luminosityChanged(luminosity_);
    }
}


double Moisture::getScaledMoisture() const
{
    return moisture_;
}

void Moisture::setScaledMoisture(double moisture)
{
    if((moisture <= 1) && (moisture != moisture_)) {
        moisture_ = moisture;
        emit moistureChanged(moisture_);
    }
}
