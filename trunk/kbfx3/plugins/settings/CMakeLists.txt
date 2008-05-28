SET(libkbfxplasmadatasettingssrc
    kbfxplasmadatapluginsettings.cpp
   )

FILE(GLOB HEADERS *.h)

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${libkbfxplasmadatasettingssrc})

	ADD_LIBRARY(kbfxplasmadatasettings SHARED ${libkbfxplasmadatasettingssrc})
	SET_TARGET_PROPERTIES(kbfxplasmadatasettings
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxplasmadatasettings PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxplasmadatasettings
	    kbfxdata
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    ${KDE3_KHTML_LIBRARY}
	    ${M_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxplasmadatasettings ${LIB_INSTALL_DIR}/kbfx/plugins)
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${libkbfxplasmadatasettingssrc})

	KDE4_ADD_LIBRARY(kbfxplasmadatasettings SHARED ${libkbfxplasmadatasettingssrc})
	TARGET_LINK_LIBRARIES(kbfxplasmadatasettings
	    kbfxdata
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    ${KDE4_KHTML_LIBS}
	    ${M_LIBRARY}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxplasmadatasettings ${LIB_INSTALL_DIR}/kbfx/plugins)
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxplasmadatasettings DESTINATION ${LIB_INSTALL_DIR}/kbfx/plugins)
INSTALL(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/kbfx/plugins)
