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
    ///The daytime property which holds if it is day or night
    Q_PROPERTY(Daytime daytime READ getDaytime WRITE setDaytime NOTIFY daytimeChanged)
    /// Holds when the night will start for the last (on timeout) calculated cycle
    Q_PROPERTY(quint64 nightStart READ getNightStart NOTIFY nightStartChanged)
  public:
    ///Daytime enumeration, tells if it is DAY (bright outside) or night. NONE is typically not used
    enum Daytime {DAY, NIGHT, NONE};
    Q_ENUM(Daytime)
      ///Constructor
      explicit DaySimulator(QObject *parent = nullptr);

    /// Sets the random Time of the day, e.g. how much day/night shall be random
    void setRandomTime(uint randomTime);
    /// Sets the cycle length of the day, e.g. how long one "24hour day" (day plus night) shall be
    void setCycle(uint cycle);
    ///Returns the current status of fthe daytime variable
    Daytime getDaytime() const;
    ///Returns when the night will start for the last calculated cycle
    uint64_t getNightStart() const;
    public slots:
      ///Set the Daytime
      void setDaytime(const Daytime &daytime);
signals:
    ///Signals that the daytime has changed (typically in timeout)
    void daytimeChanged(Daytime daytime);
    ///Signals that we calculated a new nightStart (typically in timeout)
    void nightStartChanged(uint64_t nightStart);

    private slots:
      ///Internal timeout slot to be called by timer
      virtual void timeout();

  private:
    //!< set The nightstart, called by internal calculation
    void setNightStart(uint64_t nightStart);
    Daytime daytime_{Daytime::DAY}; //!< Internal variable to keep track of daytime
    uint64_t nightStart_{0}; //!< Internal variable to keep track when the night will start for last (typically on timeout) calculated cycle
    std::shared_ptr<QTimer> timer_; //!< Internal variable to timer on whose timeout signal to react
};

#endif // DAYSIMULATOR_H
