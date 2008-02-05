project(qfaktury)
cmake_minimum_required(VERSION 2.4.7)
set(QFAKTURY_MAJOR 0)
set(QFAKTURY_MINOR 5)
set(QFAKTURY_REVISION 0-alfa)
set(QFAKTURY_VERSION ${QFAKTURY_MAJOR}.${QFAKTURY_MINOR}.${QFAKTURY_REVISION})
set(QT_USE_QTXML TRUE)
find_package(Qt4 REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include(${QT_USE_FILE})
set(qfaktury_SRCS
Faktura.cpp
Kontrahenci.cpp
KontrahenciLista.cpp
Korekta.cpp
main.cpp
Rounding.cpp
slownie.cpp
Towary.cpp
TowaryLista.cpp
Ustawienia.cpp
Uzytkownik.cpp
ZmienIlosc.cpp
Podglad.cpp
MainWindow.cpp
)

set(qfaktury_UIS
Faktura.ui
KontrahenciLista.ui
Kontrahenci.ui
Korekta.ui
MainWindow.ui
TowaryLista.ui
Towary.ui
Ustawienia.ui
Uzytkownik.ui
ZmienIlosc.ui
Podglad.ui
)


QT4_WRAP_UI(qfaktury_UIS_H ${qfaktury_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
qt4_automoc(${qfaktury_SRCS})
add_executable(qfaktury ${qfaktury_SRCS} ${qfaktury_UIS_H})
target_link_libraries(qfaktury ${QT_LIBRARIES})

INSTALL(TARGETS qfaktury DESTINATION "")


#SET(CPACK_PACKAGE_NAME "qfaktury")
#SET(CPACK_PACKAGE_VERSION_MAJOR ${QFAKTURY_MAJOR})
#SET(CPACK_PACKAGE_VERSION_MINOR ${QFAKTURY_MINOR})
#SET(CPACK_PACKAGE_VERSION_PATCH ${QFAKTURY_REVISION})
#include(CPack)


INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_NAME "qfaktury")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QFaktury - program do wystawiania faktur")
SET(CPACK_PACKAGE_VENDOR "Rafal Rusin (rafal.rusin@gmail.com)")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${QFAKTURY_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${QFAKTURY_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${QFAKTURY_REVISION})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  SET(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_STRIP_FILES "bin/MyExecutable")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")
INCLUDE(CPack)

