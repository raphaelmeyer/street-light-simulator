#include "daysimulator.h"




DaySimulator::DaySimulator(int dayDuration, int randomTime, QObject *parent):dayDuration_(dayDuration), randomTime_(randomTime)
{
time_t now = time(0);
//time%dayDuration

}

Daytime DaySimulator::getDaytime()
{

}

int DaySimulator::getDayTime(uint64_t time)
{
return 0;

}

int DaySimulator::getNightTime(uint64_t time)
{
return 0;
}
