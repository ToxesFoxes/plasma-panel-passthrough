# Panel Passthrough

A tiny KDE Plasma 6 widget that makes **a whole panel click-through**: mouse clicks, scrolling and
right-clicks on the panel go straight to the windows underneath it.

Handy for decorative overlay panels — an audio visualizer like [Kurve](https://github.com/luisbocanegra/kurve)
sitting over the bottom edge of maximized windows, a translucent clock strip, and so on — that should be
visible but never get in the way.

- **Normal mode:** the widget is invisible (zero size) and the panel ignores all input.
- **Edit mode:** the panel is clickable again so you can configure it; the widget shows a small mouse
  icon so you can find, move or remove it.

## How it works

Plasma has no "click-through" option for panels, so the widget ships a small C++ QML module
(`kz.toxesfoxes.inputpassthrough`). It sets the panel window's input mask to a region that lies
outside the surface; on Wayland Qt turns the mask into the surface's input region, so the compositor
routes every pointer event to the window below. Plasma resets the mask whenever it recalculates the
panel, so the module re-applies it.

Limitations:

- **Wayland only** (on X11 `QWindow::setMask` also clips the panel visually).
- Input can't be filtered per button: either the whole panel receives input or none of it does.
- Only affects the panel the widget is placed on.

## Requirements

Plasma 6, Qt ≥ 6.5, a Wayland session. Build deps: CMake, Extra CMake Modules, Qt6 Base/Declarative.

## Install

### Arch Linux

```sh
cd packaging/arch
makepkg -si
```

### From source

```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr
cmake --build build
sudo cmake --install build
```

Restart Plasma (or log out and back in), then right-click a panel → **Add Widgets…** →
**Panel Passthrough**.

To install into your home directory instead, use `-DCMAKE_INSTALL_PREFIX=~/.local` and add
`QML_IMPORT_PATH=${HOME}/.local/lib/qt6/qml` to `~/.config/environment.d/qml.conf` so plasmashell
finds the module.

## Removing the widget

Enter edit mode (right-click the desktop → **Enter Edit Mode**), click the mouse icon on the panel and
remove it — the panel becomes clickable immediately.

## License

GPL-2.0-or-later
