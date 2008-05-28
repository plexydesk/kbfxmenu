# Find KDE4 and provide all necessary variables and macros to compile software for it.
# It looks for KDE 4 in the following directories in the given order:
# - CMAKE_INSTALL_PREFIX
# - KDEDIR
# - /opt/kde4
# - /opt/kde
#
# Please look in FindKDE4Internal.cmake and KDE4Macros.cmake for more information.
# They are installed with the KDE 4 libraries in $KDEDIR/share/apps/cmake/modules/.
#
# Author: Alexander Neundorf <neundorf@kde.org>
# Modified by PhobosK <phobosk@mail.kbfx.org>

# For KDE4 kde-config has been renamed to kde4-config
FIND_PROGRAM(KDE4_KDECONFIG_EXECUTABLE NAMES kde4-config
   PATHS
   ${BIN_SEARCH_PATHES}
   NO_DEFAULT_PATH)

IF (NOT KDE4_KDECONFIG_EXECUTABLE)
      FIND_PROGRAM(KDE4_KDECONFIG_EXECUTABLE NAMES kde4-config )
ENDIF (NOT KDE4_KDECONFIG_EXECUTABLE)

IF (KDE4_KDECONFIG_EXECUTABLE)
      IF (KDE4_FIND_QUIETLY)
         SET(_quiet QUIET)
      ENDIF (KDE4_FIND_QUIETLY)

      IF (KDE4_FIND_REQUIRED)
         SET(_req REQUIRED)
      ENDIF (KDE4_FIND_REQUIRED)
      
      # use FindKDE4Internal.cmake to do the rest
      FIND_PACKAGE(KDE4Internal ${_req} ${_quiet})
ELSE (KDE4_KDECONFIG_EXECUTABLE)
      IF (KDE4_FIND_REQUIRED)
         MESSAGE(FATAL_ERROR "ERROR: Could not find KDE4 kde4-config")
      ENDIF (KDE4_FIND_REQUIRED)
ENDIF (KDE4_KDECONFIG_EXECUTABLE)

