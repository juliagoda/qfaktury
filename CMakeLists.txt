cmake_minimum_required(VERSION 3.6)
project(qfaktury)

if(POLICY CMP0071)
  cmake_policy(SET CMP0071 NEW)
endif()

set(QT_MIN_VERSION "5.10.0")

# Set project version
set (QFAKTURY_VERSION_MAJOR "0")
set (QFAKTURY_VERSION_MINOR "7")
set (QFAKTURY_VERSION_MICRO "2")
set (QFAKTURY_APPLICATIONS_VERSION "${QFAKTURY_VERSION_MAJOR}.${QFAKTURY_VERSION_MINOR}.${QFAKTURY_VERSION_MICRO}")

find_package(ECM 5.43.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" "${CMAKE_ROOT}/Modules")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

message(STATUS "${CMAKE_MODULE_PATH}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden -Werror -Wall -Wextra -Wno-unused-parameter -pedantic -Wno-reorder -std=c++0x")
find_package( Qt5 REQUIRED COMPONENTS Gui Core Widgets PrintSupport Xml XmlPatterns Network )


option(FEDORA "Check if this Fedora" OFF)
option(QUAZIP_FOUND "Check if QuaZipn is installed and accessible" OFF)


find_package(Fedora)

find_package(QuaZip5)


if(FEDORA)
  add_definitions(-DFEDORA_FOUND)
  message("It's Fedora. It's possible to run beesu instead of gksu")
endif()
if(QUAZIP_FOUND)
  add_definitions(-DQUAZIP)
  message("EN: QuaZip has been found. It's possible to create backup \nPL: Znaleziono QuaZip. Jest możliwe tworzenie kopii zapasowych")
else()
  message("EN: QuaZip hasn't been found in FindQuaZip5.cmake. It's not possible to create backup. \nPL: Brak biblioteki dla QuaZip. Tworzenie kopii zapasowych zablokowane")
endif()


if(NOT QUAZIP_FOUND)
    set(QUAZIP_INCLUDE_DIR "")
    set(ZLIB_INCLUDE_DIR "")
    set(QUAZIP_INCLUDE_DIRS "")
    set(QUAZIP_LIBRARIES "")
    find_path(QUAZIP_INCLUDE_DIR NAMES quazipdir.h JlCompress.h PATH_SUFFIXES quazip5)
    find_path(ZLIB_INCLUDE_DIR NAME zlib.h)
    set(QUAZIP_INCLUDE_DIRS ${QUAZIP_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR}) # QUAZIP_INCLUDE_DIRS contains includes for zlib and quazip in FindQuaZip5.cmake
    find_library(QUAZIP_LIBRARIES quazip5)
    if(NOT QUAZIP_INCLUDE_DIRS OR NOT QUAZIP_LIBRARIES)
        message("NEXT STEP OF QUAZIP SEARCHING \nEN: Could NOT find optional library quazip. PL: Nie można znaleźć biblioteki quazip w kolejnym kroku. Możliwość tworzenia backup jest zablokowana.")
    else()
        message("NEXT STEP OF QUAZIP SEARCHING \nEN: Found optional library quazip. PL: Znaleziono opcjonalną bibliotekę quazip. Możliwe tworzenie kopii zapasowych")
    endif()
endif()


add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

set( SOURCES    
     src/xmldatalayer.cpp
     src/buyerdata.cpp
     src/custompaymdata.cpp
     src/custompayment.cpp
     src/correctgross.cpp
     src/goodsgrosslist.cpp
     src/bill.cpp
     src/invoicegross.cpp
     src/duplicate.cpp
     src/convertamount.cpp
     src/invoice.cpp
     src/buyers.cpp
     src/buyerslist.cpp
     src/correction.cpp
     src/main.cpp 
     src/mainwindow.cpp
     src/goods.cpp
     src/goodslist.cpp
     src/setting.cpp
     src/user.cpp
     src/changeamount.cpp
     src/validations.cpp
     src/invoicerr.cpp
     src/SimpleSmtp_SSL_QT5/smtp_attachements/emailwindow.cpp
     src/SimpleSmtp_SSL_QT5/smtp_attachements/smtp.cpp
     src/send.cpp
     src/owncalendar.cpp
     src/warehouse.cpp
     src/deliverynote.cpp
     src/goodsissuednotes.cpp
     src/organizer.cpp
     src/saftfile.cpp
     src/saftfileoutput.cpp
     src/runguard.cpp
     src/backup.cpp
     src/csvexport.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${QUAZIP_INCLUDE_DIRS}
    src/SimpleSmtp_SSL_QT5/smtp_attachements
)


qt5_wrap_ui( UIS_HDRS
    ui/setting.ui
    ui/user.ui
    ui/mainwindow.ui
    ui/invoice.ui
    ui/goodslist.ui
    ui/goods.ui
    ui/custompaymentdialog.ui
    ui/changeamount.ui
    ui/buyers.ui
    ui/buyerslist.ui
    ui/organizer.ui
    ui/saftfile.ui
    ui/backup.ui
    ui/csvexport.ui
    src/SimpleSmtp_SSL_QT5/smtp_attachements/emailwindow.ui
)


QT5_ADD_RESOURCES(RESOURCES qfaktury.qrc)


add_executable(qfaktury ${SOURCES} ${UIS_HDRS} ${RESOURCES})

target_link_libraries (qfaktury
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Xml
    Qt5::XmlPatterns
    Qt5::Network 
    ${QUAZIP_LIBRARIES}
    )


    SET(QFAKTURY_PATH "/usr/share/qfaktury")

    install(TARGETS qfaktury DESTINATION /usr/bin)
    install(DIRECTORY icons DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY schemas DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY templates DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY docs DESTINATION /usr/share/doc/qfaktury)
    install(FILES QFaktury.desktop DESTINATION /usr/share/applications)
    install(DIRECTORY src DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY ui DESTINATION ${QFAKTURY_PATH})

