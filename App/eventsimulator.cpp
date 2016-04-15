#include "eventsimulator.h"
#include <QDebug>

EventSimulator::EventSimulator(QObject *parent) : QObject(parent)
{
    std::random_device rd;
    gen_ = std::make_shared<std::mt19937>(rd());
    random_ = std::make_shared<std::uniform_int_distribution<int>>(-1*randomTime_, randomTime_);

}
void EventSimulator::setRandomTime(const uint &randomTime)
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


uint64_t EventSimulator::getEventStart(uint64_t time)
{

    if(2*randomTime_ > cycle_)
        qWarning() << "WARNING: Random Time is bigger than cycle";

    if(gen_ == nullptr || random_ == nullptr)
        throw std::runtime_error("Internal variables not initialized");

    //calculate the start of this cycling
    uint64_t cycle_start = (time/cycle_)*cycle_;
    //seed with value depending on time (same time for cycle_ duration
    gen_->seed(cycle_start);
    long startTime;
    //calculate start time +-random time
    //this line gives wrong result?! startTime = (1.0*cycle_*timing_)+(*random_)(*gen_);
    startTime = (cycle_*timing_)+(*random_)(*gen_);
    /*int random = (*random_)(*gen_);
    if( ((startTime+random) >= 0) )
    {
        startTime+=random;
        //qDebug() << "Adding random";
    }*/
    //qDebug() << "cyle "<<cycle_<<" timing "<<timing_;
    //qDebug() << "Starttime: "<<startTime<<" calc:"<<1.0*cycle_*timing_<<" random: "<<startTime-(cycle_*timing_)<<" cycle start: "<<cycle_start;


    //check to see if we're still in the supposed range and not too low
    if((cycle_start+startTime) < cycle_start)
        return cycle_start;
    //check that we don't overshoot either: e.g. cycle = 3, start should be in [0..2] -> max is cycle_start+cycle-1
    if((cycle_start+startTime) > (cycle_start+cycle_-1))
        return cycle_start+cycle_-1;

    //return exact start time for this time
    return cycle_start + startTime;
}

uint64_t EventSimulator::getEventEnd(uint64_t time)
{
    int duration = duration_;
    uint64_t eventStart = getEventStart(time);

    if(((eventStart%cycle_) + duration) > cycle_){
        duration = cycle_-eventStart%cycle_;
        //qDebug() << "Duration is "<<duration<<"calc is "<<eventStart%cycle_;
    }
    //qDebug()<<"Event start is "<<eventStart<<" final calc is "<<eventStart+duration;
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

void EventSimulator::setTiming(const float &timing)
{
    if((timing != timing_) && (timing <= 1.0) && (timing >= 0)) {
        timing_ = timing;
        emit timingChanged(timing_);
    }
}


