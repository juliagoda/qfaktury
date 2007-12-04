project(qfaktury)
cmake_minimum_required(VERSION 2.4.7)
set(QT_USE_QTXML TRUE)
find_package(Qt4 REQUIRED)

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

