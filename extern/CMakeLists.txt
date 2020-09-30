include(FetchContent)

# Include glfw
message("Configuring GLFW")
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG        3.3.2
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

FetchContent_MakeAvailable(glfw)

# Include glm
message("Configuring GLM")
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)

# Include zlib-ng(Not currently used)
message("Configuring zlib-ng")
FetchContent_Declare(
        zlib_ng
        GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng
        GIT_TAG        1.9.9-b1
)

set(ZLIB_ENABLE_TESTS OFF)
set(WITH_NATIVE_INSTRUCTIONS ON)

FetchContent_MakeAvailable(zlib_ng)
