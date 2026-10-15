// SPDX-License-Identifier: GPL-2.0-or-later
#include "inputpassthrough.h"
#include <QQuickWindow>
#include <QRegion>

// A non-empty mask lying entirely outside the surface: Qt Wayland sends it as the input region,
// nothing intersects it, so clicks go to the window below. An empty QRegion would mean "no mask" = full input.
static const QRegion kNoInput(QRect(-2, -2, 1, 1));

InputPassthrough::InputPassthrough(QObject *parent)
    : QObject(parent)
{
    m_timer.setInterval(500);
    connect(&m_timer, &QTimer::timeout, this, &InputPassthrough::apply);
}

InputPassthrough::~InputPassthrough()
{
    restore();
}

void InputPassthrough::setItem(QQuickItem *item)
{
    if (m_item == item)
        return;
    restore();
    if (m_item)
        disconnect(m_item, nullptr, this, nullptr);
    m_item = item;
    if (m_item)
        connect(m_item, &QQuickItem::windowChanged, this, [this] { restore(); apply(); });
    apply();
    Q_EMIT itemChanged();
}

void InputPassthrough::setActive(bool active)
{
    if (m_active == active)
        return;
    m_active = active;
    if (m_active)
        apply();
    else
        restore();
    Q_EMIT activeChanged();
}

void InputPassthrough::apply()
{
    if (!m_active || !m_item || !m_item->window()) {
        m_timer.stop();
        return;
    }
    m_window = m_item->window();
    if (m_window->mask() != kNoInput)
        m_window->setMask(kNoInput);
    m_timer.start();
}

void InputPassthrough::restore()
{
    m_timer.stop();
    if (m_window && m_window->mask() == kNoInput)
        m_window->setMask(QRegion());
    m_window.clear();
}
