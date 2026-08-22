cmake_minimum_required(VERSION 3.28)

project(PasswordGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(PasswordGenerator src/main.cpp)

add_subdirectory(src/model)
add_subdirectory(src/gui)

target_link_libraries(PasswordGenerator PRIVATE Qt6::Core Qt6::Widgets)
