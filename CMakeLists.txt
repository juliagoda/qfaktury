project(qfaktury)
cmake_minimum_required(VERSION 2.4.7)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(QFAKTURY_MAJOR 0)
set(QFAKTURY_MINOR 6)
set(QFAKTURY_REVISION 0)
set(QFAKTURY_VERSION ${QFAKTURY_MAJOR}.${QFAKTURY_MINOR}.${QFAKTURY_REVISION})
set(QT_USE_QTXML TRUE)
set(CMAKE_CXX_FLAGS_DISTRIBUTION "-O3")


find_package(Qt4 REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include(${QT_USE_FILE})
set(qfaktury_SRCS
main.cpp
ConvertAmount.cpp
Faktura.cpp
Kontrahenci.cpp
KontrahenciLista.cpp
Korekta.cpp
Towary.cpp
TowaryLista.cpp
Ustawienia.cpp
Uzytkownik.cpp
ZmienIlosc.cpp
MainWindow.cpp
)

set(qfaktury_UIS
Faktura.ui
KontrahenciLista.ui
Kontrahenci.ui
MainWindow.ui
TowaryLista.ui
Towary.ui
Ustawienia.ui
Uzytkownik.ui
ZmienIlosc.ui
)

set(qfaktury_RCCS
qfaktury.qrc
)

QT4_ADD_RESOURCES(qfaktury_SRCS ${qfaktury_RCCS})
QT4_WRAP_UI(qfaktury_UIS_H ${qfaktury_UIS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
qt4_automoc(${qfaktury_SRCS})

set(WIN32_FLAG "")
if (WIN32) 
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        set(WIN32_FLAG WIN32)
    endif (CMAKE_BUILD_TYPE STREQUAL Release)
endif (WIN32)



add_executable(qfaktury ${WIN32_FLAG} ${qfaktury_SRCS} ${qfaktury_UIS_H} ${qfaktury_RCCS})
target_link_libraries(qfaktury ${QT_LIBRARIES})

INSTALL(TARGETS qfaktury RUNTIME DESTINATION "bin")

if(WIN32)
    FIND_PROGRAM(QT_GUI_DLL NAMES QtGui4.dll)
    FIND_PROGRAM(QT_CORE_DLL NAMES QtCore4.dll)
    FIND_PROGRAM(QT_XML_DLL NAMES QtXml4.dll)
    FIND_PROGRAM(MINGW_DLL NAMES mingwm10.dll)
    SET(QFAKTURY_DLLS ${QT_CORE_DLL} ${QT_GUI_DLL} ${QT_XML_DLL} ${MINGW_DLL})
    MESSAGE("QFAKTURY DLLS: ${QFAKTURY_DLLS}")
    INSTALL(FILES ${QFAKTURY_DLLS} DESTINATION "bin")
endif(WIN32)

INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_NAME "qfaktury")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QFaktury - program do wystawiania faktur")
SET(CPACK_PACKAGE_VENDOR "Rafal Rusin (rafal.rusin@gmail.com)")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR ${QFAKTURY_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${QFAKTURY_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${QFAKTURY_REVISION})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "QFaktury ${QFAKTURY_MAJOR}.${QFAKTURY_MINOR}")
SET(CPACK_NSIS_CONTACT "rafal.rusin@gmail.com")
IF(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/icons/qfaktury_128.png")
    SET(CPACK_NSIS_INSTALLED_ICON_NAME "qfaktury.exe")
    SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} QFaktury")
    SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\qfaktury.sf.net")
    SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\qfaktury.sf.net")
    SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
    SET(CPACK_STRIP_FILES "bin/qfaktury")
    SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "qfaktury" "QFaktury")
INCLUDE(CPack)

SET(DEBIAN_PACKAGE_NAME "qfaktury")
SET(DEBIAN_PACKAGE_VERSION "${QFAKTURY_MAJOR}.${QFAKTURY_MINOR}.${QFAKTURY_REVISION}")
SET(DEBIAN_ARCHITECTURE i386)
SET(DEBIAN_PACKAGE_DEPENDS libqt4-gui)

INCLUDE(UseDebian)
if(DEBIAN_FOUND)
ADD_DEBIAN_TARGETS(qfaktury)
endif(DEBIAN_FOUND)

