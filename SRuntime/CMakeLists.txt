file(GLOB_RECURSE SRuntimeSources ${PROJECT_SOURCE_DIR}/SRuntime "*.cpp" "*.c" "*.h")
add_library(SingularRuntime ${SRuntimeSources})

target_include_directories(SingularRuntime PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(SingularRuntime SingularEngine)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")