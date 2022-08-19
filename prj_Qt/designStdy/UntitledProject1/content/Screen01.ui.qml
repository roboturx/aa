/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick 6.3
import QtQuick.Controls 6.3
import QtQuick3D 6.3
import UntitledProject1

Rectangle {
    width: 1024
    height: 768

    color: Constants.backgroundColor
    property alias view3D: view3D

    View3D {
        id: view3D
        anchors.fill: parent
        antialiasing: false
        z: 1
        anchors.rightMargin: -317
        anchors.bottomMargin: -60
        anchors.leftMargin: 317
        anchors.topMargin: 60
        transformOrigin: Item.Center
        scale: 1
        rotation: -31.953

        environment: sceneEnvironment

        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
                x: 28
                y: 54
                color: "#f2a0a0"
                z: 36
                scope: cubeModel
                brightness: 0.8
                ambientColor: "#b32b2b"
            }

            PerspectiveCamera {
                id: sceneCamera
                z: 350
            }

            Model {
                id: cubeModel
                eulerRotation.y: 45
                eulerRotation.x: 30
                materials: defaultMaterial
                source: "#Cube"
            }
        }

        FocusScope {
            id: focusScope
            x: 8
            y: 71
            width: 518
            height: 397

            Item {
                id: item1
                x: 164
                y: 342
                width: 446
                height: 857
            }
        }
    }

    Item {
        id: __materialLibrary__
        DefaultMaterial {
            id: defaultMaterial
            objectName: "Default Material"
            diffuseColor: "#4aee45"
        }
    }

    Text {
        width: 449
        height: 164
        text: qsTr("Hello UntitledProject1")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenterOffset: -24
        font.bold: true
        font.pointSize: 68
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
        font.family: Constants.font.family
    }

    BorderImage {
        id: borderImage
        x: 60
        y: 288
        width: 572
        height: 420
        source: "../../../../../../../../home/m/9535042d-3bae-47ca-aa6e-79cdc824c09a.jpg"
        focus: false
    }

    Flickable {
        id: flickable
        x: 60
        y: 80
        width: 584
        height: 660

        RangeSlider {
            id: rangeSlider
            x: 88
            y: 64
            width: 528
            height: 172
            first.value: 0.25
            second.value: 0.75
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.25}D{i:4}D{i:5}D{i:6}
}
##^##*/
