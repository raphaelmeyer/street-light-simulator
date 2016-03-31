#include "daysimulator.h"

#include <gtest/gtest.h>
#include <QDebug>


class DaySimulatorTest : public testing::Test {
//public:
    protected:
 virtual void SetUp() {
        day_ = new DaySimulator();
 }

 virtual void TearDown() {
 }
    DaySimulator* day_;

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
    for(int i=0; i<100; i++)
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

TEST(InvalidDaySimulatorTest, random_Time_too_big_in_relation_to_dayDuration)  {
DaySimulator day;
day.setDayDuration(11);
day.setRandomTime(6);
EXPECT_EQ(day.getTimeOfDay(10), DaySimulator::Daytime::NONE);
}
