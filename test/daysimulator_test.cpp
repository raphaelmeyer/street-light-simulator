#include "daysimulator.h"

#include <gtest/gtest.h>
#include <QDebug>

class DaySimulatorTest : public testing::Test {
//public:
    protected:
 virtual void SetUp() {
        day_ = new DaySimulator(60,5);
 }

 virtual void TearDown() {
 }
    DaySimulator* day_;

};

TEST_F(DaySimulatorTest, can_Execute_Google_Test)  {
    for(int i=0;i<24;i++)
      EXPECT_EQ(day_->getTimeOfDay(i),Daytime::DAY);
    for(int i=35;i<60;i++)
      EXPECT_EQ(day_->getTimeOfDay(i),Daytime::NIGHT);
}
