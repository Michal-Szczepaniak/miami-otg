#include "dbusobject.h"
#include <QFile>
#include <QString>
#include <fcntl.h>
#include <unistd.h>

DbusObject::DbusObject(QObject *parent) : QObject(parent)
{

}

void DbusObject::toggle()
{
    qDebug() << "toggle called";

    int currentMode = getUSBMode();

    if (currentMode == HOST) {
        setUSBMode(NONE);
        setOTGPower(false);

        emit stateChanged(false);
    } else if (currentMode == PERIPHERAL) {
        emit stateChanged(false);
    } else {
        bool ret = setUSBMode(HOST);
        if (ret) {
            setOTGPower(true);
        }

        emit stateChanged(ret);
    }
}

bool DbusObject::setUSBMode(int value)
{
    int fd = open("/sys/devices/platform/soc/4e00000.ssusb/mode", O_WRONLY);

    if (fd < 0)
        return false ;

    std::string out;
    switch (value) {
    case HOST:
        out = "host";
        break;
    case PERIPHERAL:
        out = "peripheral";
        break;
    case NONE:
    default:
        out = "none";
    }

    ssize_t written = write(fd, out.data(), out.length());

    close(fd);

    return written > 0;
}

int DbusObject::getUSBMode()
{
    QFile f("/sys/devices/platform/soc/4e00000.ssusb/mode");

    if (!f.open(QIODevice::ReadOnly))
        return {};

    QString mode = QString::fromUtf8(f.readAll()).trimmed();
    if (mode == "host") {
        return HOST;
    } else if (mode == "peripheral") {
        return PERIPHERAL;
    } else {
        return NONE;
    }
}

bool DbusObject::setOTGPower(bool state)
{
    int fd = open("/sys/bus/iio/devices/iio:device3/in_index_otg_enable_input", O_WRONLY);

    if (fd < 0)
        return false ;

    std::string out = state ? "1" : "0";
    ssize_t written = write(fd, out.data(), out.length());

    close(fd);

    return written > 0;
}
