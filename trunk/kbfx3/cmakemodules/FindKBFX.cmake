# - Try to find the KBFX package -
# If found the following will be defined
#
#  KBFX_FOUND - KBFX package found on the system
#  KBFX_INCLUDE_DIR - Directory of the KBFX package include files
#  KBFX_LIBRARY - Where libkbfxplasma.so resides
#

FIND_PATH(KBFX_INCLUDE_DIR kbfx/kbfxconfig.h
  PATHS
  ${INCLUDE_SEARCH_PATHES}
)

FIND_LIBRARY(KBFX_LIBRARY NAMES kbfxplasma
  PATHS
  ${LIB_SEARCH_PATHES}
)

IF(KBFX_INCLUDE_DIR AND KBFX_LIBRARY)
   SET(KBFX_FOUND TRUE)
ENDIF(KBFX_INCLUDE_DIR AND KBFX_LIBRARY)

IF(KBFX_FOUND)
  IF(NOT KBFX_FIND_QUIETLY)
    MESSAGE(STATUS "Found KBFX package: ${KBFX_LIBRARY}")
  ENDIF(NOT KBFX_FIND_QUIETLY)
ELSE(KBFX_FOUND)
  IF(KBFX_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find KBFX package! Please download and install KBFX from http://www.kbfx.org")
  ENDIF(KBFX_FIND_REQUIRED)
ENDIF(KBFX_FOUND)

