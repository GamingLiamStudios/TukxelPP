# CMakeList.txt : CMake project for Tukxel++, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
find_package(OpenGL REQUIRED)

# Add source to this project's executable.
add_executable (Tukxel++ "Tukxel++.cpp")


# TODO: Add tests and install targets if needed.
link_libraries(glfw OpenGL::GL)