TARGET = miami-otg

QT += core dbus

CONFIG += console c++11

SOURCES += src/miami-otg.cpp \
    src/dbusobject.cpp

DISTFILES += qml/miami-otg.qml \
    qml/pages/otg/EnableSwitch.qml \
    rpm/miami-otg.spec \
    otg.json \
    miami-otg.service

target.path = /usr/bin

systemd.files = miami-otg.service
systemd.path = /usr/lib/systemd/system/

entries.files = otg.json
entries.path = /usr/share/jolla-settings/entries

pages.files = qml/pages/otg/EnableSwitch.qml
pages.path = /usr/share/jolla-settings/pages/otg/

INSTALLS += systemd entries pages target

HEADERS += \
    src/dbusobject.h
