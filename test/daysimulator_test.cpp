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
    for(int i=0;i<24;i++)
      EXPECT_EQ(day_->getTimeOfDay(i),Daytime::DAY);
    for(int i=35;i<60;i++)
      EXPECT_EQ(day_->getTimeOfDay(i),Daytime::NIGHT);
}
