#ifndef EVENTSIMULATOR_H
#define EVENTSIMULATOR_H

///This is a class which simulates a event
/// The day will have a duration of eventDuration +- randomTime to simulate clouds/summer/winter

#include <QObject>
#include <cstdint>
#include <memory>
#include<QTimer>

///Simulates a day/night cycle for times
class EventSimulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(uint cycle READ getCycle WRITE setCycle NOTIFY cycleChanged)
    Q_PROPERTY(uint duration READ getDuration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(uint randomTime READ getRandomTime WRITE setRandomTime NOTIFY randomTimeChanged)
    Q_PROPERTY(float timing  READ getTiming WRITE setTiming NOTIFY timingChanged)

public:
    explicit EventSimulator(QObject *parent = nullptr);

    ///Return the RandomTime
    virtual uint getRandomTime() const;

    virtual uint getCycle() const;

    virtual uint getDuration() const;

    virtual float getTiming() const;

    virtual uint64_t getEventStart(uint64_t time);
    virtual uint64_t getEventEnd(uint64_t time);

    virtual void setTimer(std::shared_ptr<QTimer> timer);

signals:
    void durationChanged(uint newValue);
    void randomTimeChanged(uint newValue);
    void cycleChanged(uint newValue);
    void timingChanged(float newValue);

public slots:

    ///Set the RandomTime to add to the day of this DaySimulator instance
    /// @param randomTime the random Time
    virtual void setRandomTime(uint randomTime);
    virtual void setDuration(const uint &duration);
    virtual void setTiming(float value);
    virtual void setCycle(const uint &value);

private slots:
    virtual void timeout() = 0;

private:
    uint cycle_{60}; //!<the duration of the simulated thing
    uint duration_{60}; //!< The duration of the event in the cycle, too big events will be truncated to the end of the cycle
    uint randomTime_{5}; //!< The random Time to add to the event timing
    float timing_{0.5}; //!< the timing relative to the cycle length

    std::shared_ptr<std::uniform_int_distribution<int>> random_; //!<
    std::shared_ptr<std::mt19937> gen_;
    std::shared_ptr<QTimer> timer_;
};

#endif // EVENTSIMULATOR_H
