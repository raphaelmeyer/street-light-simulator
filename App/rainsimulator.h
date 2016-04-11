#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H

#include "eventsimulator.h"

#include <QTimer>
#include <QObject>


class RainSimulator : public EventSimulator
{
    Q_OBJECT
    Q_PROPERTY(bool rain READ getRaining WRITE setRaining NOTIFY rainChanged)
public:
    explicit RainSimulator(QObject *parent = nullptr);

    bool getRaining() const;
public slots:
    void setRaining(bool value);
signals:
    void rainChanged(bool raining);

private slots:
    virtual void timeout();

private:
    //std::shared_ptr<EventSimulator> eventSimulator_;
    std::shared_ptr<QTimer> timer_;
    bool raining_ = false;
};

#endif // RAINSIMULATOR_H
