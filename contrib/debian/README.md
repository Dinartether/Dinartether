
Debian
====================
This directory contains files used to package dinartetherd/dinartether-qt
for Debian-based Linux systems. If you compile dinartetherd/dinartether-qt yourself, there are some useful files here.

## dinartether: URI support ##


dinartether-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dinartether-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dinartether-qt binary to `/usr/bin`
and the `../../share/pixmaps/dinartether128.png` to `/usr/share/pixmaps`

dinartether-qt.protocol (KDE)

