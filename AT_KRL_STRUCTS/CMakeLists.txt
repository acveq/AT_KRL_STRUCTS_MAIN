cmake_minimum_required(VERSION 3.5)

project(AT_KRL_STRUCTS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

include_directories(${CMAKE_SOURCE_DIR}/src/structs/libs/libxml2/include/)
include_directories(${CMAKE_SOURCE_DIR}/src/structs/libs/jsoncpp/include/)


add_library(${PROJECT_NAME} STATIC
            src/structs/include/exceptions.h
            src/structs/include/utils.h

            src/structs/include/kb_entity.h
            src/structs/include/kb_operation.h
            src/structs/include/kb_reference.h
            src/structs/include/kb_value.h
            src/structs/include/kb_type.h
            src/structs/include/kb_rule.h
            src/structs/include/membership_function.h
            src/structs/include/non_factor.h

            src/structs/src/kb_entity.cpp
            src/structs/src/kb_operation.cpp
            src/structs/src/kb_reference.cpp
            src/structs/src/kb_value.cpp
            src/structs/src/kb_type.cpp
            src/structs/src/kb_rule.cpp
            src/structs/src/membership_function.cpp
            src/structs/src/non_factor.cpp
            src/structs/libs/jsoncpp/include/CMakeLists.txt
            src/structs/libs/libxml2/include/CMakeLists.txt
            src/tests/kb_entity_tests.cpp
            src/tests/kb_operation_tests.cpp
            src/tests/kb_reference_tests.cpp
            src/tests/kb_type_tests.cpp
            src/tests/kb_value_tests.cpp
            src/tests/membership_function_tests.cpp
            src/tests/non_factor_tests.cpp
            src/structs/libs/googletest/CMakeLists.txt

        )

target_include_directories(${PROJECT_NAME} PUBLIC
    src/
    src/structs/
    src/structs/include/
    src/structs/src/
    src/structs/libs/libxml2/include/
    src/structs/libs/jsoncpp/include/
    src/structs/libs/googletest/include/
)

