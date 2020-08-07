cmake_minimum_required(VERSION 3.0)
project(Tukxel++)
set(CMAKE_CXX_STANDARD 17)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${PROJECT_NAME}/Vendor/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /arch:AVX2 /Za /Oxi")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Ofast -mavx2")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(${PROJECT_NAME}/Headers/
                    ${PROJECT_NAME}/Vendor/glad/include/
                    ${PROJECT_NAME}/Vendor/glfw/include/
                    ${PROJECT_NAME}/Vendor/glm/
                    ${PROJECT_NAME}/Vendor/stb/)

file(GLOB VENDORS_SOURCES ${PROJECT_NAME}/Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS ${PROJECT_NAME}/Headers/*.hpp)
file(GLOB PROJECT_SOURCES ${PROJECT_NAME}/Sources/*.cpp)
file(GLOB PROJECT_SHADERS ${PROJECT_NAME}/Shaders/*.comp
                          ${PROJECT_NAME}/Shaders/*.frag
                          ${PROJECT_NAME}/Shaders/*.geom
                          ${PROJECT_NAME}/Shaders/*.vert)
file(GLOB PROJECT_RESOURCES ${PROJECT_NAME}/Resources/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
    DEPENDS ${PROJECT_SHADERS})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
    DEPENDS ${PROJECT_RESOURCES})
