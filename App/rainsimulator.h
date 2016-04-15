#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H

#include "eventsimulator.h"

#include <QTimer>
#include <QObject>


/** \brief The Rainsimulator in our world
 * Defines when and how often it shall rain in the world
 */
class RainSimulator : public EventSimulator
{
  Q_OBJECT
    Q_PROPERTY(bool rain READ getRain WRITE setRain NOTIFY rainChanged)
  public:
    ///Constructor
    explicit RainSimulator(QObject *parent = nullptr);
    /** Gets the current rain status
     * @return true if it is raining
     */
    bool getRain() const;
    public slots:
      /** Sets the rain status
      /*  @param rain status, true if it is raining
      */
      void setRain(bool value);
signals:
    /// Signals if the rain status changed
    void rainChanged(bool raining);

    private slots:
      /// Slot to connect timer signal to
      virtual void timeout();

  private:
    std::shared_ptr<QTimer> timer_; //!< Internal pointer to a timer on whose timeout signal to react
    bool raining_ = false; //!< Internal variable which saves if it is raining
};

#endif // RAINSIMULATOR_H
