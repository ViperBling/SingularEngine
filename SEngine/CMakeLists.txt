file(GLOB_RECURSE SEngineSources ${PROJECT_SOURCE_DIR}/SEngine "*.cpp" "*.c" "*.h")
add_library(SingularEngine ${SEngineSources})
target_compile_definitions(SingularEngine PUBLIC SINGULARENGINE_EXPORTS)

target_link_libraries(SingularEngine imgui::imgui assimp::assimp opengl32 dxgi d3d11 d3dcompiler)

