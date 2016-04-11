#ifndef DAYSIMULATOR_H
#define DAYSIMULATOR_H

///This is a class which simulates a day
/// The day will have a duration of dayDuration +- randomTime to simulate clouds/summer/winter
/// Example: DaySimulator(60,5) will simulate a day every 60 seconds, +-5seconds
/// The randomTime addition is constant over multiple computers,
/// with synchronized computers you will always get the same randomTime.
/// Which in turn means the transition from day to night will be the same over multiple computers.

#include "eventsimulator.h"

#include <QObject>
#include <cstdint>
#include <memory>

//enum class Daytime {DAY, NIGHT, NONE};

///Simulates a day/night cycle for times
class DaySimulator : public EventSimulator
{
    Q_OBJECT
    Q_PROPERTY(Daytime daytime READ getDaytime WRITE setDaytime NOTIFY daytimeChanged)
public:
    enum Daytime {DAY, NIGHT, NONE};
    Q_ENUM(Daytime)
    ///Constructor
/// @param dayDuration How long a day shall be in seconds
/// @param randomTime How much the day/night cycle should be ranodm
    //explicit DaySimulator(int dayDuration, int randomTime, QObject *parent = nullptr);
    explicit DaySimulator(QObject *parent = nullptr);


    Daytime getDaytime() const;
public slots:
    void setDaytime(const Daytime &daytime);
signals:
    void daytimeChanged(Daytime daytime);

private slots:
    virtual void timeout();

private:
    Daytime daytime_ = Daytime::DAY;
    std::shared_ptr<QTimer> timer_;
};

#endif // DAYSIMULATOR_H
