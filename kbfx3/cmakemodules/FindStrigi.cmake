# - Try to find Strigi
# Once done this will define
#
#  STRIGI_FOUND - system has Strigi
#  STRIGI_INCLUDE_DIR - the Strigi include directory
#  STRIGIHTMLGUI_LIBRARY - Link these to use Strigi html gui
#  STRIGICLIENT_LIBRARY - Link to use the Strigi C++ client
#

FIND_PATH(STRIGI_INCLUDE_DIR strigihtmlgui.h
  PATHS
  $ENV{HOME}/include/strigi
  $ENV{HOME}/usr/include/strigi
  $ENV{KDEDIR}/include/strigi
  /opt/kde/include/strigi
  /opt/kde3/include/strigi
  /opt/kde4/include/strigi
  /usr/kde/3.5/include/strigi
  /usr/include/strigi
  /usr/local/include/strigi
  /opt/include/strigi
  ${INCLUDE_SEARCH_PATHES}
)

FIND_LIBRARY(STRIGIHTMLGUI_LIBRARY NAMES strigihtmlgui
  PATHS
  ${LIB_SEARCH_PATHES}
)
FIND_LIBRARY(STRIGICLIENT_LIBRARY NAMES searchclient
  PATHS
  ${LIB_SEARCH_PATHES}
)

IF(STRIGI_INCLUDE_DIR AND STRIGIHTMLGUI_LIBRARY AND STRIGICLIENT_LIBRARY)
   SET(STRIGI_FOUND TRUE)
ENDIF(STRIGI_INCLUDE_DIR AND STRIGIHTMLGUI_LIBRARY AND STRIGICLIENT_LIBRARY)

IF(STRIGI_FOUND)
  IF(NOT Strigi_FIND_QUIETLY)
    MESSAGE(STATUS "Found Strigi: ${STRIGIHTMLGUI_LIBRARY}")
  ENDIF(NOT Strigi_FIND_QUIETLY)
ELSE(STRIGI_FOUND)
  IF(Strigi_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find Strigi! Please download and install Strigi from http://strigi.sf.net")
  ENDIF(Strigi_FIND_REQUIRED)
ENDIF(STRIGI_FOUND)

