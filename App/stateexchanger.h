#ifndef STATEEXCHANGER_H
#define STATEEXCHANGER_H

#include "dbusobject.h"

#include <QObject>
#include <QtDBus/QtDBus>
#include <QApplication>
#include <QString>
#include <memory>

#define SERVICE_NAME "ch.bbv.streetLightSimulator"
#define PATH_NAME "/ch/bbv/streetlight"

///Defines the "measured" sensor brightness of our street-light
class Brightness : public DBusObject
{
    Q_OBJECT
    ///Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.brightness")
    Q_PROPERTY(double scaled READ getScaledBrightness WRITE setScaledBrightness NOTIFY brightnessChanged())
public:
    Brightness(QObject *application) : DBusObject(application) {}

    //Returns the scaled brightness (from 0-1.0)
    double getScaledBrightness() const;
    //Sets the scaled brightness (from 0-1.0)
    void setScaledBrightness(double brightness);

signals:
    void brightnessChanged(double brightness);

private:
    double brightness_ = 0; ///!< the brightness as "measured" (simulated) by our sensor
};

//Defines the luminosity of our lamp
class Luminosity : public DBusObject
{
    Q_OBJECT
    //Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.luminosity")
    Q_PROPERTY(double scaled READ getScaledLuminosity WRITE setScaledLuminosity NOTIFY luminosityChanged())
public:
    Luminosity(QObject *application) : DBusObject(application) {}

    //Returns the scaled luminosity of our lamp (0-1.0)
    double getScaledLuminosity() const;
    //Sets the scaled luminosity of our lamp (0-1.0)
    void setScaledLuminosity(double luminosity);

signals:
    void luminosityChanged(double luminosity);

private:
    double luminosity_ = 0; ///!< The luminosity of our lamp
};


//Exchanges the state of the street-light over D-Bus
class StateExchanger : public QObject
{
    Q_OBJECT
public:
    explicit StateExchanger(QObject *parent = nullptr);
    ~StateExchanger();

    ///Return the brightness instance of this instance
    std::shared_ptr<Brightness> brightness() const;
    ///Return the luminosity instance of this instance
    std::shared_ptr<Luminosity> luminosity() const;

public slots:
    bool initialize();

private:
    std::shared_ptr<Brightness> brightness_; ///!< Pointer to a brightness sensor instance
    std::shared_ptr<Luminosity> luminosity_; ///!< Pointer to the luminosity instance of this lamp
};

#endif // STATEEXCHANGER_H
