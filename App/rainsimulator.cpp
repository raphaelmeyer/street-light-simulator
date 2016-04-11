#include "rainsimulator.h"
#include <QObject>
#include <QDebug>

const int kRainCycle = 3*60;
const int kRainDuration = 15;

RainSimulator::RainSimulator(QObject *parent) : EventSimulator(parent)
{
    this->setCycle(kRainCycle);
    this->setDuration(kRainDuration);
    //The rain should be randomly distributed in the whole rain cycle
    setRandomTime((kRainCycle-kRainDuration)/2.0);
    setTiming( ((kRainCycle-kRainDuration) / 2.0) / kRainCycle);
}

void RainSimulator::timeout() {
    time_t now = time(0);
    if( (getEventStart(now) < now) && (getEventEnd(now) > now))
        setRaining(true);
    else
        setRaining(false);
}
bool RainSimulator::getRaining() const
{
    return raining_;
}

void RainSimulator::setRaining(bool value)
{
    if(value != raining_) {
        raining_ = value;
        emit rainChanged(raining_);
    }
}


