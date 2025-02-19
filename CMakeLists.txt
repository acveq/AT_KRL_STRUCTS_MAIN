cmake_minimum_required(VERSION 3.5)

project(AT_KRL_STRUCTS_MAIN VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        database_wrapper.h
        database_wrapper.cpp
)
add_executable(AT_KRL_STRUCTS_MAIN
    ${PROJECT_SOURCES}
    model_t.cpp model_t.h tree_node_t.cpp tree_node_t.h tree_t.cpp tree_t.h
    knowledge_base_t.cpp knowledge_base_t.h
)

add_subdirectory("AT_KRL_STRUCTS")

target_link_libraries(AT_KRL_STRUCTS_MAIN PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(AT_KRL_STRUCTS_MAIN PRIVATE Qt5::Sql)
target_link_libraries(AT_KRL_STRUCTS_MAIN PRIVATE AT_KRL_STRUCTS)
set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AT_KRL_STRUCTS_MAIN)

set_target_properties(AT_KRL_STRUCTS_MAIN PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AT_KRL_STRUCTS_MAIN
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



