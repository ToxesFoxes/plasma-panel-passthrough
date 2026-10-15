// SPDX-License-Identifier: GPL-2.0-or-later
import QtQuick
import kz.toxesfoxes.inputpassthrough

Item {
    property alias target: ipt.item
    property alias active: ipt.active
    InputPassthrough { id: ipt }
}
