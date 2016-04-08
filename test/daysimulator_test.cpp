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
    }

    virtual void TearDown() {
        day_.reset();
    }
    std::shared_ptr<DaySimulator> day_;

};

TEST_F(DaySimulatorTest, valid_day_and_night_periods)  {
    //Test default values of 60s day, 5 random
    for(int i=0;i<24;i++)
        EXPECT_EQ(day_->getTimeOfDay(i),DaySimulator::Daytime::DAY);
    for(int i=35;i<60;i++)
        EXPECT_EQ(day_->getTimeOfDay(i),DaySimulator::Daytime::NIGHT);


}

TEST_F(DaySimulatorTest, uneven_day_with_borderline_big_random)  {
    //Test corner case, 11 will always be night
    day_->setDayDuration(11);
    day_->setRandomTime(5);
    //Test first 100 days to make sure the algorithm works right
    for(int i=0;i<100;i++)
        EXPECT_EQ(day_->getTimeOfDay(10+i*11),DaySimulator::Daytime::NIGHT);
}

TEST_F(DaySimulatorTest, day_only_has_one_daytime_boundary)  {
    //Make sure the day/night time doesn't switch back and forth in between one single day
    //aka. there's a clear boundary between day and night
    for(int i=0; i<50; i++)

        for(int i=0; i<50; i++)
        {
            DaySimulator::Daytime current = DaySimulator::Daytime::DAY;
            //Go to the day boundary
            for(int j=24; j<35; j++){
                DaySimulator::Daytime thisDayTime = day_->getTimeOfDay(j+i*60);
                EXPECT_GE(thisDayTime, current);
                current = thisDayTime;
            }
        }
}

TEST_F(DaySimulatorTest, multiple_instances_have_same_day_boundary)  {
    //Test that multiple instances (a.k.a. multiple computers) have some day/night boundary
    for(int i=0; i<100; i++) {
        std::shared_ptr<DaySimulator> day2 = std::make_shared<DaySimulator>();
        for(int i=0; i<50; i++)
        {
            int dayBoundary = 0;
            int day2Boundary = 0;
            DaySimulator::Daytime current = DaySimulator::Daytime::DAY;
            //Go to the day boundary
            for(int j=24; j<35; j++){
                //if this is the first time it's not day for day_
                if((day_->getTimeOfDay(j+i*60) != DaySimulator::Daytime::DAY) && (dayBoundary == 0))
                    dayBoundary = j;
                //if this is the first time it's not day for day2_
                if((day2->getTimeOfDay(j+i*60) != DaySimulator::Daytime::DAY) && (day2Boundary == 0))
                    day2Boundary = j;
                //if both dayBoundaryies are determined
                if(dayBoundary>0 && day2Boundary > 0)
                    break;
            }
            EXPECT_EQ(dayBoundary, day2Boundary);
        }
    }
}

TEST(InvalidDaySimulatorTest, random_Time_too_big_in_relation_to_dayDuration)  {
    DaySimulator day;
    day.setDayDuration(11);
    day.setRandomTime(6);
    EXPECT_EQ(day.getTimeOfDay(10), DaySimulator::Daytime::NONE);
}

TEST_F(DaySimulatorTest, can_set_and_get_properties)  {
    QSignalSpy spyDay(day_.get(), SIGNAL(dayDurationChanged(uint)));
    QSignalSpy spyRandom(day_.get(), SIGNAL(randomTimeChanged(uint)));
    day_->setDayDuration(11);
    EXPECT_EQ(spyDay.count(),1);
    day_->setRandomTime(4);
    EXPECT_EQ(spyRandom.count(),1);
    //Test that the parameters were set correctly
    EXPECT_EQ(day_->getDayDuration(),11);
    EXPECT_EQ(day_->getRandomTime(),4);
}
