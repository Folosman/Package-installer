cmake_minimum_required(VERSION 3.16)

project(PackageInstaller LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(PackageInstaller main.cpp
    mainwindow.h mainwindow.cpp
    packageinstaller.h packageinstaller.cpp)

target_link_libraries(PackageInstaller PRIVATE Qt6::Widgets)
target_link_libraries(PackageInstaller PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS PackageInstaller
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
