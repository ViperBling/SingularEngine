add_executable(TestMath TestMath.cpp)
add_test(NAME TestMath COMMAND TestMath)
target_include_directories(TestMath PUBLIC ${PROJECT_SOURCE_DIR})