SET(libkbfxspinxsrc
	kbfxbutton.cpp
	kbfxplasmacanvasabstractitem.cpp
	kbfxplasmacanvasgroup.cpp
	kbfxplasmacanvasgroupview.cpp
	kbfxplasmacanvasitem.cpp
	kbfxplasmacanvasitem_events.cpp
	kbfxplasmacanvasitemwrapper.cpp
	kbfxplasmacanvasstack.cpp
	kbfxplasmacanvasview.cpp
	kbfxplasmaindexitem.cpp
	kbfxplasmaindexview.cpp
	kbfxspinx.cpp
	kbfxspinxmenu.cpp
	kbfxspinxpopup.cpp
	kbfxspinxscrollbar.cpp
	kbfxspinxtoolbar.cpp
	kbfxspinxtoolbutton.cpp
	kbfxspinxtop.cpp
	kbfxspinxview.cpp
	kbfxtooltip.cpp
	)

IF (NOT USE_KDE4)
	KDE3_ADD_DCOP_SKELS(libkbfxspinxsrc kbfxspinx.h)
	KDE3_AUTOMOC(${libkbfxspinxsrc})

	ADD_LIBRARY(kbfxspinx MODULE ${libkbfxspinxsrc})
	SET_TARGET_PROPERTIES(kbfxspinx
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxspinx PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxspinx
	    kbfxdata
	    kbfxcommon
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_UI_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxspinx ${PLUGIN_INSTALL_DIR})
ELSE (NOT USE_KDE4)
	# TODO: Have to rewrite it for DBUS.
	# Rewrite the DCOP interface (in src/) to DBUS for KDE4 support.
	# Should be done in a way to preserve KDE3 compatibility!
	KDE4_ADD_DCOP_SKELS(libkbfxspinxsrc kbfxspinx.h)
	KDE4_AUTOMOC(${libkbfxspinxsrc})

	KDE4_ADD_LIBRARY(kbfxspinx MODULE ${libkbfxspinxsrc})
	TARGET_LINK_LIBRARIES(kbfxspinx
	    kbfxdata
	    kbfxcommon
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxspinx ${PLUGIN_INSTALL_DIR})
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxspinx DESTINATION ${PLUGIN_INSTALL_DIR})
INSTALL(FILES kbfxspinx.desktop DESTINATION ${DATA_INSTALL_DIR}/kicker/applets)
