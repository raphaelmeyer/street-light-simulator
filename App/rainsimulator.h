#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H

#include "eventsimulator.h"

#include <QTimer>
#include <QObject>


class RainSimulator : public EventSimulator
{
    Q_OBJECT
    Q_PROPERTY(bool rain READ getRain WRITE setRain NOTIFY rainChanged)
public:
    explicit RainSimulator(QObject *parent = nullptr);

    bool getRain() const;
public slots:
    void setRain(bool value);
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
