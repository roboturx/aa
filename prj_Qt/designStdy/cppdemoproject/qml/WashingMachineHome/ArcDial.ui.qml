import QtQuick 2.8
import backend 1.0
import QtQuick.Studio.Components 1.0
import QtQuick.Studio.LogicHelper 1.0

Item {
    id: arcDial
    width: 400
    height: 403

    Item {
        id: backgroundElipse
        x: 0
        y: 0
        width: 400
        height: 400
        Image {
            id: backgroundElipse1
            x: 0
            y: 0
            source: "assets/backgroundElipse1.png"
        }
    }

    Item {
        id: outlineElipse
        x: 0
        y: 0
        width: 400
        height: 400
        Image {
            id: outlineElipse1
            x: 0
            y: 0
            source: "assets/outlineElipse1.png"

            ArcItem {
                id: arc
                x: 15
                y: 16
                width: 369
                height: 370
                end: rangeMapper.output
                begin: -180
                capStyle: 32
                strokeWidth: 14
                strokeColor: "#e9e755"
                fillColor: "#00000000"
            }
        }
    }

    TimerElement {
        id: timerElement
        x: 59
        y: 115
        width: 282
        height: 194
        _45Text: BackendObject.time
        minutesRemainingText: "TIME REMAINING"
    }

    RangeMapper {
        id: rangeMapper
        input: BackendObject.percentage
        outputMaximum: 360
    }
}

/*##^##
Designer {
    D{i:0;height:403;width:400}D{i:2;uuid:"8d9b4f5a-f5a1-55f4-a435-9bd7ad008db2-1"}D{i:1;uuid:"8d9b4f5a-f5a1-55f4-a435-9bd7ad008db2"}
D{i:4;uuid:"cbaf20f4-f684-5d8e-ac5f-aec576c06aed-1"}D{i:3;uuid:"cbaf20f4-f684-5d8e-ac5f-aec576c06aed"}
D{i:6;uuid:"836e273f-ed25-5887-908d-f5a22d06d048"}
}
##^##*/

