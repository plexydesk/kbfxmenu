IF (NOT USE_KDE4)
	KDE3_INSTALL_ICONS(hicolor)
ELSE (NOT USE_KDE4)
	KDE4_INSTALL_ICONS(hicolor)
ENDIF (NOT USE_KDE4)
