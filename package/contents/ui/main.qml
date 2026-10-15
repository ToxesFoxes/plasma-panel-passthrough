// SPDX-License-Identifier: GPL-2.0-or-later
// The whole panel hosting this widget lets clicks pass through to the windows below.
// In Plasma edit mode the panel is clickable again and the widget shows an icon.
// Requires the kz.toxesfoxes.inputpassthrough QML module from this repository.
import QtQuick
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.plasmoid

PlasmoidItem {
    id: root

    readonly property bool editMode: Plasmoid.containment.corona?.editMode ?? false
    readonly property bool inPanel: Plasmoid.formFactor === PlasmaCore.Types.Horizontal
                                    || Plasmoid.formFactor === PlasmaCore.Types.Vertical

    Plasmoid.backgroundHints: PlasmaCore.Types.NoBackground
    preferredRepresentation: fullRepresentation
    toolTipMainText: Plasmoid.title
    toolTipSubText: i18n("Clicks pass through this panel outside edit mode")

    fullRepresentation: Item {
        Layout.preferredWidth: root.editMode ? Kirigami.Units.iconSizes.small : 0
        Layout.preferredHeight: root.editMode ? Kirigami.Units.iconSizes.small : 0
        Layout.minimumWidth: Layout.preferredWidth
        Layout.maximumWidth: Layout.preferredWidth

        Kirigami.Icon {
            anchors.fill: parent
            source: "input-mouse"
            visible: root.editMode
        }
    }

    // Loaded via Loader: if the module is missing, the widget simply does nothing
    Loader {
        active: root.inPanel
        source: "Passthrough.qml"
        onLoaded: {
            item.target = root;
            item.active = Qt.binding(() => !root.editMode);
        }
    }
}
