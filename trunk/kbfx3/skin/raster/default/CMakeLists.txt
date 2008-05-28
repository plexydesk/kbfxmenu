FILE(GLOB PNGFILES *.png kbfxlayoutrc kbfxfontrc version-2 )

INSTALL(FILES ${PNGFILES}
    DESTINATION ${DATA_INSTALL_DIR}/kbfx/skins/default)
