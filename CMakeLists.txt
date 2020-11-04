cmake_minimum_required(VERSION 3.2)
project(Tukxel++)

# Make sure everything is compiled into the same dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
option(BUILD_SHARED_LIBS "" off)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")
endif()

add_subdirectory(extern)

include_directories(source
                    extern/glad/include
                    ${glfw_SOURCE_DIR}/include
                    extern/headeronly)

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set(SOURCE_FILES
    # GLAD
    extern/glad/glad.c

    # MAIN
    source/main.cpp

    # CLIENT
    source/client/client.cpp

    # RENDER
    source/client/render/shader.cpp
)

if(WIN32)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} Icon.rc)
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif()

target_compile_features(Tukxel++ PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} glfw glm::glm)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
    DEPENDS ${PROJECT_RESOURCES})