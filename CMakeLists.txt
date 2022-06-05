cmake_minimum_required(VERSION 3.20)
project(SingularEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-D_SEDebug_)
ELSEIF(${CMAKE_BUILD_TYPE} MATCHES Release)
    add_definitions(-D_SERelease_)
ELSE()
    message( FATAL_ERROR "Unknown build type!" )
ENDIF()

include_directories("${PROJECT_SOURCE_DIR}/SEditor")
include_directories("${PROJECT_SOURCE_DIR}/SEngine")
include_directories("${PROJECT_SOURCE_DIR}/SRuntime")

add_subdirectory(SEditor)
add_subdirectory(SEngine)
add_subdirectory(SRuntime)


include(CTest)
add_subdirectory(SUnitTest)

