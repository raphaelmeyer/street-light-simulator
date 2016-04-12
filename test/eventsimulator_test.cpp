#include "rainsimulator.h"

#include <gtest/gtest.h>
#include <QDebug>
#include <QSignalSpy>
#include <memory>


class EventSimulatorTest : public testing::Test {
protected:
    virtual void SetUp() {
        //RainSimulator implements the pure virtual class EventSimulator
        event_ = std::make_shared<RainSimulator>();
        event_->setDuration(60);
        event_->setCycle(60);
        event_->setRandomTime(5);
        event_->setTiming(0.5);
    }

    virtual void TearDown() {
        event_.reset();
    }
    std::shared_ptr<RainSimulator> event_;

};

TEST_F(EventSimulatorTest, can_get_and_random_time)  {
    QSignalSpy spy(event_.get(), SIGNAL(randomTimeChanged(uint)));
     event_->setRandomTime(50);
     EXPECT_EQ(spy.count(),1);
     EXPECT_EQ(event_->getRandomTime(),50);
}

TEST_F(EventSimulatorTest, can_get_and_duration)  {
    QSignalSpy spy(event_.get(), SIGNAL(durationChanged(uint)));
     event_->setDuration(50);
     EXPECT_EQ(spy.count(),1);
     EXPECT_EQ(event_->getDuration(),50);
}

TEST_F(EventSimulatorTest, can_get_and_timing)  {
    QSignalSpy spy(event_.get(), SIGNAL(timingChanged(float)));
     event_->setTiming(0.9);
     EXPECT_EQ(spy.count(),1);
     EXPECT_FLOAT_EQ(event_->getTiming(),0.9);
     //test limits of timing
     spy.clear();
     event_->setTiming(1.1);
     EXPECT_EQ(spy.count(),0);
     EXPECT_FLOAT_EQ(event_->getTiming(),0.9);
     event_->setTiming(-0.1);
     EXPECT_EQ(spy.count(),0);
     EXPECT_FLOAT_EQ(event_->getTiming(),0.9);
}

TEST_F(EventSimulatorTest, can_get_and_cycle)  {
    QSignalSpy spy(event_.get(), SIGNAL(cycleChanged(uint)));
     event_->setCycle(50);
     EXPECT_EQ(spy.count(),1);
     EXPECT_EQ(event_->getCycle(),50);
}

/*TEST_F(EventSimulatorTest, valid_for_normal_day_and_night)  {
    //Test default values of 60s day, 5 random
    for(int i=0; i<5; i++) {
        EXPECT_GE(event_->getEventStart(i*60), 24+i*60);
        EXPECT_EQ(event_->getEventEnd(i*60), 60+i*60);
    }
}*/


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
        //event start should occur somewhere between 20 and 34
        EXPECT_GE(event_->getEventStart(i*60)%60, 20);
        EXPECT_LE(event_->getEventStart(i*60)%60, 34);
        //event end should occur somewhere between 25 and 39
        EXPECT_GE(event_->getEventEnd(i*60)%60, 25);
        EXPECT_LE(event_->getEventEnd(i*60)%60, 39);
        //check that the times actually increases
        EXPECT_GE(event_->getEventStart(i*60),i*60);
        EXPECT_GE(event_->getEventEnd(i*60),i*60);
    }
}

//test that if we set a timer it will trigger
//as we cannot test the timeout signal directly, check if rain changed
//when it was set up to should have changed on timer signal
TEST_F(EventSimulatorTest, can_get_and_set_timer_and_it_will_trigger)  {
     QSignalSpy spy(event_.get(), SIGNAL(rainChanged(bool)));
    std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();
    timer->stop();
    timer->setInterval(1);
    timer->setSingleShot(true);
    event_->setTimer(timer);
    event_->setTiming(0);
    event_->setRandomTime(0);
    timer->start();
    usleep(1000);
    QCoreApplication::processEvents();
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(event_->getRain(), true);
    //check for change back to no rain
    spy.clear();
    event_->setTiming(1);
    timer->start();
    usleep(1000);
    QCoreApplication::processEvents();
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(event_->getRain(), false);
}

TEST_F(EventSimulatorTest, uneven_event_with_borderline_big_random)  {
    //Test corner case, 11 will always be event
    event_->setDuration(11);
    event_->setRandomTime(5);
    //Test first 100 days to make sure the algorithm works right
    for(int i=0;i<100;i++)
        EXPECT_LE(event_->getEventStart(10+i*11)%11,10);
}

TEST_F(EventSimulatorTest, multiple_instances_have_same_boundary)  {
    //Test that multiple instances (a.k.a. multiple computers) have same boundary
            std::shared_ptr<RainSimulator> event2 = std::make_shared<RainSimulator>();
            event2->setDuration(60);
            event2->setCycle(60);
            event2->setRandomTime(5);
            event2->setTiming(0.5);
    for(int i=0; i<100; i++) {
            EXPECT_EQ(event_->getEventStart(i*60), event2->getEventStart(i*60));
    }
}

