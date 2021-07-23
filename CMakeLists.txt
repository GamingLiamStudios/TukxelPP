cmake_minimum_required(VERSION 3.11)
project(Tukxel++)

# Make sure everything is compiled into the same dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

add_subdirectory(extern)

if(WIN32)
    add_executable(${PROJECT_NAME} Icon.rc)
else()
    add_executable(${PROJECT_NAME})
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} glfw glm::glm)

target_include_directories(${PROJECT_NAME} PUBLIC "extern")
target_include_directories(${PROJECT_NAME} PUBLIC "source") # to allow paths relative to project root

target_sources(${PROJECT_NAME} PRIVATE
    # GLAD
    extern/glad/glad.c

    # MAIN
    source/main.cpp
    source/client.cpp

    # ENGINE
    source/engine/shader.cpp
)

file(GLOB_RECURSE resources res/*.*)
add_custom_target(resources_copy ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                  ${resources} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/res)