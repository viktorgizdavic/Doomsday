cmake_minimum_required(VERSION 3.11)
set(PROJECT_NAME Doomsday)
project(${PROJECT_NAME})

function(watch)
    set_property(
            DIRECTORY
            APPEND
            PROPERTY CMAKE_CONFIGURE_DEPENDS ${ARGV}
    )
endfunction()

set(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#list(APPEND CMAKE_CXX_FLAGS "-Wall -g -Wextra -Wno-unused-variable -Wno-unused-parameter -O3")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -g -Wextra -Wno-unused-variable -Wno-unused-parameter -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")

file(GLOB SOURCES "src/*.cpp" "src/*.c" src/main.cpp)
file(GLOB HEADERS "include/*.h" "include/*.hpp")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(ASSIMP REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/imgui)

add_definitions(${OPENGL_DEFINITIONS})

add_library(STB_IMAGE libs/stb_image.cpp)
set_source_files_properties(libs/stb_image.cpp include/stb_image.h
        PROPERTIES
        COMPILE_FLAGS
        "-Wno-shift-negative-value -Wno-implicit-fallthrough")

set(LIBS glfw glad OpenGL::GL X11 Xrandr Xinerama Xi Xxf86vm Xcursor dl pthread freetype ${ASSIMP_LIBRARIES} STB_IMAGE imgui)


configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)


include_directories(include/)
add_executable(${PROJECT_NAME}
        ${SOURCES} include/RectangleObject.h src/Game.cpp include/Game.h src/BoundingBox.cpp include/BoundingBox.h src/MoveableObject.cpp include/MoveableObject.h include/Cube.h include/LightCube.h include/crosshair.h)

target_link_libraries(${PROJECT_NAME} ${LIBS})

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
file(GLOB SHADERS "shaders/*.vs"
        "shaders/*.fs")
foreach(SHADER ${SHADERS})
    # file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/shaders)
    watch(${SHADER})
endforeach()

