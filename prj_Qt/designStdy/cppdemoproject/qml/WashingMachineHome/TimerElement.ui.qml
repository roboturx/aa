import QtQuick 2.8

Item {
    id: timerElement
    width: 282
    height: 194
    property alias _45Text: _45.text
    property alias minutesRemainingText: minutesRemaining.text

    Text {
        id: _45
        x: 0
        y: 0
        width: 281
        height: 120
        color: "#ffffff"
        text: "45"
        font.pixelSize: 96
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Roboto"
        font.weight: Font.Normal
    }

    Text {
        id: minutesRemaining
        x: 0
        y: 75
        width: 283
        height: 119
        color: "#ffffff"
        text: "Minutes Remaining"
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Roboto"
        font.weight: Font.Normal
    }
}

/*##^##
Designer {
    D{i:0;uuid:"8543f6d3-bd81-5918-8b4c-d5c8f3903404"}D{i:1;uuid:"fbd34c69-d875-5f84-a0b6-be395ea34920"}
D{i:2;uuid:"9844166a-8907-5488-9c57-13f0bfc089f4"}
}
##^##*/

