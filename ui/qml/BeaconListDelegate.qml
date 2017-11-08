import QtQuick 2.4
BeaconListDelegateForm {
    property real beaconSnr: 0.;
    beaconSnrImage: getImageForSnr(beaconSnr)
    beaconName: beacon.name
    beaconPosition: beacon.position
    beaconState: beacon.state
    function getImageForSnr(snr) {
        if (snr > 60) {
            return "qrc:/icon/wifi_levels/if_ic_signal_wifi_0.svg";
        } else if (snr > 40) {
            return "qrc:/icon/wifi_levels/if_ic_signal_wifi_1.svg";
        } else if (snr > 20) {
            return "qrc:/icon/wifi_levels/if_ic_signal_wifi_2.svg";
        } else {
            return "qrc:/icon/wifi_levels/if_ic_signal_wifi_3.svg";
        }
    }
}



