#include "eventsimulator.h"
#include <QDebug>

EventSimulator::EventSimulator(QObject *parent) : QObject(parent)
{
    std::random_device rd;
    gen_ = std::make_shared<std::mt19937>(rd());
    random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);

}
void EventSimulator::setRandomTime(uint randomTime)
{
    if(randomTime_ != randomTime)
    {
        randomTime_ = randomTime;
        random_.reset();
        random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);
        emit randomTimeChanged(randomTime);
    }
}

uint EventSimulator::getRandomTime() const
{
    return randomTime_;
}

uint EventSimulator::getCycle() const
{
    return cycle_;
}

void EventSimulator::setCycle(const uint &cycle)
{
    if (cycle != cycle_) {
        cycle_ = cycle;
        emit cycleChanged(cycle_);
    }
}


int EventSimulator::getEventStart(uint64_t time)
{
    //TODO better test to exclude corner cases where we could calculate below zero
    if(cycle_ < duration_)
        return -1;

    if(gen_ == nullptr || random_ == nullptr)
        throw std::runtime_error("Internal variables not initialized");

    //seed with value depending on time (same time for cycle_ duration
    gen_->seed(time/cycle_);
    int startTime;
    //do {
    //calculate start time +-random time
    startTime = (cycle_*timing_)+(*random_)(*gen_);
    //make sure the start time isn't too late
    // } while( (startTime+duration_) > cycle_);
    //return exact start time for this time

    return ((time/cycle_) * cycle_) + startTime;

}

int EventSimulator::getEventEnd(uint64_t time)
{
    int duration = duration_;
    uint64_t eventStart = getEventStart(time);
    if(((eventStart%cycle_) + duration) > cycle_){
        duration = cycle_-eventStart%cycle_;
    }
    return eventStart+duration;
}

void EventSimulator::setTimer(std::shared_ptr<QTimer> timer)
{
    timer_ = timer;
    if(timer_)
        QObject::connect(timer_.get(), SIGNAL(timeout()), this, SLOT(timeout()));
}

uint EventSimulator::getDuration() const
{
    return duration_;
}

void EventSimulator::setDuration(const uint &duration)
{
    if(duration != duration_) {
        duration_ = duration;
        emit durationChanged(duration_);
    }
}
float EventSimulator::getTiming() const
{
    return timing_;
}

void EventSimulator::setTiming(float timing)
{
    if((timing != timing_) && (timing <= 1.0)) {
        timing_ = timing;
        emit timingChanged(timing_);
    }
}


