file(GLOB_RECURSE SEditorSources ${PROJECT_SOURCE_DIR}/SEditor "*.cpp" "*.c" "*.h")
add_library(SingularEditor ${SEditorSources})

target_include_directories(SingularEditor PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(SingularEditor SingularEngine)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")