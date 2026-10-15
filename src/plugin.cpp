// SPDX-License-Identifier: GPL-2.0-or-later
#include <QQmlEngineExtensionPlugin>

class InputPassthroughPlugin : public QQmlEngineExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid)
};

#include "plugin.moc"
