import QtQuick 2.0
import Sailfish.Silica 1.0
import com.jolla.settings 1.0
import com.jolla.settings.system 1.0
import Nemo.DBus 2.0

SettingsToggle {
    id: root

    name: qsTrId("miami-otg")
    icon.source: "image://theme/icon-m-usb"

    busy: false
    checked: false
    onToggled: {
        dbusInterface.call("toggle")
        busy = true
    }

    DBusInterface {
        id: dbusInterface

        bus: DBus.SystemBus
        service: 'com.verdanditeam.settings.otg'
        path: '/'
        iface: 'com.verdanditeam.settings.otg'

        signalsEnabled: true

        function stateChanged(state) {
            busy = false;
            checked = state;
        }
    }
}
