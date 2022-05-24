/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/
pragma Singleton

import QtQuick 2.0

QtObject {
    id: root
    property int percentage: 50

    property string time: "00::30"
    property bool waterActive: false

    property SequentialAnimation animation: SequentialAnimation {
        running: true
        loops: -1
        NumberAnimation {
            target: root
            property: "percentage"
            to: 0
            easing.type: Easing.InQuad
            duration: 500
        }
        PropertyAction { } // actually change the controlled property between the 2 other animations
        NumberAnimation {
            target: root
            property: "percentage"
            to: 100
            easing.type: Easing.OutQuad
            duration: 500
        }
    }

    property SequentialAnimation animation2: SequentialAnimation {
        running: true
        loops: -1
        PropertyAnimation {
            target: root
            property: "waterActive"
            to: false
            duration: 1000
        }
        PropertyAction { } // actually change the controlled property between the 2 other animations
        PropertyAnimation {
            target: root
            property: "waterActive"
            to: true
            duration: 1000
        }
    }
}
