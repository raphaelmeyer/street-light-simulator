#include "daysimulator.h"

#include <QDebug>
#include <random>
#include <ctime>



DaySimulator::DaySimulator(int dayDuration, int randomTime, QObject *parent):dayDuration_(dayDuration), randomTime_(randomTime), QObject(parent)
{
  std::random_device rd;
  gen_ = std::make_shared<std::mt19937>(rd());
  random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);
}

Daytime DaySimulator::getTimeOfDay(uint64_t time)
{
  //qDebug() << "Day boundary is "<<getDayTime(time);
  if( time%dayDuration_< getEndOfDayTime(time) )
    return Daytime::DAY;

  return Daytime::NIGHT;

}

////Returns the border of day for the time provided.
uint DaySimulator::getEndOfDayTime(uint64_t time)
{
  //calculate if we're in day or night time
  //e.g. for day of 60 seconds and +/-5sec random:
  //0-24 is sure day, 35-59 is sure night, inbetween is random
  //seeding with time ensures that we have the same day/night cycle
  //all machines (provided their time is synced)
  gen_->seed(time);
  return (dayDuration_/2)+(*random_)(*gen_);

}

