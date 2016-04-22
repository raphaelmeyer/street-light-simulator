#ifndef STATEEXCHANGER_H
#define STATEEXCHANGER_H

#include "dbusobject.h"

#include <QObject>
#include <QtDBus/QtDBus>
#include <QApplication>
#include <QString>
#include <memory>

#define SERVICE_NAME "ch.bbv.streetlight"
#define PATH_NAME "/ch/bbv/streetlight"

/// Defines the "measured" sensor brightness of our street-light 
class Brightness : public DBusObject
{
  Q_OBJECT
    ///Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.brightness")
    ///The brightness of the environment, sclaed to 0-1.0
    Q_PROPERTY(double scaled READ getScaledBrightness WRITE setScaledBrightness NOTIFY brightnessChanged())
  public:
    ///Constructor
    Brightness(QObject *application) : DBusObject(application) {}

    ///Returns the scaled brightness (from 0-1.0)
    double getScaledBrightness() const;
    ///Sets the scaled brightness (from 0-1.0)
    void setScaledBrightness(double brightness);

signals:
    ///Signals that the brightness has changed
    void brightnessChanged(double brightness);

  private:
    double brightness_ = 0; //!< the brightness as "measured" (simulated) by our sensor
};

/// Defines the luminosity of our lamp
class Luminosity : public DBusObject
{
  Q_OBJECT
    //Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.luminosity")
    /// The luminosity, scaled to 0-1.0
    Q_PROPERTY(double scaled READ getScaledLuminosity WRITE setScaledLuminosity NOTIFY luminosityChanged())
  public:
    ///Constructor
    Luminosity(QObject *application) : DBusObject(application) {}

    ///Returns the scaled luminosity of our lamp (0-1.0)
    double getScaledLuminosity() const;
    ///Sets the scaled luminosity of our lamp (0-1.0)
    void setScaledLuminosity(double luminosity);

signals:
    ///Signals that the luminosity has changed
    void luminosityChanged(double luminosity);

  private:
    double luminosity_ = 0; //!< The luminosity of our lamp
};

/// Defines the measured moisture as measured by our lamp
class Moisture : public DBusObject
{
  Q_OBJECT
    //Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.moisture")
    ///The moisture, scaled to 0-1
    Q_PROPERTY(double scaled READ getScaledMoisture WRITE setScaledMoisture NOTIFY moistureChanged())
  public:
    ///Constructor
    Moisture(QObject *application) : DBusObject(application) {}

    ///Returns the scaled moisture of our lamp (0-1.0)
    double getScaledMoisture() const;
    ///Sets the scaled moisture of our lamp (0-1.0)
    void setScaledMoisture(double moisture);

signals:
    ///Signals that the moisture has changed
    void moistureChanged(double moisture);

  private:
    double moisture_ = 0; //!< The moisture of our simulated environment
};

/// Defines the warning which should be displayed on the panel
class Warning : public DBusObject
{
  Q_OBJECT
    ///Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.warning")
    /// The phrase which the sign will hold
    Q_PROPERTY(QString phrase READ getWarning WRITE setWarning NOTIFY warningChanged())
  public:
    ///Constructor
    Warning(QObject *application) : DBusObject(application) {}

    ///Returns the warning of our lamp 
    QString getWarning() const;
    ///Sets the warning of our lamp 
    void setWarning(QString Warning);

signals:
    ///Signals that the warning phrase has changed
    void warningChanged(QString warning);

  private:
    QString warning_; //!< The Warning at our sign of our simulated environment
};

class Distance : public DBusObject
{
  Q_OBJECT
    ///Define the interface
    Q_CLASSINFO("D-Bus Interface", "ch.bbv.distance")
    /// The phrase which the sign will hold
    Q_PROPERTY(double distance READ getDistance WRITE setDistance NOTIFY distanceChanged())
  public:
    ///Constructor
    Distance(QObject *application) : DBusObject(application) {}

    ///Returns the distance of our lamp
    float getDistance() const;
    ///Sets the distance of our lamp
    void setDistance(float distance);

signals:
    ///Signals that the distance phrase has changed
    void distanceChanged(double distance);

  private:
    float distance_; //!< The Distance at our sign of our simulated environment
};

///Exchanges the state of the street-light over D-Bus
class StateExchanger : public QObject
{
  Q_OBJECT
  public:
    ///Constructor
    explicit StateExchanger(QObject *parent = nullptr);
    ///Destructor
    ~StateExchanger();

    ///Return the brightness instance of this instance
    std::shared_ptr<Brightness> brightness() const;
    ///Return the luminosity instance of this instance
    std::shared_ptr<Luminosity> luminosity() const;
    ///Return the moisture instance of this instance
    std::shared_ptr<Moisture> moisture() const;
    ///Return the warning instance of this instance
    std::shared_ptr<Warning> warning() const;
    ///Return the distance instance of this instance
    std::shared_ptr<Distance> distance() const;

    public slots:
      ///Initialize the StateExchanger, has to be called before use of d-bus functionality
      bool initialize();

  private:
    std::shared_ptr<Brightness> brightness_; //!< Pointer to a brightness sensor instance
    std::shared_ptr<Luminosity> luminosity_; //!< Pointer to the luminosity instance of this lamp
    std::shared_ptr<Moisture> moisture_; //!< Pointer to the luminosity instance of this lamp
    std::shared_ptr<Warning> warning_; //!< Pointer to the warning instance of this lamp
    std::shared_ptr<Distance> distance_; //!< Pointer to the distance instance of this lamp
};

#endif // STATEEXCHANGER_H
