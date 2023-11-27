cmake_minimum_required(VERSION 2.8.12.2)
project(SpaceShooter)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(dependencies/glfw)

file(GLOB_RECURSE source_executable      src/*.cpp)
file(GLOB_RECURSE source_lib_headers src/lib/*.h)
file(GLOB_RECURSE source_lib_impl src/lib/*.cpp)

file(GLOB_RECURSE glfw_impl dependencies/glfw/src/*.c)
file(GLOB_RECURSE glfw_include dependencies/glfw/include/*.h)

add_executable(main ${source_executable})
add_library(lib ${source_lib_impl})
add_library(glad dependencies/glad/src/glad.c)

target_link_libraries(main PUBLIC lib glad glfw ${glfw_LIBRARIES})
target_link_libraries(lib PUBLIC glad glfw ${glfw_LIBRARIES})

target_compile_features(main PUBLIC cxx_std_17)
target_compile_features(lib PUBLIC cxx_std_17)

target_include_directories(main PUBLIC src/lib dependencies/glad/include dependencies/glfw/include dependencies/headers dependencies/headers/glm)
target_include_directories(lib PUBLIC src/lib dependencies/glad/include dependencies/glfw/include dependencies/headers dependencies/headers/glm)

target_include_directories(glad PUBLIC dependencies/glad/include)

install(TARGETS main DESTINATION ./build)

set(CPACK_PACKAGE_NAME "SpaceShooter")
set(CPACK_PACKAGE_VERSION "1.0.0")

# This must be last
include(CPack)
