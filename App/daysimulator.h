#ifndef DAYSIMULATOR_H
#define DAYSIMULATOR_H

///This is a class which simulates a day
/// The day will have a duration of dayDuration +- randomTime to simulate clouds/summer/winter
/// Example: DaySimulator(60,5) will simulate a day every 60 seconds, +-5seconds
/// The randomTime addition is constant over multiple computers,
/// with synchronized computers you will always get the same randomTime.

#include <QObject>
#include <QTimer>
#include <cstdint>
#include <memory>

//enum class Daytime {DAY, NIGHT, NONE};

///Simulates a day/night cycle for times
class DaySimulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(uint dayDuration READ getDayDuration WRITE setDayDuration NOTIFY dayDurationChanged)
    Q_PROPERTY(uint randomTime READ getRandomTime WRITE setRandomTime NOTIFY randomTimeChanged)
    //TODO add properties for dayduration and randomtime
public:
    enum Daytime {DAY, NIGHT, NONE};
    Q_ENUM(Daytime)
    ///Constructor
/// @param dayDuration How long a day shall be in seconds
/// @param randomTime How much the day/night cycle should be ranodm
    //explicit DaySimulator(int dayDuration, int randomTime, QObject *parent = nullptr);
    explicit DaySimulator(QObject *parent = nullptr);


///Return the dayDuration
    uint getDayDuration() const;
    ///Return the RandomTime
    uint getRandomTime() const;

signals:
    void dayDurationChanged(uint newValue);
    void randomTimeChanged(uint newValue);
    //    void nightTime();
//    void dayTime();

public slots:
    /// Set the time duration of this DaySimulator instance
    /// @param duration The duration of the day
    void setDayDuration(uint duration);
    ///Set the RandomTime to add to the day of this DaySimulator instance
    /// @param randomTime the random Time
    void setRandomTime(uint randomTime);
    ///Get the time of day (day/night) for time
    /// @param time Time to query
    Daytime getTimeOfDay(quint64 time);

private:
    ///Returns the end of the day time, will give computer independent results
    /// if the computers' times are synced. E.g. day/night cycles will be synced
    /// if one uses for example time(0)
    /// @param time Time to use as seed
    int getEndOfDayTime(uint64_t time);

    uint dayDuration_=60; //!< The duration of the simulated day
    uint randomTime_=5; //!< The random Time to add to the day
    std::shared_ptr<std::uniform_int_distribution<int>> random_; //!<
    std::shared_ptr<std::mt19937> gen_;
};

#endif // DAYSIMULATOR_H
