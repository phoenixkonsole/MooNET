
Debian
====================
This directory contains files used to package moonetd/moonet-qt
for Debian-based Linux systems. If you compile moonetd/moonet-qt yourself, there are some useful files here.

## moonet: URI support ##


moonet-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install moonet-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your moonetqt binary to `/usr/bin`
and the `../../share/pixmaps/moonet128.png` to `/usr/share/pixmaps`

moonet-qt.protocol (KDE)

