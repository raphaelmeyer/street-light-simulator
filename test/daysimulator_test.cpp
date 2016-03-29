#include <gtest/gtest.h>

class DaySimulatorTest : public testing::Test {
//public:
    protected:
 virtual void SetUp() {
 }

 virtual void TearDown() {
 }

};

TEST_F(DaySimulatorTest, can_Execute_Google_Test)  {
    EXPECT_EQ(1,1);
}
