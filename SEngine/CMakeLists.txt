file(GLOB_RECURSE SEngineSources ${PROJECT_SOURCE_DIR}/SEngine "*.cpp" "*.c" "*.h")
add_library(SingularEngine ${SEngineSources})
TARGET_COMPILE_DEFINITIONS(SingularEngine PUBLIC SINGULARENGINE_EXPORTS )

target_link_libraries(SingularEngine imgui::imgui assimp::assimp opengl32 dxgi d3d11 d3dcompiler)

