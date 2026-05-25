#ifndef DBUSOBJECT_H
#define DBUSOBJECT_H

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>

class DbusObject : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.verdanditeam.settings.otg")
public:
    explicit DbusObject(QObject *parent = nullptr);

    enum {
        NONE,
        PERIPHERAL,
        HOST,
    };

signals:
    void stateChanged(bool state);

public slots:
    void toggle();

private:
    bool setUSBMode(int value);
    int getUSBMode();
    bool setOTGPower(bool state);
};

#endif // DBUSOBJECT_H
