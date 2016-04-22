#ifndef CARSIMULATOR_H
#define CARSIMULATOR_H

#include "eventsimulator.h"

#include <QTimer>
#include <QObject>


/** \brief The Carsimulator in our world
 * Defines when and how often a car shall drive through the world
 */
class CarSimulator : public EventSimulator
{
  Q_OBJECT
  public:
    ///Constructor
    explicit CarSimulator(QObject *parent = nullptr);
signals:
    /// Signals if a car event should be executed
    void carApproaching(void);

    private slots:
      /// Slot to connect timer signal to
      virtual void timeout();

  private:
    std::shared_ptr<QTimer> timer_; //!< Internal pointer to a timer on whose timeout signal to react
};

#endif // CARSIMULATOR_H
