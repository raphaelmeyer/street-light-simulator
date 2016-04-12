#include "daysimulator.h"

#include <gtest/gtest.h>
#include <QDebug>
#include <QSignalSpy>
#include <memory>


class DaySimulatorTest : public testing::Test {
    //public:
protected:
    virtual void SetUp() {
        day_ = std::make_shared<DaySimulator>();
        qRegisterMetaType<DaySimulator::Daytime>("Daytime");
    }

    virtual void TearDown() {
        day_.reset();
    }
    std::shared_ptr<DaySimulator> day_;

};

TEST_F(DaySimulatorTest, can_get_and_set_daytime)  {
    QSignalSpy spy(day_.get(), SIGNAL(daytimeChanged(Daytime)));
     day_->setDaytime(DaySimulator::NIGHT);
     EXPECT_EQ(spy.count(),1);
     EXPECT_EQ(day_->getDaytime(),DaySimulator::NIGHT);
}

TEST_F(DaySimulatorTest, valid_day_and_night_periods)  {
    //Test default values of 60s day, 5 random
    for(int i=0;i<24;i++)
        EXPECT_GE(day_->getEventStart(i),24);
    for(int i=35;i<60;i++)
        EXPECT_EQ(day_->getEventEnd(i),60);
}

TEST_F(DaySimulatorTest, uneven_day_with_borderline_big_random)  {
    //Test corner case, 11 will always be night
    day_->setCycle(11);
    day_->setRandomTime(5);
    day_->setTiming(0.5);
    //Test first 100 days to make sure the algorithm works right
    for(int i=0;i<100;i++)
        EXPECT_LE(day_->getEventStart(i*11),10+11*i);
}

//test random truncated when it may lap under cycle start time
TEST_F(DaySimulatorTest, random_truncated_to_be_in_cycle_time)  {
    day_->setCycle(3);
    day_->setRandomTime(50);
    //Test first 100 days to make sure the algorithm works right
    for(int i=0;i<100;i++){
        EXPECT_LE(day_->getEventStart(i*3),2+3*i);
        EXPECT_GE(day_->getEventStart(i*3),3*i);
        EXPECT_LE(day_->getEventEnd(i*3),(2+3*i)+1);
    }
}


TEST_F(DaySimulatorTest, day_only_has_one_daytime_boundary)  {
    //Make sure the day/night time doesn't switch back and forth in between one single day
    //aka. there's a clear boundary between day and night
    for(int i=0; i<50; i++)
        EXPECT_EQ(day_->getEventEnd(i*60), 60+i*60);
}


