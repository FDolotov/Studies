cmake_minimum_required(VERSION 3.9.3 FATAL_ERROR)

project(chill2 LANGUAGES CXX)

add_executable(${PROJECT_NAME} "main.cpp" "mainwindow.cpp" "mainwindow.hpp" "mainwindow.ui")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON)

find_package(Qt5 5.9.1 REQUIRED COMPONENTS Widgets)
include(FindPkgConfig)
pkg_check_modules(exiv2 REQUIRED IMPORTED_TARGET exiv2)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::exiv2 Qt5::Widgets)
