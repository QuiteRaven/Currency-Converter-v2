cmake_minimum_required(VERSION 3.14.5 FATAL_ERROR)

project(Currency-Converter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)

set(project_headers 
    mainwindow.h
    item_edit_dialog.h
    item_edit_frame.h
    currency_type.h)

set(project_sources 
    main.cpp
    mainwindow.cpp
    item_edit_dialog.cpp
    item_edit_frame.cpp)

qt5_wrap_cpp(project_sources_moc ${project_headers})

add_executable(${PROJECT_NAME} ${project_headers} ${project_sources} 
    ${project_sources_moc} ${project_headers_wrapped})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network)
