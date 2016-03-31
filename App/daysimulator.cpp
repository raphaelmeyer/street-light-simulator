#include "daysimulator.h"

#include <QDebug>
#include <random>
#include <ctime>



DaySimulator::DaySimulator(QObject *parent) : QObject(parent)
{
    std::random_device rd;
    gen_ = std::make_shared<std::mt19937>(rd());
    random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);
}

DaySimulator::Daytime DaySimulator::getTimeOfDay(quint64 time)
{
    int endofDay = getEndOfDayTime(time);

    if(endofDay < 0)
        return Daytime::NONE;

    if( time%dayDuration_ < (unsigned)endofDay )
        return Daytime::DAY;

    return Daytime::NIGHT;

}

void DaySimulator::setDayDuration(uint duration)
{
    if(dayDuration_ != duration) {
        dayDuration_ = duration;
        emit dayDurationChanged(duration);
    }
}

void DaySimulator::setRandomTime(uint randomTime)
{
    if(randomTime_ != randomTime)
    {
        randomTime_ = randomTime;
        random_.reset();
        random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);
        emit randomTimeChanged(randomTime);
    }
}

////Returns the border of day for the time provided.
int DaySimulator::getEndOfDayTime(uint64_t time)
{
    //TODO better test to exclude corner cases where we could calculate below zero
    if(dayDuration_ < 2*randomTime_)
        return -1;

    if(gen_ == nullptr || random_ == nullptr)
        return -1;
    //calculate if we're in day or night time
    //e.g. for day of 60 seconds and +/-5sec random:
    //0-24 is sure day, 35-59 is sure night, inbetween is random
    //seeding with time ensures that we have the same day/night cycle
    //all machines (provided their time is synced)
    //note: what happens on e.g. 11 day and 5 random?
    //11/2=5.5=->5, 5 (+-5) -> min 0, max 10, so 11 is always night
    gen_->seed(time/dayDuration_);
    return (dayDuration_/2)+(*random_)(*gen_);

}
uint DaySimulator::getRandomTime() const
{
    return randomTime_;
}

uint DaySimulator::getDayDuration() const
{
    return dayDuration_;
}


