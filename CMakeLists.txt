project(qfaktury)
cmake_minimum_required(VERSION 2.4.7)
find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
set(qfaktury_SRCS
main.cpp
slownie.cpp
version.cpp
zaokr.cpp
Form1.cpp
FormFra.cpp
Form4.cpp
)

set(qfaktury_UIS
chamount.ui
formfra.ui
kontlist.ui
korform.ui
kreator.ui
mainform.ui
preview.ui
przelew.ui
sett.ui
towary.ui
towlist.ui
user.ui
Form4.ui
)


QT4_WRAP_UI(qfaktury_UIS_H ${qfaktury_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
qt4_automoc(${qfaktury_SRCS})
add_executable(qfaktury ${qfaktury_SRCS} ${qfaktury_UIS_H})
target_link_libraries(qfaktury ${QT_LIBRARIES})

