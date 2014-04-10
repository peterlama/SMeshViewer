project(SMeshViewer)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DNOMINMAX)

set(QT_USE_QTOPENGL TRUE)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

find_library(GLEW_LIBRARY glew32.lib
    HINTS "$ENV{VS120COMNTOOLS}/../../VC/lib"
)

add_subdirectory(src)