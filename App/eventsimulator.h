#ifndef EVENTSIMULATOR_H
#define EVENTSIMULATOR_H

///This is a class which simulates one event in a cycle time and adds some randomness to it
/// It consists of multiple properties:\n
/// **Cycle** length defines how long one cycle shall be, e.g the length of a day \n
/// **duration** defines the duration of the event which will be generated\n
/// **randomTime** defines by how much the event will be randomized. E.g. zero means don't add any random time to the timing\n
/// **timing** defines when the timing shall occur, e.g. 0.5 means in the middle of the cycle \n
/// The randomness will be the same for all instances. So you can run the same program on multiple computers
/// and all events will start and stop at the same time (for the same parameters). 
/// Useful if you want for example simulate day/night cycle with some randomness
/// or rain events in some cycle lengths. 
/// This is a pure virtual class and you should inherit from it to implement your events. 
/// A function will be called on the timeout signal of timer which you have to give it via setTimer

#include <QObject>
#include <cstdint>
#include <memory>
#include<QTimer>

///Simulates events in a cycle with some randomness
class EventSimulator : public QObject
{
    Q_OBJECT

      ///the cycle property
    Q_PROPERTY(uint cycle READ getCycle WRITE setCycle NOTIFY cycleChanged)
    ///the duration property
    Q_PROPERTY(uint duration READ getDuration WRITE setDuration NOTIFY durationChanged)
    ///the randomTime property
    Q_PROPERTY(uint randomTime READ getRandomTime WRITE setRandomTime NOTIFY randomTimeChanged)
    ///The timing property
    Q_PROPERTY(float timing  READ getTiming WRITE setTiming NOTIFY timingChanged)

public:
    ///Constructor
    explicit EventSimulator(QObject *parent = nullptr);

    ///Return the RandomTime
    virtual uint getRandomTime() const;
    ///Returns the cycle time
    virtual uint getCycle() const;
///Returns the duration of the event
    virtual uint getDuration() const;
///Returns the timing of the event (0-1.0)
    virtual float getTiming() const;

    /// Returns the event start in the cycle
    /// @param time a time since linux epoch
    /// @return the start of the event for the cycle in the time
    virtual uint64_t getEventStart(uint64_t time);
    ///Returns the event end in the cycle
    /// @param time a time since linux epoch
    /// @return the end of the event for the cycle in the time
    virtual uint64_t getEventEnd(uint64_t time);

    ///Sets the internal timer pointer to whose timeout signal to react
    virtual void setTimer(std::shared_ptr<QTimer> timer);

signals:
    ///signals the desired event duration has changed
    void durationChanged(uint newValue);
    ///signals the random time has changed
    void randomTimeChanged(uint newValue);
    ///signals the cycle length has changed
    void cycleChanged(uint newValue);
    ///signals the timing of the event has changed
    void timingChanged(float newValue);

public slots:

    ///Set the RandomTime to add to the day of this DaySimulator instance
    /// @param randomTime the random Time
    virtual void setRandomTime(const uint &randomTime);
    ///Sets the duration of the event
    virtual void setDuration(const uint &duration);
    ///Sets the timing in relation to the cycle
    virtual void setTiming(const float &value);
    ///Adds some randomness to the timing event 
    /// @param cyclelength The length of the cycle 
    virtual void setCycle(const uint &cyclelength);

private slots:
  ///Defines the function which should be called on timer timeout
    virtual void timeout() = 0;

private:
    uint cycle_{60}; //!<the cycle time of the simulated thing, e.g. how long a day shall be
    uint duration_{60}; //!< The duration of the event in the cycle, too big events will be truncated to the end of the cycle
    uint randomTime_{5}; //!< The random Time to add to the event timing
    float timing_{0.5}; //!< the timing relative to the cycle length

    std::shared_ptr<std::uniform_int_distribution<int>> random_; //!< Standard distribution from which we'll generate the random time variations
    std::shared_ptr<std::mt19937> gen_; //!< A random number generator
    std::shared_ptr<QTimer> timer_; //!< Internal pointer to a timer
};

#endif // EVENTSIMULATOR_H
