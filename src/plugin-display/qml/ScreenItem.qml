// SPDX-FileCopyrightText: 2025 UnionTech Software Technology Co., Ltd.
// SPDX-License-Identifier: GPL-3.0-or-later
import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Effects
import org.deepin.dtk 1.0 as D
import org.deepin.dcc 1.0

Item {
    id: root
    property var screen
    property real translationX: 100
    property real translationY: 100
    property real scale: 0.1
    property bool selected: false
    property real radius: width * 0.05
    signal pressed
    signal positionChanged
    signal released
    signal updatePosition

    focus: true
    Repeater {
        id: repeater
        model: screen.screenItems.length
        delegate: Image {
            id: image
            x: 6 * (repeater.count - index - 1)
            y: 6 * (repeater.count - index - 1)
            z: 1 - 0.01 * index
            width: root.width - 6 * (repeater.count - 1)
            height: root.height - 6 * (repeater.count - 1)
            opacity: index === 0 ? 1 : 0.8
            source: screen.wallpaper
            mipmap: true
            fillMode: Image.PreserveAspectCrop
            asynchronous: true
            layer.enabled: true
            layer.effect: MultiEffect {
                maskEnabled: true
                maskSource: imageMask
                antialiasing: true
                maskThresholdMin: 0.5
                maskSpreadAtMin: 1.0
            }
            Item {
                id: imageMask
                anchors.fill: parent
                layer.enabled: true
                visible: false
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 0.5
                    radius: root.radius
                }
            }
            Rectangle {
                anchors.fill: parent
                radius: root.radius
                color: "transparent"
                border.color: this.palette.text
                opacity: 0.7
                border.width: 1
                smooth: true
            }
        }
    }
    DccLabel {
        x: parent.radius + 6 * repeater.count
        y: parent.radius + 6 * repeater.count
        z: 2
        width: root.width - x - 6
        height: root.height - y - 6
        text: screen.name
        color: "white"
        elide: Text.ElideMiddle
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowBlur: 0.4
        }
    }
    D.DciIcon {
        z: 2
        visible: screen && dccData.primaryScreen && (screen.name === dccData.primaryScreen.name)
        name: "home_screen"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: parent.radius + 5
        anchors.rightMargin: parent.radius + 5
        sourceSize: Qt.size(24, 24)
    }
    Loader {
        active: root.selected
        x: 6 * (repeater.count - 1)
        y: 6 * (repeater.count - 1)
        z: 2
        width: root.width - x
        height: root.height - y
        sourceComponent: Rectangle {
            radius: root.radius
            color: "transparent"
            border.color: this.palette.highlight
            border.width: 1
            smooth: true
        }
    }
    MouseArea {
        z: 2
        anchors.fill: parent
        drag.target: parent
        onPressed: root.pressed()
        onPositionChanged: root.positionChanged()
        onReleased: root.released()
    }
    Component.onCompleted: updatePosition()

    Connections {
        target: screen
        function onXChanged() {
            updatePosition()
        }
        function onYChanged() {
            updatePosition()
        }
        function onWidthChanged() {
            updatePosition()
        }
        function onHeightChanged() {
            updatePosition()
        }
    }
}
