#include "dbusobject.h"

#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusConnectionInterface>
#include <QObject>
#include <QDebug>
#include <QTime>
#include <syslog.h>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    openlog("miami-otg", LOG_PID, LOG_DAEMON);

    const QString serviceName("com.verdanditeam.settings.otg");
    const QString objectPath("/");

    QDBusConnection bus = QDBusConnection::systemBus();

    if (!bus.isConnected()) {
        qCritical() << "Failed to connect to D-Bus:"
                    << bus.lastError().message();
        return 1;
    }

    if (!bus.registerService(serviceName)) {
        qCritical() << "Failed to register service:"
                    << bus.lastError().message();
        return 1;
    }

    DbusObject obj;

    if (!bus.registerObject(objectPath, &obj, QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals)) {
        qCritical() << "Failed to register object:"
                    << bus.lastError().message();
        return 1;
    }

    qDebug() << "Listening on"
             << serviceName
             << objectPath;

    int ret = app.exec();

    closelog();

    return ret;
}
