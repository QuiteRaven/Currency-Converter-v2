cmake_minimum_required(VERSION 3.14.5 FATAL_ERROR)

project(Currency-Converter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)

set(PROJECT_HEADERS 
    mainwindow.h
    about_dialog.h
    item_edit_frame.h
    currency_Type.h)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    about_dialog.cpp
    item_edit_frame.cpp)

set(PROJECT_RESOURCES
    Resources/MainWindow.qrc)

qt5_wrap_cpp(PROJECT_SOURCES_MOC ${PROJECT_HEADERS})

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_RESOURCES}
    ${PROJECT_SOURCES_MOC} ${PROJECT_HEADERS_WRAPPED})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network)
