SET(libkbfxdatasrc
	kbfxdatagroup.cpp
	kbfxdatagrouplist.cpp
	kbfxdatasource.cpp
	kbfxdatastack.cpp
	kbfxplasmadataplugin.cpp
	kbfxplasmapluginloader.cpp
	kbfxplugin.cpp
	)

FILE(GLOB HEADERS *.h)

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${libkbfxdatasrc})

	ADD_LIBRARY(kbfxdata SHARED ${libkbfxdatasrc})
	SET_TARGET_PROPERTIES(kbfxdata
		PROPERTIES
		COMPILE_FLAGS ${CMAKE_SHARED_LIBRARY_CXX_FLAGS})
	# SET_TARGET_PROPERTIES(kbfxdata PROPERTIES
	#     SOVERSION ${LIB_MAJOR}
	#     VERSION ${APPLICATION_VERSION})
	TARGET_LINK_LIBRARIES(kbfxdata
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    ${KDE3_KHTML_LIBRARY}
	    ${M_LIBRARY}
	    )

	KDE3_INSTALL_LIBTOOL_FILE(kbfxdata ${LIB_INSTALL_DIR})
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${libkbfxdatasrc})

	KDE4_ADD_LIBRARY(kbfxdata SHARED ${libkbfxdatasrc})
	TARGET_LINK_LIBRARIES(kbfxdata
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    ${KDE4_KHTML_LIBS}
	    ${M_LIBRARY}
	    )

	KDE4_INSTALL_LIBTOOL_FILE(kbfxdata ${LIB_INSTALL_DIR})
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxdata DESTINATION ${LIB_INSTALL_DIR})
INSTALL(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/kbfx/data)
