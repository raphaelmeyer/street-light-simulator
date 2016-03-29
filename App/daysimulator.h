#ifndef DAYSIMULATOR_H
#define DAYSIMULATOR_H

///This is a class which simulates a day
/// The day will have a duration of dayDuration +- randomTime to simulate clouds/summer/winter
/// Example: DaySimulator(60,5) will simulate a day every 60 seconds, +-5seconds
/// The randomTime addition is constant over multiple computers,
/// with synchronized computers you will always get the same randomTime.

#include <QObject>
#include <ctime>
#include <QTimer>
#include <cstdint>

enum class Daytime {DAY, NIGHT};

class DaySimulator : public QObject
{
    Q_OBJECT
public:
    explicit DaySimulator(int dayDuration, int randomTime, QObject *parent = 0);
    Daytime getDaytime(void);

signals:
    void nightTime();
    void dayTime();

public slots:

private:
    int getDayTime(uint64_t time);
    int getNightTime(uint64_t time);
    void calculateDay(uint64_t time);
    int dayDuration_=0;
    int randomTime_=0;
    QTimer timer_;




};

#endif // DAYSIMULATOR_H
