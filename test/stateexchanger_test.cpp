
#include "stateexchanger.h"

#include <gtest/gtest.h>
#include <QtDBus/QtDBus>
#include <QDebug>
#include <QSignalSpy>
#include <memory>

#define SERVICE_NAME "ch.bbv.streetLightSimulator"
#define PATH_NAME "/ch/bbv/streetlight"

class StateExchangerTest : public testing::Test {
    //public:
protected:
    virtual void SetUp() {
        stateexchanger_ = std::make_shared<StateExchanger>();
        EXPECT_TRUE(stateexchanger_->initialize());
        dbus_luminosity_ = std::make_shared<QDBusInterface>(SERVICE_NAME, PATH_NAME, "ch.bbv.luminosity", QDBusConnection::sessionBus());
        dbus_brightness_ = std::make_shared<QDBusInterface>(SERVICE_NAME, PATH_NAME, "ch.bbv.brightness", QDBusConnection::sessionBus());
        dbus_moisture_ = std::make_shared<QDBusInterface>(SERVICE_NAME, PATH_NAME, "ch.bbv.moisture", QDBusConnection::sessionBus());
        dbus_warning_ = std::make_shared<QDBusInterface>(SERVICE_NAME, PATH_NAME, "ch.bbv.warning", QDBusConnection::sessionBus());
        if (!QDBusConnection::sessionBus().isConnected()) {
            fprintf(stderr, "Cannot connect to the D-Bus session bus.\n");
            exit(1);
        }
    }

    virtual void TearDown() {
    }
    std::shared_ptr<StateExchanger> stateexchanger_;
    std::shared_ptr<QDBusInterface> dbus_luminosity_;
    std::shared_ptr<QDBusInterface> dbus_brightness_;
    std::shared_ptr<QDBusInterface> dbus_moisture_;
    std::shared_ptr<QDBusInterface> dbus_warning_;
};

TEST_F(StateExchangerTest, can_get_and_set_luminosity) {
    QSignalSpy spy(stateexchanger_->luminosity().get(), SIGNAL(luminosityChanged(double)));

    dbus_luminosity_->setProperty("scaled", 0.5);
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(dbus_luminosity_->property("scaled"), 0.5);
}

TEST_F(StateExchangerTest, can_get_and_set_brightness) {
    QSignalSpy spy(stateexchanger_->brightness().get(), SIGNAL(brightnessChanged(double)));

    dbus_brightness_->setProperty("scaled", 0.5);
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(dbus_brightness_->property("scaled"), 0.5);
}

TEST_F(StateExchangerTest, can_get_and_set_moisture) {
    QSignalSpy spy(stateexchanger_->moisture().get(), SIGNAL(moistureChanged(double)));

    dbus_moisture_->setProperty("scaled", 0.5);
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(dbus_moisture_->property("scaled"), 0.5);
}

TEST_F(StateExchangerTest, can_get_and_set_warning) {
    QSignalSpy spy(stateexchanger_->warning().get(), SIGNAL(warningChanged(QString)));

    dbus_warning_->setProperty("phrase", "This is a test");
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(dbus_warning_->property("phrase"), "This is a test");
}
