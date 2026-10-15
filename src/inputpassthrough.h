// SPDX-License-Identifier: GPL-2.0-or-later
// Makes the window that hosts `item` transparent to input (empty Wayland input region).
// Plasma calls QWindow::setMask() itself when it recalculates the panel, so the mask is re-applied by a timer.
#pragma once
#include <QObject>
#include <QPointer>
#include <QQuickItem>
#include <QTimer>
#include <qqmlintegration.h>

class InputPassthrough : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQuickItem *item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)

public:
    explicit InputPassthrough(QObject *parent = nullptr);
    ~InputPassthrough() override;

    QQuickItem *item() const { return m_item; }
    void setItem(QQuickItem *item);
    bool active() const { return m_active; }
    void setActive(bool active);

Q_SIGNALS:
    void itemChanged();
    void activeChanged();

private:
    void apply();
    void restore();

    QPointer<QQuickItem> m_item;
    QPointer<QWindow> m_window;
    bool m_active = true;
    QTimer m_timer;
};
