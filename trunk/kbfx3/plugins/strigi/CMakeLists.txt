SET(libkbfxstrigiclientsrc
    kbfxstrigiplugin.cpp
   )

FILE(GLOB HEADERS *.h)

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${libkbfxstrigiclientsrc})

	ADD_LIBRARY(kbfxstrigiclient SHARED ${libkbfxstrigiclientsrc})
	SET_TARGET_PROPERTIES(kbfxstrigiclient
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxstrigiclient PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxstrigiclient
	    kbfxdata
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    ${KDE3_KHTML_LIBRARY}
	    ${M_LIBRARY}
	    ${STRIGICLIENT_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxstrigiclient ${LIB_INSTALL_DIR}/kbfx/plugins)
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${libkbfxstrigiclientsrc})

	KDE4_ADD_LIBRARY(kbfxstrigiclient SHARED ${libkbfxstrigiclientsrc})
	TARGET_LINK_LIBRARIES(kbfxstrigiclient
	    kbfxdata
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    ${KDE4_KHTML_LIBS}
	    ${M_LIBRARY}
	    ${STRIGICLIENT_LIBRARY}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxstrigiclient ${LIB_INSTALL_DIR}/kbfx/plugins)
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxstrigiclient DESTINATION ${LIB_INSTALL_DIR}/kbfx/plugins)
INSTALL(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/kbfx/plugins)
