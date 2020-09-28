cmake_minimum_required(VERSION 3.2)
project(Tukxel++)

# Make sure everything works
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
option(BUILD_SHARED_LIBS "" off)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

add_subdirectory(extern)

include_directories(extern/glad/include
                    ${glfw_SOURCE_DIR}/include
                    extern/stb)

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set(SOURCE_FILES
    # GLAD
    extern/glad/glad.c

    # MAIN
    source/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} glfw glm::glm)