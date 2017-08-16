project(qfaktury)

cmake_minimum_required(VERSION 2.8.12)
set(QT_MIN_VERSION "5.0.0")
set(KF5_MIN_VERSION "5.0.0")

find_package(ECM 1.7.0 REQUIRED CONFIG)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")

message(STATUS "${CMAKE_MODULE_PATH}")


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)


find_package( Qt5 REQUIRED COMPONENTS Gui Core Widgets PrintSupport Xml WebEngineWidgets Network )
find_package( KF5 REQUIRED COMPONENTS CoreAddons XmlGui I18n WidgetsAddons Archive )


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
    src/Send.cpp
    src/owncalendar.cpp
    src/SimpleSmtp_SSL_QT5/smtp_attachements/mainwindow.cpp
    src/SimpleSmtp_SSL_QT5/smtp_attachements/smtp.cpp
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

target_link_libraries (qfaktury
    Qt5::Gui
    Qt5::Core
    Qt5::Widgets
    Qt5::PrintSupport
    Qt5::Xml
    Qt5::WebEngineWidgets
    Qt5::Network
    KF5::CoreAddons
    KF5::XmlGui
    KF5::I18n
    KF5::WidgetsAddons
    KF5::Archive)



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

    SET(QFAKTURY_PATH $ENV{HOME}/AppData/Roaming/qfaktury)

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
