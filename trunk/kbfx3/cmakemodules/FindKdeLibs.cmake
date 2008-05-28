#INCLUDE(FindQt3)
#INCLUDE(FindQt)
#INCLUDE(FindKDE3)
INCLUDE(kdesvnMacros)
INCLUDE(KDE3Macros)

FILE(GLOB GLOB_PATHS_INCLUDE /usr/lib*/qt-3*/include/)
FIND_PROGRAM(PKG_CONFIG NAMES pkg-config)
EXECUTE_PROCESS(COMMAND ${PKG_CONFIG} "--variable=prefix" "qt-mt"
	OUTPUT_VARIABLE _qt_mt_path
	ERROR_QUIET
	OUTPUT_STRIP_TRAILING_WHITESPACE)
SET(QT_MT_PATH ${_qt_mt_path} CACHE STRING "QT Path" FORCE)
FIND_PATH(QT_INCLUDE_DIR_PLUS qt.h
	${GLOB_PATHS_INCLUDE}
	${QT_MT_PATH}/include)
IF (NOT QT_INCLUDE_DIR)
	SET(QT_INCLUDE_DIR ${QT_INCLUDE_DIR_PLUS})
ENDIF (NOT QT_INCLUDE_DIR)

FIND_PROGRAM(CMAKE_UNAME uname ${BIN_SEARCH_PATHES})
IF(CMAKE_UNAME)
	EXECUTE_PROCESS(COMMAND ${CMAKE_UNAME} "-m"
		OUTPUT_VARIABLE CMAKE_SYSTEM_PROCESSOR
		ERROR_QUIET
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	IF("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "64")
		SET(LIB_SUFFIX "64" CACHE STRING "Define suffix of directory name (32/64)" FORCE)
	ELSE("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "64")
		SET(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" FORCE)
	ENDIF("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "64")
ENDIF(CMAKE_UNAME)

SET(INCLUDE_SEARCH_PATHES
    ${INCLUDE_SEARCH_PATHES}
    ${KDE3_INCLUDE_DIRS})

SET(LIB_SEARCH_PATHES
    ${LIB_SEARCH_PATHES}
    ${KDE3_LIB_DIR})

IF (LIB_SUFFIX)
    SET(LIB_SEARCH_PATHES
        $ENV{KDEDIR}/lib${LIB_SUFFIX}
	$ENV{HOME}/lib${LIB_SUFFIX}
	$ENV{HOME}/usr/lib${LIB_SUFFIX}
	/opt/lib${LIB_SUFFIX}
        /opt/kde/lib${LIB_SUFFIX}
        /opt/kde3/lib${LIB_SUFFIX}
        /usr/lib${LIB_SUFFIX}
	/usr/kde/3.5/lib${LIB_SUFFIX}
        /usr/local/lib${LIB_SUFFIX}
        ${LIB_SEARCH_PATHES}
        )
ENDIF (LIB_SUFFIX)



FIND_LIBRARY(M_LIBRARY NAMES m
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_LIBRARY(KDE3_UI_LIBRARY NAMES kdeui
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_LIBRARY(KDE3_PART_LIBRARY NAMES kparts
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_LIBRARY(KDE3_KIO_LIBRARY NAMES kio
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_LIBRARY(KDE3_KHTML_LIBRARY NAMES khtml
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_LIBRARY(KDE3_DCOP_LIBRARY NAMES DCOP
  PATHS
  ${LIB_SEARCH_PATHES}
)

FIND_PROGRAM(KDE3_KDECONFIG_EXECUTABLE NAME kde-config
    PATHS ${BIN_SEARCH_PATHES})

FIND_PROGRAM(MSGFMT
    NAMES gmsgfmt msgfmt
    PATHS ${BIN_SEARCH_PATHES})


FIND_PROGRAM(STRIP
    NAMES strip
    PATHS ${BIN_SEARCH_PATHES})

FIND_PROGRAM(KDE3_MEINPROC_EXECUTABLE NAME meinproc
    PATHS ${BIN_SEARCH_PATHES})

IF(KDE3_MEINPROC_EXECUTABLE)
    MESSAGE(STATUS "Found meinproc: ${KDE3_MEINPROC_EXECUTABLE}")
ELSE(KDE3_MEINPROC_EXECUTABLE)
    MESSAGE(FATAL_ERROR "Could NOT find meinproc program!")
ENDIF(KDE3_MEINPROC_EXECUTABLE)

IF(MSGFMT)
    EXECUTE_PROCESS(COMMAND ${MSGFMT} "--version"
    OUTPUT_VARIABLE _msgout
	ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)
    STRING(REGEX MATCH "GNU[\t ]gettext" _isgnu "${_msgout}")
    IF (NOT _isgnu)
        MESSAGE(STATUS "No gnu msgfmt found!")
        SET(MSGFMT ":" CACHE STRING "Msgfmt program")
    ELSE(NOT _isgnu)
        MESSAGE(STATUS "Found gnu msgfmt: ${MSGFMT}")
    ENDIF (NOT _isgnu)
ELSE(MSGFMT)
    SET(MSGFMT ":" CACHE STRING "Msgfmt program")
    MESSAGE( FATAL_ERROR "Could NOT find msgfmt program")
ENDIF(MSGFMT)

EXECUTE_PROCESS(COMMAND ${KDE3_KDECONFIG_EXECUTABLE} "--prefix"
	COMMAND xargs "echo" "-n"
	OUTPUT_VARIABLE _kde_prefix_path
	ERROR_QUIET
	OUTPUT_STRIP_TRAILING_WHITESPACE)
SET(KDE_HTML_COMMON_PATH ${_kde_prefix_path}/share/doc/HTML/en/common CACHE STRING "KDE HTML common Path" FORCE)

# 'cause my own defines were not good I take them from kde4 trunk
#add some KDE specific stuff
SET(SHARE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/share CACHE PATH "Base directory for files which go to share/" FORCE)
SET(EXEC_INSTALL_PREFIX  ${CMAKE_INSTALL_PREFIX}       CACHE PATH  "Base directory for executables and libraries" FORCE)
#
## the following are directories where stuff will be installed to
SET(BIN_INSTALL_DIR          "${EXEC_INSTALL_PREFIX}/bin"                  CACHE PATH "The kde bin install dir (default prefix/bin)" FORCE)
SET(SBIN_INSTALL_DIR         "${EXEC_INSTALL_PREFIX}/sbin"                 CACHE PATH "The kde sbin install dir (default prefix/sbin)" FORCE)
SET(LIB_INSTALL_DIR          "${EXEC_INSTALL_PREFIX}/lib${LIB_SUFFIX}"     CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed (default is /lib${LIB_SUFFIX})" FORCE)
SET(LIBEXEC_INSTALL_DIR      "${LIB_INSTALL_DIR}/kde3/libexec"             CACHE PATH "The subdirectory relative to the install prefix where libraries will be installed (default is /lib/kde3/libexec)" FORCE)
SET(PLUGIN_INSTALL_DIR       "${LIB_INSTALL_DIR}/kde3"                     CACHE PATH "The subdirectory relative to the install prefix where plugins will be installed (default is ${LIB_INSTALL_DIR}/kde3)" FORCE)
SET(INCLUDE_INSTALL_DIR      "${CMAKE_INSTALL_PREFIX}/include"             CACHE PATH "The subdirectory to the header prefix" FORCE)
SET(CONFIG_INSTALL_DIR       "${SHARE_INSTALL_PREFIX}/config"              CACHE PATH "The config file install dir" FORCE)
SET(DATA_INSTALL_DIR         "${SHARE_INSTALL_PREFIX}/apps"                CACHE PATH "The parent directory where applications can install their data" FORCE)
SET(HTML_INSTALL_DIR         "${SHARE_INSTALL_PREFIX}/doc/HTML"            CACHE PATH "The HTML install dir for documentation"  FORCE)
SET(ICON_INSTALL_DIR         "${SHARE_INSTALL_PREFIX}/icons"               CACHE PATH "The icon install dir (default prefix/share/icons/)" FORCE)
SET(KCFG_INSTALL_DIR         "${SHARE_INSTALL_PREFIX}/config.kcfg"         CACHE PATH "The install dir for kconfig files" FORCE)
SET(LOCALE_INSTALL_DIR       "${SHARE_INSTALL_PREFIX}/locale"              CACHE PATH "The install dir for translations" FORCE)
SET(MIME_INSTALL_DIR         "${SHARE_INSTALL_PREFIX}/mimelnk"             CACHE PATH "The install dir for the mimetype desktop files" FORCE)
SET(SERVICES_INSTALL_DIR     "${SHARE_INSTALL_PREFIX}/services"            CACHE PATH "The install dir for service (desktop, protocol, ...) files" FORCE)
SET(SERVICETYPES_INSTALL_DIR "${SHARE_INSTALL_PREFIX}/servicetypes"        CACHE PATH "The install dir for servicestypes desktop files" FORCE)
SET(SOUND_INSTALL_DIR        "${SHARE_INSTALL_PREFIX}/sounds"              CACHE PATH "The install dir for sound files" FORCE)
SET(TEMPLATES_INSTALL_DIR    "${SHARE_INSTALL_PREFIX}/templates"           CACHE PATH "The install dir for templates (Create new file...)" FORCE)
SET(WALLPAPER_INSTALL_DIR    "${SHARE_INSTALL_PREFIX}/wallpapers"          CACHE PATH "The install dir for wallpapers" FORCE)
SET(KCONF_UPDATE_INSTALL_DIR "${DATA_INSTALL_DIR}/kconf_update"            CACHE PATH "The kconf_update install dir" FORCE)
# this one shouldn't be used anymore
SET(APPLNK_INSTALL_DIR       "${SHARE_INSTALL_PREFIX}/applnk"              CACHE PATH "Is this still used ?" FORCE)
SET(AUTOSTART_INSTALL_DIR    "${SHARE_INSTALL_PREFIX}/autostart"           CACHE PATH "The install dir for autostart files" FORCE)
SET(XDG_APPS_DIR             "${SHARE_INSTALL_PREFIX}/applications/kde"    CACHE PATH "The XDG apps dir" FORCE)
SET(XDG_DIRECTORY_DIR        "${SHARE_INSTALL_PREFIX}/desktop-directories" CACHE PATH "The XDG directory" FORCE)
SET(SYSCONF_INSTALL_DIR      "${CMAKE_INSTALL_PREFIX}/etc"                 CACHE PATH "The kde sysconfig install dir (default/etc)" FORCE)
SET(MAN_INSTALL_DIR          "${SHARE_INSTALL_PREFIX}/man"                 CACHE PATH "The kde man install dir (default prefix/share/man/)" FORCE)
SET(INFO_INSTALL_DIR         "${CMAKE_INSTALL_PREFIX}/info"                CACHE PATH "The kde info install dir (default prefix/info)" FORCE)

# linker flags - must get checked
SET(LINK_NO_UNDEFINED "")
SET(lundef "-Wl,--no-undefined")
KDESVN_CHECK_LINK_FLAG(${lundef} _NO_UNDEFINED)
IF (_NO_UNDEFINED)
    SET(LINK_NO_UNDEFINED "${lundef}")
ENDIF (_NO_UNDEFINED)

SET(lundef "-Wl,--allow-shlib-undefined")
KDESVN_CHECK_LINK_FLAG(${lundef} _ALLOW_SHLIB)
IF (_ALLOW_SHLIB)
    SET(LINK_NO_UNDEFINED "${LINK_NO_UNDEFINED} ${lundef}")
ENDIF (_ALLOW_SHLIB)


# own macros
MACRO(KDESVN_INSTALL_ICONS _theme)

   FILE(GLOB _icons *.png)
   FILE(GLOB _svg *svgz)
   SET(_icons ${_icons} ${_svg})
   FOREACH(_current_ICON ${_icons} )
      GET_FILENAME_COMPONENT(_ctype ${_current_ICON} EXT)

	  IF (${_ctype} STREQUAL ".png")
      STRING(REGEX REPLACE "^.*/[a-zA-Z]+([0-9]+)\\-([a-z]+)\\-(.+\\.png)$" "\\1" _size "${_current_ICON}")
      STRING(REGEX REPLACE "^.*/[a-zA-Z]+([0-9]+)\\-([a-z]+)\\-(.+\\.png)$" "\\2" _group "${_current_ICON}")
      STRING(REGEX REPLACE "^.*/[a-zA-Z]+([0-9]+)\\-([a-z]+)\\-(.+\\.png)$" "\\3" _name "${_current_ICON}")
	  SET(_sizestring "${_size}x${_size}")
	  ENDIF (${_ctype} STREQUAL ".png")

	  IF (${_ctype} STREQUAL ".svgz")
        STRING(REGEX REPLACE "^.*/[a-zA-Z]+\\-([a-z]+)\\-(.+\\.svgz)$" "\\1" _group "${_current_ICON}")
        STRING(REGEX REPLACE "^.*/[a-zA-Z]+\\-([a-z]+)\\-(.+\\.svgz)$" "\\2" _name "${_current_ICON}")
		SET(_sizestring "scalable")
	  ENDIF (${_ctype} STREQUAL ".svgz")

      SET(_icon_GROUP "actions")

      IF(${_group} STREQUAL "mime")
         SET(_icon_GROUP  "mimetypes")
      ENDIF(${_group} STREQUAL "mime")

      IF(${_group} STREQUAL "filesys")
         SET(_icon_GROUP  "filesystems")
      ENDIF(${_group} STREQUAL "filesys")

      IF(${_group} STREQUAL "device")
         SET(_icon_GROUP  "devices")
      ENDIF(${_group} STREQUAL "device")

      IF(${_group} STREQUAL "app")
         SET(_icon_GROUP  "apps")
      ENDIF(${_group} STREQUAL "app")

      IF(${_group} STREQUAL "action")
         SET(_icon_GROUP  "actions")
      ENDIF(${_group} STREQUAL "action")

      #message(STATUS "icon: ${_current_ICON} size: ${_sizestring} group: ${_group} name: ${_name}" )
      SET(_ICON_INSTALL_DIR ${ICON_INSTALL_DIR}/${_theme}/${_sizestring}/${_icon_GROUP})

      INSTALL(FILES ${_current_ICON} DESTINATION ${_ICON_INSTALL_DIR} RENAME ${_name})

   ENDFOREACH (_current_ICON)
ENDMACRO(KDESVN_INSTALL_ICONS)

MACRO(ADD_POFILES packagename)
    SET(_gmofiles)
    FILE(GLOB _pofiles *.po)

    FOREACH(_current_po ${_pofiles})
        GET_FILENAME_COMPONENT(_name ${_current_po} NAME_WE)
        STRING(REGEX REPLACE "^.*/([a-zA-Z]+)(\\.po)" "\\1" _lang "${_current_po}")
        SET(_gmofile "${CMAKE_CURRENT_BINARY_DIR}/${_name}.gmo")
        ADD_CUSTOM_COMMAND(OUTPUT ${_gmofile}
            COMMAND ${MSGFMT}
            ARGS "-o" "${_gmofile}" "${_current_po}"
            DEPENDS ${_current_po}
            )
        SET(_gmofiles ${_gmofiles} ${_gmofile})
        INSTALL(FILES ${_gmofile}
            DESTINATION ${LOCALE_INSTALL_DIR}/${_lang}/LC_MESSAGES
            RENAME ${packagename}.mo)
    ENDFOREACH(_current_po ${_pofiles})

    ADD_CUSTOM_TARGET(translations ALL
        DEPENDS ${_gmofiles})

ENDMACRO(ADD_POFILES)


# KDE3_CREATE_HANDBOOK( docbookfile )
#   Create the handbook from the docbookfile (using meinproc)
MACRO (KDE3_CREATE_HANDBOOK _docbook )
   GET_FILENAME_COMPONENT(_tmp_src_FILE ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
   GET_FILENAME_COMPONENT(_tmp_bin_FILE ${CMAKE_CURRENT_BINARY_DIR} ABSOLUTE)

   IF(EXISTS ${_tmp_src_FILE}/${_docbook})
     get_filename_component(_input  ${_tmp_src_FILE}/${_docbook} ABSOLUTE)
   ENDIF(EXISTS ${_tmp_src_FILE}/${_docbook})
   IF(EXISTS ${_tmp_bin_FILE}/${_docbook})
     get_filename_component(_input  ${_tmp_bin_FILE}/${_docbook} ABSOLUTE)
   ENDIF(EXISTS ${_tmp_bin_FILE}/${_docbook})

   SET(_doc ${CMAKE_CURRENT_BINARY_DIR}/index.cache.bz2)
   ADD_CUSTOM_COMMAND(OUTPUT ${_doc}
      COMMAND ${KDE3_MEINPROC_EXECUTABLE} --check --cache ${_doc} ${_input}
      DEPENDS ${_input} ${KDE3_MEINPROC_EXECUTABLE}
   )
   ADD_CUSTOM_TARGET(handbook ALL DEPENDS ${_doc})
ENDMACRO (KDE3_CREATE_HANDBOOK)


# KDE3_INSTALL_HANDBOOK()
#   Install the handbook documentation
MACRO (KDE3_INSTALL_HANDBOOK _appname )
   GET_FILENAME_COMPONENT(_tmp_src_FILE ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
   GET_FILENAME_COMPONENT(_tmp_bin_FILE ${CMAKE_CURRENT_BINARY_DIR} ABSOLUTE)
   GET_FILENAME_COMPONENT(_basename ${_tmp_src_FILE} NAME_WE)
   SET( dirname ${_basename}/${_appname})

   FILE(GLOB _books_bin ${_tmp_bin_FILE}/*.docbook)
   FILE(GLOB _images_bin ${_tmp_bin_FILE}/*.png)
   FILE(GLOB _books_src ${_tmp_src_FILE}/*.docbook)
   FILE(GLOB _images_src ${_tmp_src_FILE}/*.png)

   INSTALL( FILES ${CMAKE_CURRENT_BINARY_DIR}/index.cache.bz2 ${_books_src} ${_books_bin} ${_images_src} ${_images_bin}
   			DESTINATION ${HTML_INSTALL_DIR}/${dirname} )

    INSTALL( CODE "EXECUTE_PROCESS ( COMMAND /bin/ln -s \"${KDE_HTML_COMMON_PATH}\" \"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\" ERROR_QUIET )" )
    INSTALL( CODE "MESSAGE(STATUS \"Installing $ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\")" )
    INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"IF(EXISTS \\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\\\")\\n\")" )
    INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"MESSAGE(STATUS \\\"Uninstalling \\\\\\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\\\\\\\"\\\")\\n\")" )
    INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"ENDIF(EXISTS \\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\\\")\\n\")" )
    INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"FILE(REMOVE \\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/common\\\")\\n\")" )

   # Specific for KBFX code - remove for other installs
   FILE(GLOB _docbook_PNGFILES ${CMAKE_SOURCE_DIR}/skin/raster/default/*.png)
   FOREACH(_p ${_docbook_PNGFILES})
      GET_FILENAME_COMPONENT(_png_name ${_p} NAME)
      INSTALL( CODE "EXECUTE_PROCESS ( COMMAND /bin/ln -s \"${DATA_INSTALL_DIR}/kbfx/skins/default/${_png_name}\" \"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}\" ERROR_QUIET )" )
      INSTALL( CODE "MESSAGE(STATUS \"Installing $ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/${_png_name}\")" )
      INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"MESSAGE(STATUS \\\"Uninstalling \\\\\\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/${_png_name}\\\\\\\"\\\")\\n\")" )
      INSTALL( CODE "FILE(APPEND ${CMAKE_BINARY_DIR}/uninstall_plus.cmake \"FILE(REMOVE \\\"$ENV{DESTDIR}${HTML_INSTALL_DIR}/${dirname}/${_png_name}\\\")\\n\")" )
   ENDFOREACH(_p)
   # End of specific for KBFX code
ENDMACRO (KDE3_INSTALL_HANDBOOK )

