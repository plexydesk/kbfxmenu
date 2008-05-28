SET(libkbfxcommonsrc
	kbfxkiodownload.cpp
        kbfxpixmaplabel.cpp
	kbfxconfig.cpp
	kbfxpushbutton.cpp
	kbfxthemesdata.cpp
	kbfxfontchooser.cpp
	kbfxplasmapixmapprovider.cpp
	)

FILE(GLOB HEADERS *.h)

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${libkbfxcommonsrc})

	ADD_LIBRARY(kbfxcommon SHARED ${libkbfxcommonsrc})
	SET_TARGET_PROPERTIES(kbfxcommon
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxcommon PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxcommon
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    ${KDE3_KHTML_LIBRARY}
	    ${M_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxcommon ${LIB_INSTALL_DIR})
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${libkbfxcommonsrc})

	KDE4_ADD_LIBRARY(kbfxcommon SHARED ${libkbfxcommonsrc})
	TARGET_LINK_LIBRARIES(kbfxcommon
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    ${KDE4_KHTML_LIBS}
	    ${M_LIBRARY}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxcommon ${LIB_INSTALL_DIR})
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxcommon DESTINATION ${LIB_INSTALL_DIR})
INSTALL(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/kbfx/common)
