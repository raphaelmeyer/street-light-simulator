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
    uint getRandomTime() const;

    uint getCycle() const;

    uint getDuration() const;

    float getTiming() const;

    int getEventStart(uint64_t time);
    int getEventEnd(uint64_t time);

    void setTimer(std::shared_ptr<QTimer> timer);

signals:
    void durationChanged(uint newValue);
    void randomTimeChanged(uint newValue);
    void cycleChanged(uint newValue);
    void timingChanged(float newValue);

public slots:

    ///Set the RandomTime to add to the day of this DaySimulator instance
    /// @param randomTime the random Time
    void setRandomTime(uint randomTime);
    void setDuration(const uint &duration);
    void setTiming(float value);
    void setCycle(const uint &value);

private slots:
    virtual void timeout() = 0;

private:
    uint cycle_ = 60;
    uint duration_=30; //!< The duration of the simulated day
    uint randomTime_=5; //!< The random Time to add to the day
    float timing_=0.5;

    std::shared_ptr<std::uniform_int_distribution<int>> random_; //!<
    std::shared_ptr<std::mt19937> gen_;
    std::shared_ptr<QTimer> timer_;
};

#endif // EVENTSIMULATOR_H
