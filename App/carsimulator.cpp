#include "carsimulator.h"
#include <QObject>
#include <QDebug>

const int kCarCycle = 10;
const int kCarDuration = 1;

CarSimulator::CarSimulator(QObject *parent) : EventSimulator(parent)
{
    this->setCycle(kCarCycle);
    this->setDuration(kCarDuration);
    //The rain should be randomly distributed in the whole rain cycle
    setRandomTime((kCarCycle-kCarDuration)/2.0);
    setTiming( ((kCarCycle-kCarDuration) / 2.0) / kCarCycle);
}

void CarSimulator::timeout() {
    uint64_t now = time(0);
    if( (getEventStart(now) < now) && (getEventEnd(now) > now))
        emit carApproaching();
}


