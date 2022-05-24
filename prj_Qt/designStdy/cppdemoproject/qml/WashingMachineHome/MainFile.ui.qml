import QtQuick 2.8

Rectangle {
    id: mainFile
    width: 500
    height: 987
    color: "transparent"
    property alias spinLabelText: spinLabel.text
    property alias fabricLabelText: fabricLabel.text
    clip: true

    Item {
        id: mainBackground
        x: 0
        y: 0
        width: 500
        height: 987
        Image {
            id: mainBackground1
            x: 0
            y: 0
            source: "assets/mainBackground1.png"
        }
    }

    ArcDial {
        id: arcDial
        x: 51
        y: 205
        width: 400
        height: 403
    }

    Text {
        id: spinLabel
        x: 0
        y: 662
        width: 501
        height: 42
        color: "#34bb27"
        text: "SPIN CYCLE"
        font.pixelSize: 24
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Roboto"
        font.weight: Font.Normal
    }

    Text {
        id: fabricLabel
        x: 98
        y: 54
        width: 306
        height: 42
        color: "#ffffff"
        text: "COTTON 30"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
        font.family: "Roboto"
        font.weight: Font.Normal
    }

    SpinIcon {
        id: spinIcon
        x: 153
        y: 758
        width: 197
        height: 133
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66;uuid:"0f5c378d-b572-50d7-bcf9-b29189cd8f65"}D{i:2;uuid:"6e1f33f8-a437-59e5-a60e-8f8645218df5-1"}
D{i:1;uuid:"6e1f33f8-a437-59e5-a60e-8f8645218df5"}D{i:3;uuid:"1838a6c9-130c-5572-a4cf-c5a45e7ee7da"}
D{i:4;uuid:"dfca6a4c-8d35-5db4-8a8d-3d74e1ec9eba"}D{i:5;uuid:"5f3bd6d6-c08e-5fba-b908-d992035ecd02"}
D{i:6;uuid:"5b61d918-0486-52b3-90f3-fa32da5aba4b"}
}
##^##*/

