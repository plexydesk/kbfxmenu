SET(libkbfxplasmadataplasmoidsrc
    kbfxplasmadatapluginplosmoid.cpp
   )

FILE(GLOB HEADERS *.h)

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${libkbfxplasmadataplasmoidsrc})

	ADD_LIBRARY(kbfxplasmadataplasmoid SHARED ${libkbfxplasmadataplasmoidsrc} )
	SET_TARGET_PROPERTIES(kbfxplasmadataplasmoid
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxplasmadataplasmoid PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxplasmadataplasmoid
	    kbfxdata
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    ${KDE3_KHTML_LIBRARY}
	    ${M_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxplasmadataplasmoid ${LIB_INSTALL_DIR}/kbfx/plugins)
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${libkbfxplasmadataplasmoidsrc})

	KDE4_ADD_LIBRARY(kbfxplasmadataplasmoid SHARED ${libkbfxplasmadataplasmoidsrc} )
	TARGET_LINK_LIBRARIES(kbfxplasmadataplasmoid
	    kbfxdata
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    ${KDE4_KHTML_LIBS}
	    ${M_LIBRARY}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxplasmadataplasmoid ${LIB_INSTALL_DIR}/kbfx/plugins)
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxplasmadataplasmoid DESTINATION ${LIB_INSTALL_DIR}/kbfx/plugins)
INSTALL(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/kbfx/plugins)
