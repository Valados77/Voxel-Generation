cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

set(PROJECT_NAME Voxel-Generation)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
src/main.cpp
src/renderer/ShaderProgram.cpp
src/renderer/ShaderProgram.h
src/renderer/Texture2D.cpp
src/renderer/Texture2D.h
src/renderer/Camera.cpp
src/renderer/Camera.h
src/renderer/ChunkRenderer.cpp
src/renderer/ChunkRenderer.h
src/renderer/BufferProgram.cpp
src/renderer/BufferProgram.h
src/renderer/Block.cpp
src/renderer/Block.h
src/resources/ResourceManager.cpp
src/resources/ResourceManager.h
src/resources/ResourceManager.h
src/resources/stb_image.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

