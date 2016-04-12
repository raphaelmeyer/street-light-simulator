#include "rainsimulator.h"

#include <gtest/gtest.h>
#include <QDebug>
#include <QSignalSpy>
#include <memory>


class RainSimulatorTest : public testing::Test {
    //public:
protected:
    virtual void SetUp() {
        rain_ = std::make_shared<RainSimulator>();
    }

    virtual void TearDown() {
        rain_.reset();
    }
    std::shared_ptr<RainSimulator> rain_;

};

TEST_F(RainSimulatorTest, can_get_and_set_rain)  {
    QSignalSpy spy(rain_.get(), SIGNAL(rainChanged(bool)));
     rain_->setRain(true);
     EXPECT_EQ(spy.count(),1);
     EXPECT_EQ(rain_->getRain(),true);
}
