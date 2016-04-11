#include "rainsimulator.h"

#include <gtest/gtest.h>
#include <QDebug>
#include <QSignalSpy>
#include <memory>


class EventSimulatorTest : public testing::Test {
    //public:
protected:
    virtual void SetUp() {
        //RainSimulator implements EventSimulator
        event_ = std::make_shared<RainSimulator>();
        event_->setDuration(60);
        event_->setCycle(60);
        event_->setRandomTime(5);
        event_->setTiming(0.5);
    }

    virtual void TearDown() {
        event_.reset();
    }
    std::shared_ptr<EventSimulator> event_;

};

TEST_F(EventSimulatorTest, valid_for_normal_day_and_night)  {
    //Test default values of 60s day, 5 random
    for(int i=0; i<50; i++) {
        EXPECT_GE(event_->getEventStart(i*60)%60, 24);
        EXPECT_EQ(event_->getEventEnd(i*60)%60, 0);
    }
}


//simulate a case in which we want 5 second events between the 20 and 40 second mark of every minute
TEST_F(EventSimulatorTest, shorter_event_duration_is_calculated_correctly)  {
    event_->setDuration(5);
    //the events can start between second 20 and 35 --> middle is 27.5=27
    // timing: 27/60 = 0.45
    event_->setTiming(0.45);
    //random time is (35-20)/2 = 7.5 = 7
    event_->setRandomTime(7);
    //we have a actual range of event start from 20 to 34, which means the event is always over before the 40th second.
    //We accept this behaviour here.
    for(int i=0; i<50; i++) {
        EXPECT_GE(event_->getEventStart(i*60)%60, 20);
        EXPECT_LE(event_->getEventStart(i*60)%60, 34);
        EXPECT_GE(event_->getEventEnd(i*60)%60, 25);
        EXPECT_LE(event_->getEventEnd(i*60)%60, 39);
    }
}

//TODO. add tests for timers, look at below tests if still needed
/*
TEST_F(EventSimulatorTest, uneven_event_with_borderline_big_random)  {
    //Test corner case, 11 will always be night
    event_->setDuration(11);
    event_->setRandomTime(5);
    //Test first 100 days to make sure the algorithm works right
    for(int i=0;i<100;i++)
        EXPECT_EQ(event_->getEventStart(10+i*11),EventSimulator::Daytime::NIGHT);
}
/*
TEST_F(EventSimulatorTest, event_only_has_one_daytime_boundary)  {
    //Make sure the day/night time doesn't switch back and forth in between one single day
    //aka. there's a clear boundary between day and night
    for(int i=0; i<50; i++)

        for(int i=0; i<50; i++)
        {
            EventSimulator::Daytime current = EventSimulator::Daytime::DAY;
            //Go to the day boundary
            for(int j=24; j<35; j++){
                EventSimulator::Daytime thisDayTime = event_->getTimeOfDay(j+i*60);
                EXPECT_GE(thisDayTime, current);
                current = thisDayTime;
            }
        }
}

TEST_F(EventSimulatorTest, multiple_instances_have_same_event_boundary)  {
    //Test that multiple instances (a.k.a. multiple computers) have some day/night boundary
    for(int i=0; i<100; i++) {
        std::shared_ptr<EventSimulator> day2 = std::make_shared<EventSimulator>();
        for(int i=0; i<50; i++)
        {
            int dayBoundary = 0;
            int day2Boundary = 0;
            //Go to the day boundary
            for(int j=24; j<35; j++){
                //if this is the first time it's not day for event_
                if((event_->getTimeOfDay(j+i*60) != EventSimulator::Daytime::DAY) && (dayBoundary == 0))
                    dayBoundary = j;
                //if this is the first time it's not day for day2_
                if((day2->getTimeOfDay(j+i*60) != EventSimulator::Daytime::DAY) && (day2Boundary == 0))
                    day2Boundary = j;
                //if both dayBoundaryies are determined
                if(dayBoundary>0 && day2Boundary > 0)
                    break;
            }
            EXPECT_EQ(dayBoundary, day2Boundary);
        }
    }
}

TEST(InvalidEventSimulatorTest, random_Time_too_big_in_relation_to_dayDuration)  {
    EventSimulator day;
    day.setDayDuration(11);
    day.setRandomTime(6);
    EXPECT_EQ(day.getTimeOfDay(10), EventSimulator::Daytime::NONE);
}

TEST_F(EventSimulatorTest, can_set_and_get_properties)  {
    QSignalSpy spyDay(event_.get(), SIGNAL(dayDurationChanged(uint)));
    QSignalSpy spyRandom(event_.get(), SIGNAL(randomTimeChanged(uint)));
    event_->setDayDuration(11);
    EXPECT_EQ(spyDay.count(),1);
    event_->setRandomTime(4);
    EXPECT_EQ(spyRandom.count(),1);
    //Test that the parameters were set correctly
    EXPECT_EQ(event_->getDayDuration(),11);
    EXPECT_EQ(event_->getRandomTime(),4);
}
*/
