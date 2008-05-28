SET(kbfxconfigappsrc
    main.cpp
    kbfxconfigapp.cpp
    )

SET(kbfxconfigappui
    kbfxthemeinfo.ui
    kbfxconfigdlgbutton.ui
    kbfxconfigdlgmain.ui
    kbfxconfigdlgthemes.ui
    kbfxconfigdlgabout.ui
    kbfxconfigdlgstyle.ui
    kbfxconfigdlgtooltip.ui
    kbfxconfigdlgfonts-old.ui
    kbfxconfigdlgplugins.ui
    kbfxconfigdlglayout.ui
    )

IF (NOT USE_KDE4)
	KDE3_AUTOMOC(${kbfxconfigappsrc})

	KDE3_ADD_UI_FILES(kbfxconfigappsrc ${kbfxconfigappui})

	KDE3_ADD_EXECUTABLE(kbfxconfigapp ${kbfxconfigappsrc})

	TARGET_LINK_LIBRARIES(kbfxconfigapp
	    kbfxdata
	    kbfxcommon
	    ${QT_AND_KDECORE_LIBS}
	    ${KDE3_KIO_LIBRARY}
	    ${KDE3_UI_LIBRARY}
	    )
ELSE (NOT USE_KDE4)
	KDE4_AUTOMOC(${kbfxconfigappsrc})

	KDE4_ADD_UI3_FILES(kbfxconfigappsrc ${kbfxconfigappui})

	KDE4_ADD_EXECUTABLE(kbfxconfigapp ${kbfxconfigappsrc})

	TARGET_LINK_LIBRARIES(kbfxconfigapp
	    kbfxdata
	    kbfxcommon
	    ${KDE4_KDECORE_LIBS}
	    ${KDE4_KIO_LIBS}
	    ${KDE4_KDEUI_LIBS}
	    )
ENDIF (NOT USE_KDE4)

INSTALL(TARGETS kbfxconfigapp
    RUNTIME DESTINATION ${BIN_INSTALL_DIR})

INSTALL(FILES kbfxconfigappui.rc DESTINATION ${DATA_INSTALL_DIR}/kbfxconfigapp)
INSTALL(FILES kbfxconfigapp.desktop kbfx_theme.desktop DESTINATION ${XDG_APPS_DIR})
INSTALL(FILES kbfx_install_theme.desktop kbfx_prepare_theme.desktop
    DESTINATION ${DATA_INSTALL_DIR}/konqueror/servicemenus)
INSTALL(FILES x-kbfxtheme.desktop
    DESTINATION ${MIME_INSTALL_DIR}/application)
