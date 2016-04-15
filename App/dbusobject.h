#ifndef DBUSOBJECT_H
#define DBUSOBJECT_H
#include <QApplication>
#include <QObject>
#include <QtDBus/QtDBus>

/// The default path name under which the objects shall be published
#define PATH_NAME "/ch/bbv/streetlight"

/** \brief A class to unify all of our own D-Bus objects
 * we might to extend this in the future, for now it's more or less nothing more than a
 * wrapper for QDBusAbstractAdaptor */
class DBusObject : public QDBusAbstractAdaptor
{
  public:
    ///Constructor
    DBusObject(QObject *application = nullptr);
};

#endif // DBUSOBJECT_H
