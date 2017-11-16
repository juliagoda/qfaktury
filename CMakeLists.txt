project(qfaktury)

cmake_minimum_required(VERSION 2.8.12)
set(QT_MIN_VERSION "5.0.0")

# Set project version
set (QFAKTURY_VERSION_MAJOR "0")
set (QFAKTURY_VERSION_MINOR "7")
set (QFAKTURY_VERSION_MICRO "1")
set (QFAKTURY_APPLICATIONS_VERSION "${QFAKTURY_VERSION_MAJOR}.${QFAKTURY_VERSION_MINOR}.${QFAKTURY_VERSION_MICRO}")

find_package(ECM 1.7.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")


set(QFAKTURY_PATH "/usr/share/qfaktury")

set(FEDORA 0)

include(FindFedora.cmake)

add_definitions ( -D_IF_FEDORA=FEDORA )



message(STATUS "${CMAKE_MODULE_PATH}")


find_path(ZLIB_INCLUDE_DIR NAMES zlib.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
   PATH_SUFFIXES zlib
)

find_path(ZLIB_INCLUDE_DIR_2 NAMES zlib.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
)


if(ZLIB_INCLUDE_DIR OR ZLIB_INCLUDE_DIR_2)
   set(ZLIB_FOUND TRUE)
else()
   set(ZLIB_FOUND FALSE)
   message(FATAL_ERROR "EN: Could NOT find required package zlib. PL: Nie można znaleźć pakietu zlib. Zainstaluj pakiet zlib")
endif()



find_path(QUAZIP_INCLUDE_DIR NAMES JlCompress.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
   PATH_SUFFIXES quazip5
)

find_library(QUAZIP_LIBRARY NAMES quazip5
    PATHS
    ~/usr/lib
   /opt/local/lib
   /usr/lib
   /usr/lib64
   /usr/local/lib64
   /usr/local/lib
)

find_path(QUAZIP_INCLUDE_DIR_2 NAMES JlCompress.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
   PATH_SUFFIXES quazip
)

find_library(QUAZIP_LIBRARY_2 NAMES quazip
    PATHS
    ~/usr/lib
   /opt/local/lib
   /usr/lib
   /usr/lib64
   /usr/local/lib64
   /usr/local/lib
)


link_directories(/usr/local/lib /usr/lib /usr/lib64 /usr/local/lib64 ~/usr/lib)


if((QUAZIP_INCLUDE_DIR OR QUAZIP_INCLUDE_DIR_2)  AND (QUAZIP_LIBRARY OR QUAZIP_LIBRARY_2))
   set(QUAZIP_FOUND TRUE)
else()
   set(QUAZIP_FOUND FALSE)
   message(FATAL_ERROR "EN: Could NOT find required package quazip. PL: Nie można znaleźć pakietu quazip. Zainstaluj pakiet quazip")
endif()


find_package( Qt5 REQUIRED COMPONENTS Gui Core Widgets PrintSupport Xml WebEngineWidgets Network )


add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

set( SOURCES    
     src/XmlDataLayer.cpp 
     src/BuyerData.cpp 
     src/CustomPaymData.cpp 
     src/CustomPayment.cpp 
     src/CorrectGross.cpp 
     src/GoodsGrossList.cpp 
     src/Bill.cpp 
     src/InvoiceGross.cpp 
     src/Duplicate.cpp 
     src/ConvertAmount.cpp 
     src/Invoice.cpp 
     src/Buyers.cpp 
     src/BuyersList.cpp 
     src/Correction.cpp 
     src/main.cpp 
     src/MainWindow.cpp 
     src/Goods.cpp 
     src/GoodsList.cpp 
     src/Setting.cpp 
     src/User.cpp 
     src/ChangeAmount.cpp 
     src/Validations.cpp 
     src/InvoiceRR.cpp 
    src/SimpleSmtp_SSL_QT5/smtp_attachements/mainwindow.cpp
    src/SimpleSmtp_SSL_QT5/smtp_attachements/smtp.cpp
     src/Send.cpp 
     src/OwnCalendar.cpp 
     src/Warehouse.cpp 
     src/DeliveryNote.cpp 
     src/GoodsIssuedNotes.cpp
)

include_directories(
    src
    src/SimpleSmtp_SSL_QT5/smtp_attachements
    ui
    templates
    icons
    docs
    ${CMAKE_CURRENT_BINARY_DIR}
    
)

if (QUAZIP_INCLUDE_DIR)
include_directories(
    ${QUAZIP_INCLUDE_DIR}
    
)

endif()

if (QUAZIP_INCLUDE_DIR_2)
include_directories(
    ${QUAZIP_INCLUDE_DIR_2}
    
)

endif()

qt5_wrap_ui( UIS_HDRS
    ui/Setting.ui
    ui/User.ui
    ui/MainWindow.ui
    ui/Invoice.ui
    ui/GoodsList.ui
    ui/Goods.ui
    ui/CustomPaymentDialog.ui
    ui/ChangeAmount.ui
    ui/Buyers.ui
    ui/BuyersList.ui
    src/SimpleSmtp_SSL_QT5/smtp_attachements/mainwindow.ui
)


QT5_ADD_RESOURCES(RESOURCES qfaktury.qrc)


add_executable(qfaktury ${SOURCES} ${UIS_HDRS} ${RESOURCES})

if (QUAZIP_LIBRARY)
target_link_libraries (qfaktury
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Xml
    Qt5::WebEngineWidgets
    Qt5::Network 
    quazip5
    )
endif()
if (QUAZIP_LIBRARY_2)
target_link_libraries (qfaktury
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Xml
    Qt5::WebEngineWidgets
    Qt5::Network 
    quazip
    )
endif()

if((CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "GNU")
   AND NOT CMAKE_CROSSCOMPILING)

    SET(QFAKTURY_PATH "/usr/share/qfaktury")

    install(TARGETS qfaktury DESTINATION /usr/bin)
    install(DIRECTORY icons DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY templates DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY docs DESTINATION /usr/share/doc/qfaktury)
    install(FILES QFaktury.desktop DESTINATION /usr/share/applications)
    install(DIRECTORY src DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY ui DESTINATION ${QFAKTURY_PATH})

endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows" AND NOT CMAKE_CROSSCOMPILING)

    SET(QFAKTURY_PATH "$ENV{HOME}/AppData/Roaming/qfaktury")

    install(TARGETS qfaktury DESTINATION C:/Windows/System32)
    install(DIRECTORY icons DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY templates DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY docs DESTINATION ${QFAKTURY_PATH})
    install(FILES QFaktury.desktop DESTINATION $ENV{HOME}/Desktop)
    install(DIRECTORY src DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY ui DESTINATION ${QFAKTURY_PATH})

endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin" AND NOT CMAKE_CROSSCOMPILING)

    SET(QFAKTURY_PATH "$ENV{HOME}/Library/Application Support/qfaktury")

    install(TARGETS qfaktury DESTINATION /usr/local/bin)
    install(DIRECTORY icons DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY templates DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY docs DESTINATION ${QFAKTURY_PATH})
    install(FILES QFaktury.desktop DESTINATION $ENV{HOME}/Desktop)
    install(DIRECTORY src DESTINATION ${QFAKTURY_PATH})
    install(DIRECTORY ui DESTINATION ${QFAKTURY_PATH})

endif()
